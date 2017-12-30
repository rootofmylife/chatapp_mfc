
// Chat_Client_DlgDlg.h : header file
//

#pragma once
#include "afxsock.h"
#include "afxwin.h"
#define SEND_BUFFER_SIZE    4096
#define RECV_BUFFER_SIZE	4096
struct MESS {
	char me[100];
};

//CStringArray mes_temp;

class ClientSocket : public CSocket
{
public:
	ClientSocket();
	~ClientSocket();
	CDialog * pDlg;
	bool check_upfile_rec = FALSE;
	bool check_upfile_sen = FALSE;
	virtual void OnReceive(int nErrorCode);
	BOOL GetFileFromRemoteSender(CString fName);
};


// CChatClientDlgDlg dialog
class CChatClientDlgDlg : public CDialog
{
// Construction
public:
	CChatClientDlgDlg(CWnd* pParent = NULL);	// standard constructor
	ClientSocket m_Client;
	int check_if_disable = 0;
	void AddMsg(MESS* mess);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_CLIENT_DLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton btn_cnt;
	afx_msg void OnBnClickedConnect();
	CButton btn_stop;
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedButton2();
	CString send_box;
	CEdit messbox_readonly;
	afx_msg void OnOK();
	CListBox listChat;
	CEdit sendBox;
	afx_msg void OnBnClickedLogin();
	CButton sendBTN;
	CButton uploadBTN;
	CButton loginBTN;
	afx_msg void OnBnClickedUpload();
	BOOL SendFileToRemoteRecipient(CString fName);
	CButton regBTN;
	afx_msg void OnBnClickedReg();
};
