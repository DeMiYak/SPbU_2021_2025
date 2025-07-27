
// MFC_SDI_YMDView.cpp : implementation of the CMFCSDIYMDView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_SDI_YMD.h"
#endif

#include "MFC_SDI_YMDDoc.h"
#include "MFC_SDI_YMDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSDIYMDView

IMPLEMENT_DYNCREATE(CMFCSDIYMDView, CView)

BEGIN_MESSAGE_MAP(CMFCSDIYMDView, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCSDIYMDView construction/destruction

CMFCSDIYMDView::CMFCSDIYMDView() noexcept
{
    // TODO: add construction code here

}

CMFCSDIYMDView::~CMFCSDIYMDView()
{
}

BOOL CMFCSDIYMDView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CMFCSDIYMDView drawing

void CMFCSDIYMDView::OnDraw(CDC* pDC)
{
    CMFCSDIYMDDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (pDoc->isOpenWindow) {
        drawHist(pDoc, pDC);
    }

    // TODO: add draw code for native data here
}

void CMFCSDIYMDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CMFCSDIYMDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCSDIYMDView diagnostics

#ifdef _DEBUG
void CMFCSDIYMDView::AssertValid() const
{
    CView::AssertValid();
}

void CMFCSDIYMDView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMFCSDIYMDDoc* CMFCSDIYMDView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSDIYMDDoc)));
    return (CMFCSDIYMDDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSDIYMDView message handlers


// Рисует гистограмму
void CMFCSDIYMDView::drawHist(CMFCSDIYMDDoc* pDoc, CDC* pDC)
{
    int empLen = pDoc->hist.GetEmpLength();
    int* empFreq = pDoc->hist.GetEmpFrequency();
    int whBalls = pDoc->d1.GetWhBalls();
    int blBalls = pDoc->d1.GetBlBalls();
    int pickNum = pDoc->d1.GetPickNum();

    CRect clientRect;
    GetClientRect(&clientRect);

    CPen newPen;
    newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    CPen* pOldPen = (CPen*)pDC->SelectObject(&newPen);

    int maxFreq = INT_MIN;
    int minFreq = INT_MAX;
    for (int i = 0; i < empLen; i++)
    {
        if (empFreq[i] > maxFreq)
            maxFreq = empFreq[i];
        if (empFreq[i] < minFreq)
            minFreq = empFreq[i];
    }

    int histWidth = 0.8 * clientRect.Width();
    int barWidth = double(2) / 3 * clientRect.Width() / empLen;
    int barSpaceWidth = 0.2 * barWidth;
    int histHeight = 0.6 * clientRect.Height();
    int leftSpace = 0.1 * clientRect.Width();
    int bottomSpace = 0.8 * clientRect.Height();
    CString message;
    int k = 0;
    for (int i = 0; i < empLen; ++i)
    {
        int barHeight = histHeight * (empFreq[i] - minFreq) / (maxFreq - minFreq);
        int left = i * barWidth + leftSpace + k * barSpaceWidth;
        int right = (i + 1) * barWidth + leftSpace + k * barSpaceWidth;
        int middle = (left + right) / 2;
        int top = bottomSpace - barHeight;
        int bottom = bottomSpace;
        //pDC->FillSolidRect(0,0,0,0, RGB(255,255,255));
        //message.Format(L"%d", i);
        //pDC->TextOut(middle, bottom + 0.05 * histHeight, message);
        CRect barRect(left, top, right, bottom);
        pDC->FillSolidRect(&barRect, RGB(120, 100, 200));
        ++k;
    }
    // Изменение цвета кисти (чтобы цвет не распространялся на TextOut)
    pDC->FillSolidRect(0, 0, 0, 0, RGB(255, 255, 255));
    for (int i = 0; i < empLen; ++i) {
        message.Format(L"%d", i);
        pDC->TextOut(leftSpace + (i + 0.5) * barWidth + i * barSpaceWidth, bottomSpace + 0.05 * histHeight, message);
    }

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
    info.Format(L"%s%d%s%d%s%d%s%d", L"Гипергеометрическое распределение при: белых шариков = ",
        whBalls, L", чёрных шариков = ", blBalls,
        L", число вытаскиваний = ", pickNum,
        L", объём выборки = ", pDoc->samMod->samVol);
    pDC->TextOut(leftSpace - 20, 0.1 * clientRect.Height(), info);
    // TODO: Add your implementation code here.
}