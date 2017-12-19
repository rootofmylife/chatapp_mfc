
// Chat_Server_GUIDlg.h : header file
//

#pragma once
//#include "ServerSocket.h"
#include "afxwin.h"
#include "afxsock.h"

struct MESS {
	char me[100];
};

CString m_msgArray = "";

class ClientSocket_2 : public CSocket
{
public:
	ClientSocket_2();
	~ClientSocket_2();
	CDialog * pDlg;
	void OnReceive(int nErrorCode);
};

class ServerSocket_2 : public CSocket
{
public:
	ServerSocket_2();
	~ServerSocket_2();
	CDialog * pDlg;
	ClientSocket_2 m_sktClient;
	void OnAccept(int nErrorCode);
};

// CChatServerGUIDlg dialog
class CChatServerGUIDlg : public CDialog
{
// Construction
public:
	CChatServerGUIDlg(CWnd* pParent = NULL);	// standard constructor
	ServerSocket_2 m_Server;
	void AddMsg(CString mess);
	void Accept();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_SERVER_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString send_box;
	//CSocket server, client;
	afx_msg void OnBnClickedSendbtn();
	CButton send_btn;
	CEdit messbox_readonly;
	afx_msg void OnBnClickedStart();
	CButton start_btn;
	CButton stop_btn;
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedOkbtn();
	CButton btn_ok;
	CButton btn_cal;
	afx_msg void OnBnClickedCanbtn();
	afx_msg void OnOK();
	//afx_msg void OnCancel();
	void updatemessbox(CString t);
};



