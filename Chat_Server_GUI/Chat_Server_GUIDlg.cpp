
// Chat_Server_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat_Server_GUI.h"
#include "Chat_Server_GUIDlg.h"
#include "afxdialogex.h"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatServerGUIDlg dialog

ClientSocket_2::ClientSocket_2() {

}

ClientSocket_2::~ClientSocket_2() {

}

ServerSocket_2::ServerSocket_2() {

}

ServerSocket_2::~ServerSocket_2() {

}

CChatServerGUIDlg::CChatServerGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHAT_SERVER_GUI_DIALOG, pParent)
	, send_box(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND, send_box);
	DDX_Control(pDX, IDC_SENDBTN, send_btn);

	DDX_Control(pDX, IDC_OKBTN, btn_ok);
	DDX_Control(pDX, IDC_CANBTN, btn_cal);
	DDX_Control(pDX, IDC_LISTCHAT, listChat);
	DDX_Control(pDX, IDC_SEND, sendBox);
	DDX_Control(pDX, IDC_LOGINBTN, loginBTN);
	DDX_Control(pDX, IDC_REGBTN, regBTN);
	DDX_Control(pDX, IDC_UPBTN, upload_btn);
}

BEGIN_MESSAGE_MAP(CChatServerGUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SENDBTN, &CChatServerGUIDlg::OnBnClickedSendbtn)
	ON_BN_CLICKED(IDC_OKBTN, &CChatServerGUIDlg::OnBnClickedOkbtn)
	ON_BN_CLICKED(IDC_CANBTN, &CChatServerGUIDlg::OnBnClickedCanbtn)
	ON_BN_CLICKED(IDC_LOGINBTN, &CChatServerGUIDlg::OnBnClickedLoginbtn)
	ON_BN_CLICKED(IDC_REGBTN, &CChatServerGUIDlg::OnBnClickedRegbtn)
END_MESSAGE_MAP()


// CChatServerGUIDlg message handlers

BOOL CChatServerGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	///////////////////////////////////////

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

									// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatServerGUIDlg::OnPaint()
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
HCURSOR CChatServerGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatServerGUIDlg::OnBnClickedSendbtn()
{
	// TODO: Add your control notification handler code here
	char send_text[1000];
	CString temp;
	GetDlgItemText(IDC_SEND, temp); // Get text form send box
	sprintf(send_text, "%s", temp.GetString());

	listChat.AddString(_T("Server: ") + temp);

	m_Server.m_sktClient.Send(&send_text, strlen(send_text), 0);
	sendBox.SetWindowTextA(_T(""));
}

void CChatServerGUIDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	//CDialog::OnOK();

	//if (AfxSocketInit() == FALSE) {
	//	AfxMessageBox(_T("Sockets Could Not Be Initialized"));
	//	return;
	//}
	////m_Server.m_sktClient = this;
	//m_Server.Create(1234);

	//if (m_Server.Listen() == FALSE) {
	//	MessageBox(_T("Unable to Listen on that port, please try another port"));
	//	m_Server.Close();
	//	return;
	//}



	start_btn.EnableWindow(FALSE);
	stop_btn.EnableWindow(TRUE);

}

void CChatServerGUIDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	m_Server.m_sktClient.ShutDown(2);
	m_Server.Close();
	start_btn.EnableWindow(TRUE);
	stop_btn.EnableWindow(FALSE);
}

void CChatServerGUIDlg::OnBnClickedOkbtn()
{
	// TODO: Add your control notification handler code here

	if (AfxSocketInit() == FALSE) {
		AfxMessageBox(_T("Sockets Could Not Be Initialized"));
		return;
	}
	m_Server.m_sktClient.pDlg = this;
	m_Server.Create(1234);

	if (m_Server.Listen() == FALSE) {
		MessageBox(_T("Unable to Listen on that port, please try another port"));
		m_Server.Close();
		return;
	}
	btn_ok.EnableWindow(0);
	btn_cal.EnableWindow(1);
	//loginBTN.EnableWindow(1);
	//regBTN.EnableWindow(1);
	MessageBox(_T("Server connected..."));

	//LOGIN AND REG
	CString buff_str;
	myFile.Open(_T("data.txt"), CFile::modeRead);
	while (true) {
		if (myFile.ReadString(buff_str) != NULL) {
			info.Add(buff_str);
		}
		else {
			MessageBox("Done");
			break;
		}
	}
	myFile.Close();
}

