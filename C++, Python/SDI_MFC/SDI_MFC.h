
// SDI_MFC.h: основной файл заголовка для приложения SDI_MFC
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSDIMFCApp:
// Сведения о реализации этого класса: SDI_MFC.cpp
//

class CSDIMFCApp : public CWinAppEx
{
public:
	CSDIMFCApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDIMFCApp theApp;
