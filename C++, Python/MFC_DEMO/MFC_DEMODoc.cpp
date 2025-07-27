
// MFC_DEMODoc.cpp : implementation of the CMFCDEMODoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_DEMO.h"
#endif

#include "MFC_DEMODoc.h"
#include"Method.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDEMODoc

IMPLEMENT_DYNCREATE(CMFCDEMODoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDEMODoc, CDocument)
	ON_COMMAND(ID_DIALOG_MODELLING, &CMFCDEMODoc::OnFrequencyModelling)
	ON_COMMAND(ID_DIALOG_PARAMETERS, &CMFCDEMODoc::OnFrequencyParameters)
	ON_COMMAND(ID_PL_PARAMETERS, &CMFCDEMODoc::OnPlParameters)
	ON_COMMAND(ID_PL_MODELLING, &CMFCDEMODoc::OnPlModelling)
	ON_COMMAND(ID_CV_PARAMETERS, &CMFCDEMODoc::OnCvParameters)
	ON_COMMAND(ID_CV_MODELLING, &CMFCDEMODoc::OnCvModelling)
END_MESSAGE_MAP()


// CMFCDEMODoc construction/destruction

CMFCDEMODoc::CMFCDEMODoc() noexcept :
	d0(),
	samMod(new BernHypGeomSampleGenerator(100)),
	chiSqHist(),
	method(BD),
	pl_d0(),
	pl_d1(23,31),
	pl_samMod(new BernHypGeomSampleGenerator(100)),
	pl_method(BD),
	cv_d0(),
	cv_d1(),
	cv_samMod(new BernHypGeomSampleGenerator(100)),
	cv_method(BD),
	p_levels(nullptr),
	pl_repnum(10000),
	critnum(10),
	from_sv(100),
	intrv_sv(100),
	powcrits(nullptr),
	cv_repnum(10000),
	slvl(0.05)
{
}

CMFCDEMODoc::~CMFCDEMODoc()
{
	delete samMod;
	delete pl_samMod;
	delete cv_samMod;
	delete[] p_levels;
	delete[] powcrits;
}

BOOL CMFCDEMODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDEMODoc serialization

void CMFCDEMODoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDEMODoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCDEMODoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDEMODoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCDEMODoc diagnostics

#ifdef _DEBUG
void CMFCDEMODoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDEMODoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDEMODoc commands

/// <summary>
/// Моделирует эмпирические и теоретические частоты
/// </summary>
void CMFCDEMODoc::OnFrequencyModelling()
{
	Window = HIST;
	samMod->Simulate(d0, samMod->GetSamVol());
	chiSqHist.SetData(samMod, d0);
	chiSqHist.CalcChiSq();

	UpdateAllViews(0);
	// TODO: Add your command handler code here
}

/// <summary>
/// Переписывает параметры для моделирования эмпирических и
/// теоретических частот и моделирует их
/// </summary>
void CMFCDEMODoc::OnFrequencyParameters()
{
	ModelDlg model;
	model.samVol = samMod->GetSamVol();
	model.pickNum = d0.GetPickNum();
	model.blBalls = d0.GetBlBalls();
	model.whBalls = d0.GetWhBalls();
	model.method = method;
	if (model.DoModal() == IDOK) {
		// samMod->samVol = model.samVol;
		d0.SetParameters(model.whBalls, model.blBalls, model.pickNum);
		// Радио-кнопка (является Бернулли)
		method = model.method;
		// Длина эмпирических частот

		// Работа с радио-кнопками (выбор метода)
		delete samMod;
		switch (method) {
		case BD:
			samMod = new BernHypGeomSampleGenerator(model.samVol);
			break;
		case IF:
			samMod = new InvFunHypGeomSampleGenerator(model.samVol);
			break;
		}
		OnFrequencyModelling();
	}
	// TODO: Add your command handler code here
}

/// <summary>
/// Строит p-distribution (распределение p-levels) в виде
/// кумулятивной функции распределения по параметрам.
/// </summary>
void CMFCDEMODoc::Simulate_P_Distribution()
{
	delete[] p_levels;
	p_levels = new double[pl_repnum];
	for (int i = 0; i < pl_repnum; i++) {
		pl_samMod->Simulate(pl_d1, pl_samMod->GetSamVol());
		chiSqHist.SetData(pl_samMod, pl_d0);
		chiSqHist.CalcChiSq();
		p_levels[i] = chiSqHist.GetPLevel();
	}
	for (int i = 0; i < 20; i++) {
		p_distribution[i] = 0;
	}
	for (int i = 0; i < pl_repnum; i++) {
		double plvl = p_levels[i];
		plvl = floor(plvl / 0.05);
		if (plvl == 20) plvl--;
		p_distribution[int(plvl)]++;
	}
	for (int k = 1; k < 20; k++) {
		p_distribution[k] += p_distribution[k - 1];
		p_distribution[k - 1] /= pl_repnum;
	}
	p_distribution[19] /= pl_repnum;

}

