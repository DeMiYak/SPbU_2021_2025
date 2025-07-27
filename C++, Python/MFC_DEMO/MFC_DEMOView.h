// MFC_DEMOView.h : interface of the CMFCDEMOView class

#pragma once


class CMFCDEMOView : public CView
{
protected: // create from serialization only
	CMFCDEMOView() noexcept;
	DECLARE_DYNCREATE(CMFCDEMOView)

// Attributes
public:
	CMFCDEMODoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCDEMOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// Рисует гистограмму
	void drawHist(CMFCDEMODoc* pDoc, CDC* pDC);
	void drawPLevels(CMFCDEMODoc* pDoc, CDC* pDC);
	void drawPowCrits(CMFCDEMODoc* pDoc, CDC* pDC);
};

#ifndef _DEBUG  // debug version in MFC_DEMOView.cpp
inline CMFCDEMODoc* CMFCDEMOView::GetDocument() const
   { return reinterpret_cast<CMFCDEMODoc*>(m_pDocument); }
#endif

