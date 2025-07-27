#pragma once
#include "afxdialogex.h"
#include"Model.h"

// PLevelDlg dialog

/// <summary>
/// Диалог для 2-ой задачи: распределение p-levels против альтернативы.
/// </summary>
class PLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PLevelDlg)

public:
	PLevelDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PLevelDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_PLEVEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// Белые шарики H1
	/// </summary>
	int pl_h1_whball;
	/// <summary>
	/// Чёрные шарики H1
	/// </summary>
	int pl_h1_blball;
	/// <summary>
	/// Число вытаскиваний H1
	/// </summary>
	int pl_h1_picknum;
	/// <summary>
	/// Число вытаскиваний H0
	/// </summary>
	int pl_h0_picknum;
	/// <summary>
	/// Чёрные шарики H0
	/// </summary>
	int pl_h0_blball;
	/// <summary>
	/// Белые шарики H0
	/// </summary>
	int pl_h0_whball;
	/// <summary>
	/// Объём выборки
	/// </summary>
	int pl_samvol;
	/// <summary>
	/// Число повторений
	/// </summary>
	int pl_repnum;
	/// <summary>
	/// Метод моделирования
	/// </summary>
	Method pl_method;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusPlH0Picknum();
};
