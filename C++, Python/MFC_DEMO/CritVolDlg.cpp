// CritVolDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_DEMO.h"
#include "afxdialogex.h"
#include "CritVolDlg.h"


// CritVolDlg dialog

IMPLEMENT_DYNAMIC(CritVolDlg, CDialogEx)

CritVolDlg::CritVolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_CRITVOL, pParent)
	, cv_h0_whball(20)
	, cv_h0_blball(30)
	, cv_h0_picknum(10)
	, cv_h1_picknum(10)
	, cv_h1_blball(30)
	, cv_h1_whball(20)
	, cv_from_sv(100)
	, cv_interval_sv(100)
	//cv_to_sv(1000)
	, cv_slvl(0.05)
	, cv_repnum(500)
	, critnum(10)
{

}

CritVolDlg::~CritVolDlg()
{
}

void CritVolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CV_FROM_SV, cv_from_sv);
	DDX_Text(pDX, IDC_CV_INTRVL_SV, cv_interval_sv);
	DDX_Text(pDX, IDC_CV_SLVL, cv_slvl);
	DDX_Text(pDX, IDC_CV_H1_PICKNUM, cv_h1_picknum);
	DDX_Text(pDX, IDC_CV_H1_BLBALL, cv_h1_blball);
	DDX_Text(pDX, IDC_CV_H1_WHBALL, cv_h1_whball);
	DDX_Text(pDX, IDC_CV_H0_PICKNUM, cv_h0_picknum);
	DDX_Text(pDX, IDC_CV_H0_BLBALL, cv_h0_blball);
	DDX_Text(pDX, IDC_CV_H0_WHBALL, cv_h0_whball);
	DDX_Radio(pDX, IDC_CV_INV, (int&)cv_method);
	DDX_Text(pDX, IDC_CV_REPNUM, cv_repnum);
	DDX_Text(pDX, IDC_CV_CRITNUM_SV, critnum);
}


BEGIN_MESSAGE_MAP(CritVolDlg, CDialogEx)
//	ON_EN_CHANGE(IDC_CV_H0_PICKNUM, &CritVolDlg::OnEnChangeCvH0Picknum)
	ON_BN_CLICKED(IDOK, &CritVolDlg::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_CV_H0_PICKNUM, &CritVolDlg::OnEnKillfocusCvH0Picknum)
END_MESSAGE_MAP()


// CritVolDlg message handlers

/// <summary>
/// Сохраняет соответствие между числом вытаскиваний H1
/// и числом вытаскиваний H0
/// </summary>
//void CritVolDlg::OnEnChangeCvH0Picknum()
//{
//	UpdateData(1);
//	cv_h1_picknum = cv_h0_picknum;
//	UpdateData(0);
//}

/// <summary>
/// Проверка при нажатии на кнопку ОК.
/// </summary>
void CritVolDlg::OnBnClickedOk()
{
	UpdateData(1);
	BOOL condVol, condIntrv, condBl, condWh, condPick, condSLvl;
	condVol = cv_from_sv >= 5 && cv_from_sv <= 100000 && cv_interval_sv >= 10 && cv_interval_sv <= 10000;
	condIntrv = critnum >= 5 && critnum <= 50;
	// condRepnum = cv_repnum >= 300 && cv_repnum <= 3000;
	condBl = cv_h0_blball > 0 && cv_h1_blball > 0;
	condWh = cv_h0_whball > 0 && cv_h1_whball > 0;
	condPick = cv_h0_picknum > 0 && cv_h0_picknum <= cv_h0_whball && cv_h0_picknum <= cv_h0_blball &&
		cv_h1_picknum > 0 && cv_h1_picknum <= cv_h1_whball && cv_h1_picknum <= cv_h1_blball;
	condSLvl = 0 < cv_slvl && cv_slvl < 1;
	UpdateData(0);
	if (condVol && condBl && condWh && condPick && condIntrv && condSLvl) {
		CDialog::OnOK();
	}
	else {
		if (!condVol) {
			AfxMessageBox(L"Объём выборки должен быть в пределах:\nот 5 до 100000\nИнтервал от 10 до 10000");
		}
		if (!condBl) {
			AfxMessageBox(L"Чёрных шариков должно быть > 0");
		}
		if (!condWh) {
			AfxMessageBox(L"Белых шариков должно быть > 0");
		}
		if (!condPick) {
			AfxMessageBox(L"Число вытаскиваний должно быть > 0 и\nона не должна превосходить числа белых и чёрных шариков");
		}
		if (!condIntrv) {
			AfxMessageBox(L"Число интервалов должно быть от 5 до 50");
		}
		if (!condSLvl) {
			AfxMessageBox(L"Уровень значимости должен быть в диапазоне\nот 0 до 1");
		}
		/*if (!condRepnum) {
			AfxMessageBox(L"Размер выборки должен быть в пределах от 300 до 3000");
		}*/
	}
	// TODO: Add your control notification handler code here
}

/// <summary>
/// Сохраняет соответствие между числом вытаскиваний H1
/// и числом вытаскиваний H0
/// </summary>
void CritVolDlg::OnEnKillfocusCvH0Picknum()
{
	UpdateData(1);
	cv_h1_picknum = cv_h0_picknum;
	UpdateData(0);
}
