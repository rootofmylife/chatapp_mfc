
// Chat_Client_DlgDlg.h : header file
//

#pragma once
#include "afxsock.h"
#include "afxwin.h"

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
	virtual void OnReceive(int nErrorCode);
};


// CChatClientDlgDlg dialog
class CChatClientDlgDlg : public CDialog
{
// Construction
public:
	CChatClientDlgDlg(CWnd* pParent = NULL);	// standard constructor
	ClientSocket m_Client;
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
};
