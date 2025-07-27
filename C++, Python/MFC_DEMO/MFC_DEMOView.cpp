
// MFC_DEMOView.cpp : implementation of the CMFCDEMOView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_DEMO.h"
#endif

#include "MFC_DEMODoc.h"
#include "MFC_DEMOView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDEMOView

IMPLEMENT_DYNCREATE(CMFCDEMOView, CView)

BEGIN_MESSAGE_MAP(CMFCDEMOView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCDEMOView construction/destruction

CMFCDEMOView::CMFCDEMOView() noexcept
{
	// TODO: add construction code here

}

CMFCDEMOView::~CMFCDEMOView()
{
}

BOOL CMFCDEMOView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDEMOView drawing
// Работа с заголовочными файлами
// Напоминание про систему прекомпилированных заголовков


void CMFCDEMOView::OnDraw(CDC* pDC)
{
	CMFCDEMODoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    
    if (pDoc->Window == HIST) {
		drawHist(pDoc, pDC);
    }
    if (pDoc->Window == PLEVEL) {
        drawPLevels(pDoc, pDC);
    }
    if (pDoc->Window == CRITVOL) {
        drawPowCrits(pDoc, pDC);
    }
	
    // TODO: add draw code for native data here
}

void CMFCDEMOView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDEMOView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDEMOView diagnostics

#ifdef _DEBUG
void CMFCDEMOView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDEMOView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDEMODoc* CMFCDEMOView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDEMODoc)));
	return (CMFCDEMODoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDEMOView message handlers


/// <summary>
/// Рисует гистограмму с эмпирическими и теоретическими частотами
/// </summary>
/// <param name="pDoc"></param>
/// <param name="pDC"></param>
void CMFCDEMOView::drawHist(CMFCDEMODoc* pDoc, CDC* pDC)
{
    int len = pDoc->chiSqHist.GetFreqLen();
    int* empFreq = pDoc->chiSqHist.GetEmpFreq();
    double* thFreq = pDoc->chiSqHist.GetThFreq();
    double chisq = pDoc->chiSqHist.GetChi();
    int df = pDoc->chiSqHist.GetDegreeOfFreedom();
    double plevel = pDoc->chiSqHist.GetPLevel();
    int whBalls = pDoc->d0.GetWhBalls();
    int blBalls = pDoc->d0.GetBlBalls();
    int pickNum = pDoc->d0.GetPickNum();
    

    CRect clientRect;
    GetClientRect(&clientRect);

    CPen newPen;
    newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    CPen* pOldPen = (CPen*)pDC->SelectObject(&newPen);

    // Задаём наибольшие и наименьшие значения частот.
    int maxFreq = INT_MIN;
    int minFreq = INT_MAX;
    for (int i = 0; i < len; i++)
    {
        if (empFreq[i] > maxFreq || thFreq[i] > maxFreq)
            maxFreq = max(empFreq[i], thFreq[i]);
        if (empFreq[i] < minFreq || thFreq[i] < minFreq)
            minFreq = min(empFreq[i], thFreq[i]);
    }
    int diff = maxFreq - minFreq;

    int histWidth = 0.8 * clientRect.Width();
    int barWidth = double(2) / 3 * clientRect.Width() / len;
    int barSpaceWidth = 0.2 * barWidth;
    int thBarWidth = 0.25 * barWidth;
    int histHeight = 0.6 * clientRect.Height();
    int leftSpace = 0.1 * clientRect.Width();
    int bottomSpace = 0.8 * clientRect.Height();
    CString message;
    // int k = 0;
    for (int i = 0; i < len; ++i)
    {
        // Empiric barHeight
        int barHeightEmp = histHeight * (empFreq[i] - minFreq) / diff;
        int leftEmp = i * barWidth + leftSpace + i * barSpaceWidth;
        int rightEmp = (i + 1) * barWidth + leftSpace + i * barSpaceWidth;
        int topEmp = bottomSpace - barHeightEmp;
        int bottom = bottomSpace;
        CRect barRectEmp(leftEmp, topEmp, rightEmp, bottom);
        pDC->FillSolidRect(&barRectEmp, RGB(120, 100, 200));

        // Theoretic barHeight
        int barHeightTh = histHeight * (thFreq[i] - minFreq) / diff;
        int topTh = bottomSpace - barHeightTh;
        int leftTh = i * barWidth + leftSpace + i * barSpaceWidth + thBarWidth;
        int rightTh = (i + 1) * barWidth + leftSpace + i * barSpaceWidth - thBarWidth;
        CRect barRectTh(leftTh, topTh, rightTh, bottom);
        pDC->FillSolidRect(&barRectTh, RGB(80, 60, 130));
    }
    // Изменение цвета кисти (чтобы цвет не распространялся на TextOut)
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255, 255, 255));
    for (int i = 0; i < len; ++i) {
        message.Format(L"%d", i);
        pDC->TextOut(leftSpace + (i + 0.5) * barWidth + i * barSpaceWidth, bottomSpace + 0.05 * histHeight, message);
    }
    
    // Легенда под гистограммой
    CRect EmpRect(leftSpace, bottomSpace*1.1, leftSpace + 0.1*histWidth, bottomSpace*1.15);
    pDC->FillSolidRect(&EmpRect, RGB(120, 100, 200));
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255, 255, 255));
    message.Format(L"%s", L"- эмпирическая частота");
    pDC->TextOut(leftSpace + 0.105*histWidth, bottomSpace*1.11, message);
    CRect ThRect(leftSpace, bottomSpace * 1.2, leftSpace + 0.1 * histWidth, bottomSpace * 1.25);
    pDC->FillSolidRect(&ThRect, RGB(80, 60, 130));
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255, 255, 255));
    message.Format(L"%s", L"- теоретическая частота");
    pDC->TextOut(leftSpace + 0.105 * histWidth, bottomSpace * 1.21, message);
    
    // Черчение графика
    
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace + histWidth, bottomSpace);
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace, bottomSpace - histHeight);

    pDC->SelectObject(pOldPen);
    newPen.DeleteObject();

    CString maxStr;
    maxStr.Format(L"%d", maxFreq);
    pDC->TextOut(leftSpace - 10 * ceil(log10(maxFreq)), bottomSpace - histHeight, maxStr);
    CString minStr;
    minStr.Format(L"%d", minFreq);
    pDC->TextOut(leftSpace - 20, bottomSpace - 20, minStr);

    CString info;
    info.Format(L"%s%s%d%s%d%s%d%s%d", pDoc->d0.GetName(), L" при: белых шариков = ",
        whBalls, L", чёрных шариков = ", blBalls,
        L", число вытаскиваний = ", pickNum,
        L", объём выборки = ", pDoc->samMod->GetSamVol());
    pDC->TextOut(leftSpace - 20, 0.1 * clientRect.Height(), info);

    CString info2;
    info2.Format(L"%s%lf%s%d%s%lf",
        L"статистика хи-квадрата = ", chisq,
        L", степень свободы = ", df,
        L", пороговое значение (p-level) = ", plevel);
    pDC->TextOut(leftSpace - 20, 0.12 * clientRect.Height(), info2);

    // TODO: Add your implementation code here.
}

