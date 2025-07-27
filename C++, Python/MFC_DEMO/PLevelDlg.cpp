// PLevelDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_DEMO.h"
#include "afxdialogex.h"
#include "PLevelDlg.h"


// PLevelDlg dialog

IMPLEMENT_DYNAMIC(PLevelDlg, CDialogEx)

PLevelDlg::PLevelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_PLEVEL, pParent)
	, pl_h1_whball(23)
	, pl_h1_blball(31)
	, pl_h1_picknum(10)
	, pl_h0_picknum(10)
	, pl_h0_blball(30)
	, pl_h0_whball(20)
	, pl_samvol(100)
	, pl_repnum(500)
	, pl_method(BD)
{

}

PLevelDlg::~PLevelDlg()
{
}

void PLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PL_H1_WHBALL, pl_h1_whball);
	DDX_Text(pDX, IDC_PL_H1_BLBALL, pl_h1_blball);
	DDX_Text(pDX, IDC_PL_H1_PICKNUM, pl_h1_picknum);
	DDX_Text(pDX, IDC_PL_H0_PICKNUM, pl_h0_picknum);
	DDX_Text(pDX, IDC_PL_H0_BLBALL, pl_h0_blball);
	DDX_Text(pDX, IDC_PL_H0_WHBALL, pl_h0_whball);
	DDX_Text(pDX, IDC_PL_SAMVOL, pl_samvol);
	DDX_Text(pDX, IDC_PL_REPNUM, pl_repnum);
	DDX_Radio(pDX, IDC_PL_INV, (int&)pl_method);
}


BEGIN_MESSAGE_MAP(PLevelDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PLevelDlg::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_PL_H0_PICKNUM, &PLevelDlg::OnEnChangePlH0Picknum)
	ON_EN_KILLFOCUS(IDC_PL_H0_PICKNUM, &PLevelDlg::OnEnKillfocusPlH0Picknum)
END_MESSAGE_MAP()


// PLevelDlg message handlers

/// <summary>
/// Проверка при нажатии на кнопку ОК
/// </summary>
void PLevelDlg::OnBnClickedOk()
{
	UpdateData(1);
	BOOL condVol, condRep, condPick, condWh, condBl;
	condVol = pl_samvol >= 5 && pl_samvol <= 100000;
	condRep = pl_repnum >= 200 && pl_repnum <= 10000;
	condWh = pl_h0_whball > 0 && pl_h1_whball > 0;
	condBl = pl_h0_blball > 0 && pl_h1_blball > 0;
	condPick = pl_h0_picknum > 0 && pl_h0_picknum <= pl_h0_whball && pl_h0_picknum <= pl_h0_blball &&
		pl_h1_picknum > 0 && pl_h1_picknum <= pl_h1_whball && pl_h1_picknum <= pl_h1_blball;
	UpdateData(0);


	// TODO: Add your control notification handler code here
	if (condVol && condRep && condPick && condWh && condBl) {
		CDialogEx::OnOK();
	}
	else {
		if (!condVol) {
			AfxMessageBox(L"Объём выборки должен быть в пределах:\nот 5 до 100000");
		}
		if (!condRep) {
			AfxMessageBox(L"Число повторов должно быть в пределах:\nот 200 до 10000");
		}
		if (!condBl) {
			AfxMessageBox(L"Чёрных шариков должно быть > 0");
		}
		if (!condWh) {
			AfxMessageBox(L"Белых шариков должно быть > 0");
		}
		if (!condPick) {
			AfxMessageBox(L"Число вытаскиваний должно быть > 0 и\nона не должна превосходить числа белых и чёрных шариков как в H0, так и в H1");
		}
	}
}


//void PLevelDlg::OnEnChangePlH0Picknum()
//{
//	UpdateData(1);
//	pl_h1_picknum = pl_h0_picknum;
//	UpdateData(0);
//}

/// <summary>
/// Сохраняет соответствие между числом вытаскиваний H1
/// и числом вытаскиваний H0
/// </summary>
void PLevelDlg::OnEnKillfocusPlH0Picknum()
{
	UpdateData(1);
	pl_h1_picknum = pl_h0_picknum;
	UpdateData(0);
	// TODO: Add your control notification handler code here
}
