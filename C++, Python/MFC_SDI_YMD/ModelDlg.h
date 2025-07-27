#pragma once
#include "afxdialogex.h"

enum Method { BD = 0, IF = 1 };

// ModelDlg dialog

class ModelDlg : public CDialog
{
	DECLARE_DYNAMIC(ModelDlg)

public:
	ModelDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ModelDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_MODEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP();
public:
	int whBalls;
	int blBalls;
	int pickNum;
	int samVol;
	Method method;
	afx_msg void OnBnClickedInvmet();
	afx_msg void OnBnClickedOk();
};