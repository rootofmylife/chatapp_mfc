
// Chat_Client_Dlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChatClientDlgApp:
// See Chat_Client_Dlg.cpp for the implementation of this class
//

class CChatClientDlgApp : public CWinApp
{
public:
	CChatClientDlgApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChatClientDlgApp theApp;
