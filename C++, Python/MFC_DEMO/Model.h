#pragma once
#include "afxdialogex.h"
#include"Method.h"
// ModelDlg dialog

/// <summary>
/// Диалог для 1-ой задачи: гистограмма эмпирических и теоретических частот
/// гипергеометрического распределения (двумя методами)
/// </summary>
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
	/// <summary>
	/// Белые шарики
	/// </summary>
	int whBalls;
	/// <summary>
	/// Чёрные шарики
	/// </summary>
	int blBalls;
	/// <summary>
	/// Число вытаскиваний
	/// </summary>
	int pickNum;
	/// <summary>
	/// Объём выборки
	/// </summary>
	int samVol;
	/// <summary>
	/// Метод моделирования
	/// </summary>
	Method method;
	afx_msg void OnBnClickedOk();
};
