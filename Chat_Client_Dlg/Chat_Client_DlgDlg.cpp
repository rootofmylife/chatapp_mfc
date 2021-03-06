
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
	DDX_Control(pDX, IDC_BUTTON2, sendBTN);
	DDX_Control(pDX, IDC_UPLOAD, uploadBTN);
	DDX_Control(pDX, IDC_LOGIN, loginBTN);
	DDX_Control(pDX, IDC_REG, regBTN);
	DDX_Control(pDX, IDC_IMG, m_Picture);
}

BEGIN_MESSAGE_MAP(CChatClientDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CChatClientDlgDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_STOP, &CChatClientDlgDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatClientDlgDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_LOGIN, &CChatClientDlgDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_UPLOAD, &CChatClientDlgDlg::OnBnClickedUpload)
	ON_BN_CLICKED(IDC_REG, &CChatClientDlgDlg::OnBnClickedReg)
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
	loginBTN.EnableWindow(1);
	regBTN.EnableWindow(1);
}

void CChatClientDlgDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	m_Client.ShutDown(2);
	m_Client.Close();
	btn_cnt.EnableWindow(1);
	btn_stop.EnableWindow(0);
	loginBTN.EnableWindow(1);
	regBTN.EnableWindow(1);
	check_if_disable = 0;
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

	if (package_mess == "please use other account and password...") {
		MessageBox(package_mess);
		return;
	}
	else if (package_mess == "Register successfully!!!") {
		MessageBox(package_mess);
		return;
	}

	//if (sendBTN.EnableWindow(0) != TRUE && uploadBTN.EnableWindow(0) != TRUE) {
	if(check_if_disable == 0) {
		check_if_disable = 1;
		if (package_mess == "connect successfully, enjoy!!!!!") {
			sendBTN.EnableWindow(1);
			uploadBTN.EnableWindow(1);
			regBTN.EnableWindow(1);
			check_upfile_rec = FALSE;
		}
		else {
			MessageBox("Wrong username or password!!! Try again!");
			return;
		}
	}

	if (package_mess == "file?") {
		check_upfile_rec == TRUE;
		//char send_text[1000];
		//CString temp = "yesiam";
		//wsprintf(send_text, "%s", temp.GetString());
		//m_Client.Send(&send_text, strlen(send_text), 0);
		return;
	}

	MessageBeep(0x00000000L);
	
	listChat.AddString(_T("Server: ") + package_mess);

}

void CChatClientDlgDlg::OnOK() {
	// prevent press Enter and close the dialog
		
}

void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	if (check_upfile_rec == TRUE) {
		char name[256];
		int ter = Receive((char*)&name, 256, 0);
		name[ter] = '\0';
		CString localfile(name);

		AfxMessageBox("im heere");

		char GotFileSize[1024];
		Receive(GotFileSize, 1024, 0);
		long FileSize = atoi(GotFileSize);
		long SizeCheck = 0;
		FILE *fp = fopen(localfile, "w");
		char* mfcc;
		mfcc = (char*)malloc(FileSize + 1);
		while (SizeCheck < FileSize) {
			int Received = Receive(mfcc, FileSize, 0);
			int Written = fwrite(mfcc, sizeof(char), Received, fp);
			SizeCheck += Written;
			for (int i = 0; i < Written; i++) {
				if (mfcc[i] == '\n') {
					SizeCheck += 1;
				}
			}
		}
		fclose(fp);
		free(mfcc);
		check_upfile_rec == FALSE;
		return;
	}

	char buff[100];
	int nRead;
	nRead = Receive((char*)&buff, 100, 0);
	buff[nRead] = '\0';
	CString szTemp(buff);
	MESS *temp;
	temp = (MESS*)buff;
	((CChatClientDlgDlg*)pDlg)->AddMsg(temp);
	//CSocket::OnReceive(nErrorCode);
}

void CChatClientDlgDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	//Gui thong tin client
	char uspwtext[1000];
	CString us, pw, uspw;
	GetDlgItemText(IDC_USER, us);
	GetDlgItemText(IDC_PASS, pw);
	uspw = us + pw;
	wsprintf(uspwtext, "%s", uspw.GetString());
	m_Client.Send(&uspwtext, strlen(uspwtext), 0);
	loginBTN.EnableWindow(0);
	regBTN.EnableWindow(0);
}

void CChatClientDlgDlg::OnBnClickedUpload()
{
	// TODO: Add your control notification handler code here
	CFileDialog filedir(TRUE);
	CString fName;
	if (filedir.DoModal() == IDOK) {
		listChat.AddString(_T("User: ") + filedir.GetPathName());
		fName = filedir.GetPathName();

		CImage img;
		img.Load(fName);
		int dimx = 150, dimy = 150;

		CDC *screenDC = GetDC();
		CDC mDC;
		mDC.CreateCompatibleDC(screenDC);
		CBitmap b;
		b.CreateCompatibleBitmap(screenDC, dimx, dimy);

		CBitmap *pob = mDC.SelectObject(&b);
		mDC.SetStretchBltMode(HALFTONE);
		img.StretchBlt(mDC.m_hDC, 0, 0, dimx, dimy, 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY);
		mDC.SelectObject(pob);

		m_Picture.SetBitmap((HBITMAP)b.Detach());
		ReleaseDC(screenDC);

		// send file

		FILE *fp = fopen(fName, "r");
		fseek(fp, 0, SEEK_END);
		long FileSize = ftell(fp);
		char GotFileSize[1024];
		_itoa_s(FileSize, GotFileSize, 10);
		send(m_Client, GotFileSize, 1024, 0);
		rewind(fp);
		long SizeCheck = 0;
		char* mfcc;

		if (FileSize > 1499) {
			mfcc = (char*)malloc(1500);
			while (SizeCheck < FileSize) {
				int Read = fread_s(mfcc, 1500, sizeof(char), 1500, fp);
				int Sent = send(m_Client, mfcc, Read, 0);
				SizeCheck += Sent;
			}
		}
		else {
			mfcc = (char*)malloc(FileSize + 1);
			fread_s(mfcc, FileSize, sizeof(char), FileSize, fp);
			send(m_Client, mfcc, FileSize, 0);
		}
		fclose(fp);
		Sleep(500);
		free(mfcc);

		//SendFileToRemoteRecipient(fName);
	}
}

void CChatClientDlgDlg::OnBnClickedReg()
{
	// TODO: Add your control notification handler code here
	char uspwtext[1000];
	CString us, pw, uspw;
	GetDlgItemText(IDC_USER, us);
	GetDlgItemText(IDC_PASS, pw);
	uspw = "REG" + us + pw;
	wsprintf(uspwtext, "%s", uspw.GetString());
	m_Client.Send(&uspwtext, strlen(uspwtext), 0);
}