/// <summary>
/// Рисует P-Levels по выборке p-levels вместе с 
/// теоретическим распределением (равномерным).
/// Изображает кумулятивную функцию распределения
/// </summary>
/// <param name="pDoc"></param>
/// <param name="pDC"></param>
void CMFCDEMOView::drawPLevels(CMFCDEMODoc* pDoc, CDC* pDC)
{
    // Разделим зарисовку на несколько этапов:
    // 0. Копирование необходимых данных из pDoc
    double* p_distr = (double*)pDoc->p_distribution;
    int whBalls_h0 = pDoc->pl_d0.GetWhBalls();
    int blBalls_h0 = pDoc->pl_d0.GetBlBalls();
    int pickNum_h0 = pDoc->pl_d0.GetPickNum();
    int whBalls_h1 = pDoc->pl_d1.GetWhBalls();
    int blBalls_h1 = pDoc->pl_d1.GetBlBalls();
    int samVol = pDoc->pl_samMod->GetSamVol();
    int repNum = pDoc->pl_repnum;

    // 1. Черчение графика
    // Создание квадрата для рисования
    CRect clientRect;
    GetClientRect(&clientRect);
    
    // Чёрная ручка (для осей)
    CPen newPenBlack;
    newPenBlack.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

    CPen* pOldPen = (CPen*)pDC->SelectObject(&newPenBlack);
    
    // Красная ручка (для полученного распределения p-levels)
    CPen newPenRed;
    newPenRed.CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

    // Серебрянная ручка (для теоретического распределения)
    CPen newPenSilver;
    newPenSilver.CreatePen(PS_SOLID, 2, RGB(220, 220, 220));

    // Параметры графика
    int graphWidth = 0.8 * clientRect.Width();
    int graphHeight = 0.6 * clientRect.Height();
    int seqWidth = double(graphWidth) / 20;
    int leftSpace = 0.1 * clientRect.Width();
    int bottomSpace = 0.8 * clientRect.Height();

    // Зарисовка осей X, Y
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace + graphWidth, bottomSpace);
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace, bottomSpace - graphHeight);
    
    // Меняем ручку на серебрянную
    pDC->SelectObject(newPenSilver);

    // Чёрная ручка больше не нужна
    newPenBlack.DeleteObject();

    // График теоретического распределения
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace + graphWidth, bottomSpace - graphHeight);

    // Меняем ручку на красную
    pDC->SelectObject(newPenRed);
    newPenSilver.DeleteObject();
    
    CString X;
    pDC->MoveTo(leftSpace, bottomSpace);
    // График эмпирического распределения + значения по оси X
    for (int k = 1; k <= 20; k++) {
        X.Format(L"%.2lf", k*0.05);
        pDC->LineTo(leftSpace + k * seqWidth, bottomSpace - p_distr[k-1]*graphHeight);
        pDC->TextOut(leftSpace + k * seqWidth, bottomSpace + 0.05 * graphHeight, X);
    }

    pDC->SelectObject(pOldPen);
    newPenRed.DeleteObject();
    // 2. Описания графика
    CString Y;
    
    // Значения по оси Y
    for (int i = 0; i <= 20; i++) {
        double k = i * 0.05;
        Y.Format(L"%.2lf", k);
        pDC->TextOut(leftSpace - 30, bottomSpace - k * graphHeight, Y);
    }

    CString info;
    info.Format(L"%s", L"Распределение p-levels против альтернативы H1");
    pDC->TextOut(leftSpace - 20, 0, info);
    // H0
    info.Format(L"%s%d%s%d%s%d", L"Распределение, на согласие с которым проверятся гипотеза: белых шариков = ",
        whBalls_h0, L", чёрных шариков = ", blBalls_h0,
        L", число вытаскиваний = ", pickNum_h0);
    pDC->TextOut(leftSpace - 20, 0.05 * clientRect.Height(), info);
    // H1
    info.Format(L"%s%d%s%d", L"Моделируемое распределение: белых шариков = ",
        whBalls_h1, L", чёрных шариков = ", blBalls_h1);
    pDC->TextOut(leftSpace - 20, 0.1 * clientRect.Height(), info);

    // Объём выборки, число повторений
    info.Format(L"%s%d%s%d", L"Объём выборки = ", samVol, L", число повторов = ", repNum);
    pDC->TextOut(leftSpace - 20, 0.15 * clientRect.Height(), info);

    // Легенда под графиком
    CRect EmpRect(leftSpace, bottomSpace * 1.1, leftSpace + 0.1 * graphWidth, bottomSpace * 1.15);
    pDC->FillSolidRect(&EmpRect, RGB(220, 20, 60));
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255,255,255));
    info.Format(L"%s", L"- эмпирическая функция распределения");
    pDC->TextOut(leftSpace + 0.105 * graphWidth, bottomSpace * 1.11, info);
    CRect ThRect(leftSpace, bottomSpace * 1.2, leftSpace + 0.1 * graphWidth, bottomSpace * 1.25);
    pDC->FillSolidRect(&ThRect, RGB(220, 220, 220));
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255,255,255));
    info.Format(L"%s", L"- теоретическая функция распределения");
    pDC->TextOut(leftSpace + 0.105 * graphWidth, bottomSpace * 1.21, info);

}

