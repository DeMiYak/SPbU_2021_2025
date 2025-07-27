
// MFC_SDI_YMD.h : main header file for the MFC_SDI_YMD application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCSDIYMDApp:
// See MFC_SDI_YMD.cpp for the implementation of this class
//

class CMFCSDIYMDApp : public CWinAppEx
{
public:
	CMFCSDIYMDApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCSDIYMDApp theApp;
