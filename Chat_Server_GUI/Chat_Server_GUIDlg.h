
// Chat_Server_GUIDlg.h : header file
//

#pragma once
//#include "ServerSocket.h"
#include "afxwin.h"
#include "afxsock.h"
#include <atlimage.h>
#define SEND_BUFFER_SIZE    4096
#define RECV_BUFFER_SIZE    4096

struct MESS {
	char me[100];
};

class ClientSocket_2 : public CSocket
{
public:
	ClientSocket_2();
	~ClientSocket_2();
	CDialog * pDlg;
	bool check_upfile_rec = FALSE;
	bool check_upfile_sen = FALSE;
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
	CStringArray info;
	ServerSocket_2 m_Server;
	CStdioFile myFile;
	CString us_chatter_client;
	CString pw_chatter_client;
	int check_if_disable = 0;
	
	void AddMsg(MESS* mess);
	void Accept();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_SERVER_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnDraw(CDC* pDC);

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
	CButton btn_ok;
	CButton btn_cal;
	CListBox listChat;
	CButton send_btn;
	CEdit messbox_readonly;
	CButton start_btn;
	CButton stop_btn;
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedOkbtn();
	afx_msg void OnBnClickedCanbtn();
	afx_msg void OnBnClickedSendbtn();
	afx_msg void OnBnClickedStart();
	afx_msg void OnOK();
	//afx_msg void OnCancel();
	CEdit sendBox;
	afx_msg void OnBnClickedLoginbtn();
	afx_msg void OnBnClickedRegbtn();
	CButton loginBTN;
	CButton regBTN;
	CButton upload_btn;
	afx_msg void OnBnClickedUpbtn();
	CStatic m_Picture;
};