/// <summary>
/// Перезаписывает параметры для распределения p-levels и
/// перемоделирует распределение p-levels
/// </summary>
void CMFCDEMODoc::OnPlParameters()
{
	PLevelDlg model;
	model.pl_h0_whball = pl_d0.GetWhBalls();
	model.pl_h0_blball = pl_d0.GetBlBalls();
	model.pl_h0_picknum = pl_d0.GetPickNum();
	model.pl_h1_whball = pl_d1.GetWhBalls();
	model.pl_h1_blball = pl_d1.GetBlBalls();
	model.pl_h1_picknum = pl_d1.GetPickNum();
	model.pl_samvol = pl_samMod->GetSamVol();
	model.pl_repnum = pl_repnum;
	model.pl_method = pl_method;
	if (model.DoModal() == IDOK) {
		pl_method = model.pl_method;

		pl_d0.SetParameters(model.pl_h0_whball, model.pl_h0_blball, model.pl_h0_picknum);
		pl_d1.SetParameters(model.pl_h1_whball, model.pl_h1_blball, model.pl_h1_picknum);

		pl_repnum = model.pl_repnum;
		
		delete pl_samMod;
		switch (pl_method) {
		case BD:
			pl_samMod = new BernHypGeomSampleGenerator(model.pl_samvol);
			break;
		case IF:
			pl_samMod = new InvFunHypGeomSampleGenerator(model.pl_samvol);
			break;
		}
		OnPlModelling();
	}
	// TODO: Add your command handler code here
}

/// <summary>
/// Моделирования распределения p_levels
/// </summary>
void CMFCDEMODoc::OnPlModelling()
{
	Window = PLEVEL;
	Simulate_P_Distribution();
	UpdateAllViews(0);
}


/// <summary>
/// Строит массив мощностей критерия по полям
/// </summary>
void CMFCDEMODoc::Simulate_PowCrits()
{
	delete[] powcrits;
	powcrits = new double[critnum];
	int curr_sv = from_sv;
	for (int k = 0; k < critnum; k++) {
		double critpow = 0;
		for (int i = 0; i < cv_repnum; i++) {
			cv_samMod->Simulate(cv_d1, curr_sv);
			chiSqHist.SetData(cv_samMod, cv_d0);
			chiSqHist.CalcChiSq();
			double pLevel = chiSqHist.GetPLevel();
			if (pLevel <= slvl) {
				critpow++;
			}
		}
		critpow /= cv_repnum;
		powcrits[k] = critpow;
		curr_sv += intrv_sv;
	}
}

/// <summary>
/// Перезаписывает параметры и перемоделирует график зависимости
/// мощности критерия от объёма выборки при заданных альтернативе и уровне
/// значимости 
/// </summary>
void CMFCDEMODoc::OnCvParameters()
{
	CritVolDlg model;
	model.cv_h0_whball = cv_d0.GetWhBalls();
	model.cv_h0_blball = cv_d0.GetBlBalls();
	model.cv_h0_picknum = cv_d0.GetPickNum();
	model.cv_h1_whball = cv_d1.GetWhBalls();
	model.cv_h1_blball = cv_d1.GetBlBalls();
	model.cv_h1_picknum = cv_d1.GetPickNum();
	model.cv_from_sv = from_sv;
	model.critnum = critnum;
	model.cv_repnum = cv_repnum;
	model.cv_interval_sv = intrv_sv;
	model.cv_slvl = slvl;
	model.cv_method = cv_method;
	model.cv_repnum = cv_repnum;
	if (model.DoModal() == IDOK) {
		cv_d0.SetParameters(model.cv_h0_whball, model.cv_h0_blball, model.cv_h0_picknum);
		cv_d1.SetParameters(model.cv_h1_whball, model.cv_h1_blball, model.cv_h1_picknum);

		cv_method = model.cv_method;
		slvl = model.cv_slvl;
		from_sv = model.cv_from_sv;
		intrv_sv = model.cv_interval_sv;
		critnum = model.critnum;
		cv_repnum = model.cv_repnum;

		delete cv_samMod;
		switch (cv_method) {
		case BD:
			cv_samMod = new BernHypGeomSampleGenerator(model.cv_from_sv);
			break;
		case IF:
			cv_samMod = new InvFunHypGeomSampleGenerator(model.cv_from_sv);
			break;
		}
		OnCvModelling();
	}
}

/// <summary>
/// Моделирование графика зависимости мощности критерия 
/// мощности критерия от объёма выборки при заданных альтернативе и уровне
/// значимости
/// </summary>
void CMFCDEMODoc::OnCvModelling()
{
	Window = CRITVOL;
	Simulate_PowCrits();
	UpdateAllViews(0);
}