void CChatServerGUIDlg::OnBnClickedCanbtn()
{
	// TODO: Add your control notification handler code here
	m_Server.m_sktClient.ShutDown(2);
	m_Server.Close();
	btn_ok.EnableWindow(1);
	btn_cal.EnableWindow(0);
	MessageBox(_T("Server closed..."));
}

void CChatServerGUIDlg::AddMsg(MESS* mess) {
	CString package_mess;
	package_mess.Format("%s", mess->me);

	//if (send_btn.EnableWindow(0) != TRUE && upload_btn.EnableWindow(0) != TRUE) {
	if (check_if_disable == 0) {
		check_if_disable = 1;
		for (int i = 0; i < info.GetSize(); i++) {
			if (info[i] == package_mess) {
				MessageBox(_T("Success..."));
				CString temp = "connect successfully, enjoy!!!!!";
				char send_text[1000];
				sprintf(send_text, "%s", temp.GetString());
				m_Server.m_sktClient.Send(&send_text, strlen(send_text), 0);
				send_btn.EnableWindow(1);
				upload_btn.EnableWindow(1);
				return;
			}
		}
	}
		
	
	MessageBeep(0x00000000L);
	listChat.AddString(_T("User: ") + package_mess);
}

void CChatServerGUIDlg::Accept()
{
	AfxMessageBox("Client Request Connection");
	if (m_Server.Accept(m_Server.m_sktClient))
		return;

}

void ClientSocket_2::OnReceive(int nErrorCode)
{
	char buff[100];
	int nRead;
	nRead = Receive((char*)&buff, 100, 0);
	buff[nRead] = '\0';
	CString szTemp(buff);
	MESS *temp;
	temp = (MESS*)buff;
	((CChatServerGUIDlg*)pDlg)->AddMsg(temp);
	CSocket::OnReceive(nErrorCode);
}

void ServerSocket_2::OnAccept(int nErrorCode)
{
	AfxMessageBox(_T("Client connected..."));
	Accept(m_sktClient);
	CSocket::OnAccept(nErrorCode);
}

void CChatServerGUIDlg::OnOK() {
	// Nothing inside to prevent the dialog from being closed when the ENTER key is pressed
}
/*
void CChatServerGUIDlg::OnCancel() {
// Nothing inside to prevent the dialog from being closed when the ESC key is pressed
}
*/


void CChatServerGUIDlg::OnBnClickedLoginbtn()
{
	// TODO: Add your control notification handler code here
	CString us;
	CString pw;
	int flag = 0;
	GetDlgItemText(IDC_USER, us);
	GetDlgItemText(IDC_PWD, pw);
	CString uspw = us + pw;
	for (int i = 0; i < info.GetSize(); i++) {
		if (info[i] == uspw) {
			flag = 1;
			MessageBox(_T("Success..."));
			break;
		}
	}
	if (flag == 0) {
		MessageBox(0, "Failed login! Try again");
		return;
	}
	loginBTN.EnableWindow(0);
	regBTN.EnableWindow(0);
	send_btn.EnableWindow(1);
	upload_btn.EnableWindow(1);
}


void CChatServerGUIDlg::OnBnClickedRegbtn()
{
	// TODO: Add your control notification handler code here
	CString us;
	CString pw;
	GetDlgItemText(IDC_USER, us);
	GetDlgItemText(IDC_PWD, pw);
	CString uspw = us + pw;
	for (int i = 0; i < info.GetSize(); i++) {
		if (info[i] == uspw) {
			MessageBox(_T("please use other account and password..."));
			return;
		}
	}

	info.Add(uspw);

	myFile.Open("data.txt", CFile::modeWrite);
	myFile.SeekToEnd();
	myFile.WriteString(uspw);
	myFile.WriteString(_T("\n"));
	myFile.Close();
	MessageBox("Register successfully!!!");
}
