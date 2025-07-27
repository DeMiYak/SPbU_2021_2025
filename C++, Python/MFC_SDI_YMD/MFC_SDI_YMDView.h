
// MFC_SDI_YMDView.h : interface of the CMFCSDIYMDView class
//

#pragma once


class CMFCSDIYMDView : public CView
{
protected: // create from serialization only
	CMFCSDIYMDView() noexcept;
	DECLARE_DYNCREATE(CMFCSDIYMDView)

	// Attributes
public:
	CMFCSDIYMDDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	virtual ~CMFCSDIYMDView();
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
	void drawHist(CMFCSDIYMDDoc* pDoc, CDC* pDC);
};

#ifndef _DEBUG  // debug version in MFC_DEMOView.cpp
inline CMFCSDIYMDDoc* CMFCSDIYMDView::GetDocument() const
{
	return reinterpret_cast<CMFCSDIYMDDoc*>(m_pDocument);
}
#endif