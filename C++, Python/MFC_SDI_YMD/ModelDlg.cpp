// ModelDlg.cpp : implementation file
//

#include "pch.h"
#include "MFC_SDI_YMD.h"
#include "afxdialogex.h"
#include "ModelDlg.h"


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
	//ON_EN_CHANGE(IDC_SAMVOL, &ModelDlg::OnEnChangeSamvol)
	//ON_EN_KILLFOCUS(IDC_PICKNUM, &ModelDlg::OnEnKillfocusPicknum)
	//ON_EN_CHANGE(IDC_BLBALL, &ModelDlg::OnEnChangeBlball)
	//ON_EN_CHANGE(IDC_WHBALL, &ModelDlg::OnEnChangeWhball)
	ON_BN_CLICKED(IDC_INVMET, &ModelDlg::OnBnClickedInvmet)
	ON_BN_CLICKED(IDOK, &ModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ModelDlg message handlers


//void ModelDlg::OnEnChangeSamvol()
//{
//	UpdateData(1);
//	if (samVol < 50) {
//		samVol = 50;
//	}
//	if (samVol > 100000) {
//		samVol = 100000;
//	}
//	UpdateData(0);
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


//void ModelDlg::OnEnKillfocusPicknum()
//{
//	UpdateData(1);
//	if (pickNum < 1) {
//		pickNum = 1;
//	}
//	if (pickNum > min(whBalls, blBalls)) {
//		pickNum = min(whBalls, blBalls);
//	}
//	UpdateData(0);
//	// TODO: Add your control notification handler code here
//}

//
//void ModelDlg::OnEnChangeBlball()
//{
//	UpdateData(1);
//	if (blBalls < 1) {
//		blBalls = 1;
//	}
//	if (pickNum > blBalls) {
//		pickNum = blBalls;
//	}
//	UpdateData(0);
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


//void ModelDlg::OnEnChangeWhball()
//{
//	UpdateData(1);
//	if (whBalls < 1) {
//		whBalls = 1;
//	}
//	if (pickNum > whBalls) {
//		pickNum = whBalls;
//	}
//	UpdateData(0);
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


void ModelDlg::OnBnClickedInvmet()
{
	// TODO: Add your control notification handler code here
}


// Исправление 9
void ModelDlg::OnBnClickedOk()
{
	UpdateData(1);
	BOOL condVol, condBl, condWh, condPick;
	condVol = samVol >= 80 && samVol <= 100000;
	condBl = blBalls > 0;
	condWh = whBalls > 0;
	condPick = pickNum > 0 && pickNum <= whBalls;
	UpdateData(0);
	if (condVol && condBl && condWh && condPick) {
		CDialog::OnOK();
	}
	else {
		if (!condVol) {
			AfxMessageBox(L"Объём выборки должен быть в пределах:\nот 80 до 100000");
		}
		if (!condBl) {
			AfxMessageBox(L"Чёрных шариков должно быть > 0");
		}
		if (!condWh) {
			AfxMessageBox(L"Белых шариков должно быть > 0");
		}
		if (!condPick) {
			AfxMessageBox(L"Число вытаскиваний должно быть > 0 и\nона не должна превосходить числа белых шариков");
		}
	}
	// TODO: Add your control notification handler code here
}