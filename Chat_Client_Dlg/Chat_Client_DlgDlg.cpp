
// Chat_Client_DlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat_Client_Dlg.h"
#include "Chat_Client_DlgDlg.h"
#include "afxdialogex.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ClientSocket::ClientSocket()
{
}


ClientSocket::~ClientSocket()
{
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatClientDlgDlg dialog



CChatClientDlgDlg::CChatClientDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHAT_CLIENT_DLG_DIALOG, pParent)
	, send_box(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONNECT, btn_cnt);
	DDX_Control(pDX, IDC_STOP, btn_stop);
	DDX_Text(pDX, IDC_SEND, send_box);
	DDX_Control(pDX, IDC_LISTCHAT, listChat);
	DDX_Control(pDX, IDC_SEND, sendBox);
}

BEGIN_MESSAGE_MAP(CChatClientDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CChatClientDlgDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_STOP, &CChatClientDlgDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatClientDlgDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatClientDlgDlg message handlers

BOOL CChatClientDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatClientDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatClientDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlgDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	if (AfxSocketInit() == FALSE)
	{
		AfxMessageBox("Failed to Initialize Sockets");
		return;
	}

	if (m_Client.Create() == FALSE)
	{
		MessageBox("Failed to Create Socket");
		return;

	}
	if (m_Client.Connect(_T("127.0.0.1"), 1234) == FALSE)
	{
		MessageBox("Failed to Connect");
		return;

	}
	m_Client.pDlg = this;
	btn_cnt.EnableWindow(0);
	btn_stop.EnableWindow(1);
}


void CChatClientDlgDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	m_Client.ShutDown(2);
	m_Client.Close();
	btn_cnt.EnableWindow(1);
	btn_stop.EnableWindow(0);
}


void CChatClientDlgDlg::OnBnClickedButton2()
{
	char send_text[1000];
	CString temp;
	GetDlgItemText(IDC_SEND, temp); // Get text form send box
	wsprintf(send_text, "%s", temp.GetString());
	listChat.AddString(_T("User: ") + temp);
	// TODO: Add your control notification handler code here
	m_Client.Send(&send_text, strlen(send_text), 0);
	sendBox.SetWindowTextA(_T(""));
}

void CChatClientDlgDlg::AddMsg(MESS* mess) {
	CString package_mess;
	package_mess.Format("%s", mess->me);
	listChat.AddString(_T("Server: ") + package_mess);
	//MessageBox(0, CString(temp_int));
	//MessageBox(0, "da nhan");
	//if (package_mess.IsEmpty() == FALSE)
	//messbox_readonly.SetWindowText(package_mess);
}

void CChatClientDlgDlg::OnOK() {
	// prevent press Enter and close the dialog
}

void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char buff[100];
	int nRead;
	nRead = Receive((char*)&buff, 100, 0);
	buff[nRead] = '\0';
	CString szTemp(buff);
	//MessageBox(0, szTemp, "Mess", 0);
	MESS *temp;
	temp = (MESS*)buff;
	((CChatClientDlgDlg*)pDlg)->AddMsg(temp);
	CSocket::OnReceive(nErrorCode);
}