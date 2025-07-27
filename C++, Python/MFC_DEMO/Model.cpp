// ModelDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_DEMO.h"
#include "afxdialogex.h"
#include "Model.h"


// ModelDlg dialog

IMPLEMENT_DYNAMIC(ModelDlg, CDialog)

ModelDlg::ModelDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(ID_MODEL, pParent)
	, whBalls(20)
	, blBalls(30)
	, pickNum(10)
	, samVol(100)
	, method(BD)
{

}

ModelDlg::~ModelDlg()
{
}

void ModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WHBALL, whBalls);
	DDX_Text(pDX, IDC_BLBALL, blBalls);
	DDX_Text(pDX, IDC_PICKNUM, pickNum);
	DDX_Text(pDX, IDC_SAMVOL, samVol);
	DDX_Radio(pDX, IDC_INVMET, (int&)method);
}


BEGIN_MESSAGE_MAP(ModelDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ModelDlg message handlers

/// <summary>
/// Проверка при нажатии на кнопку ОК
/// </summary>
void ModelDlg::OnBnClickedOk()
{
	UpdateData(1);
	BOOL condVol, condBl, condWh, condPick;
	condVol = samVol >= 5 && samVol <= 100000;
	condBl = blBalls > 0;
	condWh = whBalls > 0;
	condPick = pickNum > 0 && pickNum <= whBalls && pickNum <= blBalls;
	UpdateData(0);
	if (condVol && condBl && condWh && condPick) {
		CDialog::OnOK();
	}
	else {
		if (!condVol) {
			AfxMessageBox(L"Объём выборки должен быть в пределах:\nот 5 до 100000");
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
	}
}
