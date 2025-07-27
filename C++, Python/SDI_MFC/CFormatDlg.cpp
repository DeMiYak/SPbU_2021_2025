// CFormatDlg.cpp: файл реализации
//

#include "pch.h"
#include "SDI_MFC.h"
#include "afxdialogex.h"
#include "CFormatDlg.h"


// Диалоговое окно CFormatDlg

IMPLEMENT_DYNAMIC(CFormatDlg, CDialog)

CFormatDlg::CFormatDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_FORMAT, pParent)
	, m_width(0)
	, m_colorIndex(0)
{

}

CFormatDlg::~CFormatDlg()
{
}

void CFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONTROL, m_width);
	DDX_Radio(pDX, IDC_RADIO1, m_colorIndex);
	DDX_Control(pDX, IDC_EDIT_CONTROL, m_editCtrl);
	DDX_Control(pDX, IDC_RADIO2, m_blue);
}


BEGIN_MESSAGE_MAP(CFormatDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CFormatDlg::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_EDIT_CONTROL, &CFormatDlg::OnEnChangeEditControl)
	ON_BN_CLICKED(IDCANCEL, &CFormatDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO3, &CFormatDlg::OnBnClickedRadioGreen)
	ON_BN_CLICKED(IDC_RADIO2, &CFormatDlg::OnBnClickedRadioBlue)
	ON_BN_CLICKED(IDC_RADIO1, &CFormatDlg::OnBnClickedRadioRed)
//	ON_BN_KILLFOCUS(IDC_RADIO2, &CFormatDlg::OnBnKillfocusRadio2)
	ON_EN_KILLFOCUS(IDC_EDIT_CONTROL, &CFormatDlg::OnEnKillfocusEditControl)
//	ON_BN_SETFOCUS(IDC_RADIO2, &CFormatDlg::OnBnSetfocusRadio2)
//	ON_BN_KILLFOCUS(IDC_RADIO2, &CFormatDlg::OnBnKillfocusRadio2)
END_MESSAGE_MAP()


// Обработчики сообщений CFormatDlg


void CFormatDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


//void CFormatDlg::OnEnChangeEditControl()
//{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
//}


void CFormatDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}


void CFormatDlg::OnBnClickedRadioGreen()
{
	m_lineColor = RGB(0, 255, 0);
	m_editCtrl.EnableWindow(1);
	// TODO: добавьте свой код обработчика уведомлений
}


void CFormatDlg::OnBnClickedRadioBlue()
{
	m_lineColor = RGB(0, 0, 255);
	m_editCtrl.EnableWindow(0);
	// TODO: добавьте свой код обработчика уведомлений
}


void CFormatDlg::OnBnClickedRadioRed()
{
	m_lineColor = RGB(255, 0, 0);
	m_editCtrl.EnableWindow(1);
	// TODO: добавьте свой код обработчика уведомлений
}

void CFormatDlg::OnEnKillfocusEditControl()
{
	UpdateData(1);
	if (m_width > 3)
		m_width = 3;
	if (m_width < 1)
		m_width = 1;
	UpdateData(0);
	// TODO: Add your control notification handler code here
}


//void CFormatDlg::OnBnSetfocusRadio2()
//{
//	/*m_editCtrl.ShowWindow(SW_HIDE);*/
	//m_editCtrl.EnableWindow(0);
	// TODO: Add your control notification handler code here
//}


//void CFormatDlg::OnBnKillfocusRadio2()
//{
//	/*m_editCtrl.ShowWindow(SW_SHOW);*/
//	/*if (m_blue.GetCheck() == BST_CHECKED) {
//		m_editCtrl.EnableWindow(TRUE);
//	}
//	else {
//		m_editCtrl.EnableWindow(FALSE);
//	}*/
	//m_editCtrl.EnableWindow(1);
	// TODO: Add your control notification handler code here
//}
