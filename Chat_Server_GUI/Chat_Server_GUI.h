
// Chat_Server_GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Chat_Server_GUIDlg.h"
// CChatServerGUIApp:
// See Chat_Server_GUI.cpp for the implementation of this class
//

class CChatServerGUIApp : public CWinApp
{
public:
	CChatServerGUIApp();
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChatServerGUIApp theApp;