/// <summary>
/// Рисует график зависимости мощности критерия от объёма выборки
/// при заданных альтернативе и уровне значимости
/// </summary>
/// <param name="pDoc"></param>
/// <param name="pDC"></param>
void CMFCDEMOView::drawPowCrits(CMFCDEMODoc* pDoc, CDC* pDC)
{
    int from_sv = pDoc->from_sv;
    int intrv_sv = pDoc->intrv_sv;
    int critnum = pDoc->critnum;
    int cv_repnum = pDoc->cv_repnum;
    double slvl = pDoc->slvl;
    double* powcrits = (double*)pDoc->powcrits;
    int whBalls_h0 = pDoc->cv_d0.GetWhBalls();
    int blBalls_h0 = pDoc->cv_d0.GetBlBalls();
    int pickNum_h0 = pDoc->cv_d0.GetPickNum();
    int whBalls_h1 = pDoc->cv_d1.GetWhBalls();
    int blBalls_h1 = pDoc->cv_d1.GetBlBalls();

    // 1. Черчение графика
    // Создание квадрата для рисования
    CRect clientRect;
    GetClientRect(&clientRect);

    // Чёрная ручка (для осей)
    CPen newPenBlack;
    newPenBlack.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

    CPen* pOldPen = (CPen*)pDC->SelectObject(&newPenBlack);

    // Красная ручка (для полученного распределения p-levels)
    CPen newPenRed;
    newPenRed.CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

    // Параметры графика
    int graphWidth = 0.8 * clientRect.Width();
    int graphHeight = 0.6 * clientRect.Height();
    int seqWidth = double(graphWidth) / critnum;
    int leftSpace = 0.1 * clientRect.Width();
    int bottomSpace = 0.8 * clientRect.Height();

    // Зарисовка осей X, Y
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace + graphWidth, bottomSpace);
    pDC->MoveTo(leftSpace, bottomSpace);
    pDC->LineTo(leftSpace, bottomSpace - graphHeight);

    // Меняем ручку на красную
    pDC->SelectObject(newPenRed);

    // Чёрная ручка больше не нужна
    newPenBlack.DeleteObject();

    CString X;
    pDC->MoveTo(leftSpace, bottomSpace);
    // График мощности критерия (ошибки первого рода) + значения по оси X
    for (int k = 1; k <= critnum; k++) {
        X.Format(L"%d", from_sv+intrv_sv*(k-1));
        pDC->LineTo(leftSpace + k * seqWidth, bottomSpace - powcrits[k - 1] * graphHeight);
        pDC->TextOut(leftSpace + k * seqWidth, bottomSpace + 0.05 * graphHeight, X);
    }

    pDC->SelectObject(pOldPen);
    newPenRed.DeleteObject();

    // 2. Описания графика
    CString Y;

    // Значения по оси Y
    for (int i = 0; i <= 20; i++) {
        double k = i * 0.05;
        Y.Format(L"%.2lf", k);
        pDC->TextOut(leftSpace - 30, bottomSpace - k * graphHeight, Y);
    }

    CString info;
    // Название
    info.Format(L"%s", L"График зависимости мощности критерия от объёма выборки при заданном уровне значимости и заданной альтернативе");
    pDC->TextOut(leftSpace - 20, 0, info);
    // H0
    info.Format(L"%s%d%s%d%s%d", L"Распределение, на согласие с которым проверятся гипотеза: белых шариков = ",
        whBalls_h0, L", чёрных шариков = ", blBalls_h0,
        L", число вытаскиваний = ", pickNum_h0);
    pDC->TextOut(leftSpace - 20, 0.05 * clientRect.Height(), info);
    // H1
    info.Format(L"%s%d%s%d", L"Моделируемое распределение: белых шариков = ",
        whBalls_h1, L", чёрных шариков = ", blBalls_h1);
    pDC->TextOut(leftSpace - 20, 0.1 * clientRect.Height(), info);

    // Уровень значимости, от, интервал, до
    info.Format(L"%s%.2lf%s%d%s%d%s%d%s%d", L"Уровень значимости = ", slvl, 
        L", от = ", from_sv, L", интервал = ", intrv_sv, L", до = ", from_sv + intrv_sv*(critnum-1), L", число повторов = ", cv_repnum);
    pDC->TextOut(leftSpace - 20, 0.15 * clientRect.Height(), info);

    // Легенда под графиком
    CRect EmpRect(leftSpace, bottomSpace * 1.1, leftSpace + 0.1 * graphWidth, bottomSpace * 1.15);
    pDC->FillSolidRect(&EmpRect, RGB(220, 20, 60));
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255, 255, 255));
    info.Format(L"%s", L"- мощность критерия");
    pDC->TextOut(leftSpace + 0.105 * graphWidth, bottomSpace * 1.11, info);
}
