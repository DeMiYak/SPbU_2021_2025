
// MFC_SDI_YMDDoc.cpp : implementation of the CMFCSDIYMDDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_SDI_YMD.h"
#endif

#include "MFC_SDI_YMDDoc.h"
#include"ModelDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCSDIYMDDoc

IMPLEMENT_DYNCREATE(CMFCSDIYMDDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCSDIYMDDoc, CDocument)
	ON_COMMAND(ID_DIALOG_MODELLING, &CMFCSDIYMDDoc::OnDialogModelling)
	ON_COMMAND(ID_DIALOG_PARAMETERS, &CMFCSDIYMDDoc::OnDialogParameters)
END_MESSAGE_MAP()


// CMFCSDIYMDDoc construction/destruction

CMFCSDIYMDDoc::CMFCSDIYMDDoc() noexcept
{
	d1.ChangeWhBalls();
	d1.ChangeBlBalls();
	d1.ChangePickNum();
	/*hist.distrHist = d1;
	hist.samHist = nullptr;*/
	hist.SetLength(d1.GetPickNum() + 1);
	samMod = new BernoulliSample(100);
	method = BD;

	// TODO: add one-time construction code here

}

CMFCSDIYMDDoc::~CMFCSDIYMDDoc()
{
	delete samMod;
}

BOOL CMFCSDIYMDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCSDIYMDDoc serialization

void CMFCSDIYMDDoc::Serialize(CArchive& ar)
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
void CMFCSDIYMDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCSDIYMDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCSDIYMDDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCSDIYMDDoc diagnostics

#ifdef _DEBUG
void CMFCSDIYMDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCSDIYMDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCSDIYMDDoc commands


void CMFCSDIYMDDoc::OnDialogModelling()
{
	isOpenWindow = TRUE;
	samMod->Simulate(d1, samMod->samVol);
	hist.CountSampleFrequency(samMod, d1);

	UpdateAllViews(0);
	// TODO: Add your command handler code here
}


void CMFCSDIYMDDoc::OnDialogParameters()
{
	ModelDlg model;
	model.samVol = samMod->samVol;
	model.pickNum = d1.GetPickNum();
	model.blBalls = d1.GetBlBalls();
	model.whBalls = d1.GetWhBalls();
	model.method = method;
	if (model.DoModal() == IDOK) {
		// samMod->samVol = model.samVol;

		// Присваивание значений из диалогового окна
		// Число взятий
		d1.ChangePickNum(model.pickNum);
		// Белые шарики
		d1.ChangeBlBalls(model.blBalls);
		// Чёрные шарики
		d1.ChangeWhBalls(model.whBalls);
		// Радио-кнопка (является Бернулли)
		method = model.method;
		// Длина эмпирических частот
		hist.SetLength(model.pickNum + 1);

		// Работа с радио-кнопками (выбор метода)
		if (method == BD) {
			delete samMod;
			samMod = new BernoulliSample(model.samVol);
		}
		else {
			delete samMod;
			samMod = new InverseFunctionSample(model.samVol);
		}
	}
	// TODO: Add your command handler code here
}