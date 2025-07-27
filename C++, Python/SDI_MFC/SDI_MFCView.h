// SDI_MFCView.h: интерфейс класса CSDIMFCView
//

#pragma once


class CSDIMFCView : public CView
{
protected: // создать только из сериализации
	CSDIMFCView() noexcept;
	DECLARE_DYNCREATE(CSDIMFCView)

// Атрибуты
public:
	CSDIMFCDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CSDIMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/*LOGPEN logPen;
	LOGBRUSH logBrush;*/
	COLORREF colorRef;
// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChangecolorRed();
	afx_msg void OnChangecolorGreen();
	afx_msg void OnChangecolorBlue();
	afx_msg void OnDialogclassMainTest();
	afx_msg void OnDialogclassDialOpen();
	afx_msg void OnDialogclassDialSave();
private:
	// CFormatDlg duplicates (to save the changes)
	int m_width = 1;
	int m_colorIndex = 0;
public:
	afx_msg void OnDialogclassColor();
};

#ifndef _DEBUG  // версия отладки в SDI_MFCView.cpp
inline CSDIMFCDoc* CSDIMFCView::GetDocument() const
   { return reinterpret_cast<CSDIMFCDoc*>(m_pDocument); }
#endif

