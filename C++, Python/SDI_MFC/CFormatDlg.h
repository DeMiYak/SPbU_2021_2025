#pragma once
#include "afxdialogex.h"


// Диалоговое окно CFormatDlg

class CFormatDlg : public CDialog
{
	DECLARE_DYNAMIC(CFormatDlg)

public:
	CFormatDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CFormatDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FORMAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	afx_msg void OnEnChangeEditControl();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioGreen();
	afx_msg void OnBnClickedRadioBlue();
	afx_msg void OnBnClickedRadioRed();
	int m_width;
	int m_colorIndex;
	COLORREF m_lineColor;
//	afx_msg void OnBnKillfocusRadio2();
	afx_msg void OnEnKillfocusEditControl();
//	afx_msg void OnBnSetfocusRadio2();
//	afx_msg void OnBnKillfocusRadio2();
	CEdit m_editCtrl;
	CButton m_blue;
};