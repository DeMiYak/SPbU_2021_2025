#pragma once
#include "afxdialogex.h"
#include "Method.h"

// CritVolDlg dialog

/// <summary>
/// Диалог для 3-ей задачи: график зависимости мощности критерия от 
/// объёма выборки при заданных альтернативе и уровне значимости
/// </summary>
class CritVolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CritVolDlg)

public:
	CritVolDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CritVolDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_CRITVOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// Начальный объём выборки
	/// </summary>
	int cv_from_sv;
	/// <summary>
	/// Интервал между объёмами выборки
	/// </summary>
	int cv_interval_sv;
	/// <summary>
	/// Уровень значимости
	/// </summary>
	double cv_slvl;
	/// <summary>
	/// Число вытаскиваний H1
	/// </summary>
	int cv_h1_picknum;
	/// <summary>
	/// Чёрные шарики H1
	/// </summary>
	int cv_h1_blball;
	/// <summary>
	/// Белые шарики H1
	/// </summary>
	int cv_h1_whball;
	/// <summary>
	/// Число вытаскиваний H0
	/// </summary>
	int cv_h0_picknum;
	/// <summary>
	/// Чёрные шарики H0
	/// </summary>
	int cv_h0_blball;
	/// <summary>
	/// Белые шарики H0
	/// </summary>
	int cv_h0_whball;
	/// <summary>
	/// Метод моделирования H1
	/// </summary>
	Method cv_method;
//	afx_msg void OnEnChangeCvH0Picknum();
	afx_msg void OnBnClickedOk();
	/// <summary>
	/// Число повторов моделирования p-value
	/// </summary>
	int cv_repnum;
	/// <summary>
	/// Число вычислений мощностей критерия
	/// </summary>
	int critnum;
	afx_msg void OnEnKillfocusCvH0Picknum();
};
