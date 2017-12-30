
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
		}
		else {
			MessageBox("Wrong username or password!!! Try again!");
			return;
		}
	}

	if (package_mess == "ready to receive file?") {
		m_Client.check_upfile_rec == TRUE;
		char send_text[1000];
		CString temp = "yesiam";
		wsprintf(send_text, "%s", temp.GetString());
		// TODO: Add your control notification handler code here
		m_Client.Send(&send_text, strlen(send_text), 0);
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
		GetFileFromRemoteSender("./save");
		check_upfile_rec = FALSE;
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
	CSocket::OnReceive(nErrorCode);
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
		SendFileToRemoteRecipient(fName);
	}
}

BOOL CChatClientDlgDlg::SendFileToRemoteRecipient(CString fName) {
	// return value
	BOOL bRet = TRUE;
	int fileLength, cbLeftToSend;
	BYTE* sendData = NULL;
	CFile sourceFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;

	if (!(bFileIsOpen = sourceFile.Open(fName,
		CFile::modeRead | CFile::typeBinary, &fe)))
	{
		TCHAR strCause[256];
		fe.GetErrorMessage(strCause, 255);
		TRACE("SendFileToRemoteRecipient encountered an error while opening the local file\n \tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError);

		/* you should handle the error here */

		bRet = FALSE;
		goto PreReturnCleanup;
	}

	// first send length of file

	fileLength = sourceFile.GetLength();
	fileLength = htonl(fileLength);

	cbLeftToSend = sizeof(fileLength);

	do
	{
		int cbBytesSent;
		BYTE* bp = (BYTE*)(&fileLength) + sizeof(fileLength) - cbLeftToSend;
		cbBytesSent = m_Client.Send(bp, cbLeftToSend);

		// test for errors and get out if they occurred
		if (cbBytesSent == SOCKET_ERROR)
		{
			int iErr = ::GetLastError();
			TRACE("SendFileToRemoteRecipient returned a socket error while sending file length\n \tNumber of Bytes sent = %d\n \tGetLastError = %d\n", cbBytesSent, iErr);

			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}

		// data was successfully sent, so account
		// for it with already-sent data
		cbLeftToSend -= cbBytesSent;
	} while (cbLeftToSend>0);

	// now send the file's data    
	sendData = new BYTE[SEND_BUFFER_SIZE];

	cbLeftToSend = sourceFile.GetLength();

	do
	{
		// read next chunk of SEND_BUFFER_SIZE bytes from file

		int sendThisTime, doneSoFar, buffOffset;

		sendThisTime = sourceFile.Read(sendData, SEND_BUFFER_SIZE);
		buffOffset = 0;

		do
		{
			doneSoFar = m_Client.Send(sendData + buffOffset,
				sendThisTime);

			// test for errors and get out if they occurred
			if (doneSoFar == SOCKET_ERROR)
			{
				int iErr = ::GetLastError();
				TRACE("SendFileToRemoteRecipient returned a socket error while sending chunked file data\n"	"\tNumber of Bytes sent = %d\n"	"\tGetLastError = %d\n", doneSoFar, iErr);

				/* you should handle the error here */

				bRet = FALSE;
				goto PreReturnCleanup;
			}

			// data was successfully sent,
			// so account for it with already-sent data

			buffOffset += doneSoFar;
			sendThisTime -= doneSoFar;
			cbLeftToSend -= doneSoFar;
		} while (sendThisTime > 0);

	} while (cbLeftToSend > 0);

PreReturnCleanup: // labelled goto destination

				  // free allocated memory
				  // if we got here from a goto that skipped allocation,
				  // delete of NULL pointer
				  // is permissible under C++ standard and is harmless
	delete[] sendData;

	if (bFileIsOpen)
		sourceFile.Close();
	// only close file if it's open (open might have failed above)

	return bRet;
}

BOOL ClientSocket::GetFileFromRemoteSender(CString fName) {
	BOOL bRet = TRUE; // return value
					  // used to monitor the progress of a receive operation
	int dataLength, cbBytesRet, cbLeftToReceive;
	// pointer to buffer for receiving data
	// (memory is allocated after obtaining file size)
	BYTE* recdData = NULL;

	CFile destFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;

	if (!(bFileIsOpen = destFile.Open(fName, CFile::modeCreate |
		CFile::modeWrite | CFile::typeBinary, &fe)))
	{
		TCHAR strCause[256];
		fe.GetErrorMessage(strCause, 255);
		TRACE("GetFileFromRemoteSender encountered an error while opening the local file\n"	"\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError);

		/* you should handle the error here */

		bRet = FALSE;
		goto PreReturnCleanup;
	}

	// get the file's size first
	cbLeftToReceive = sizeof(dataLength);

	do
	{
		BYTE* bp = (BYTE*)(&dataLength) + sizeof(dataLength) - cbLeftToReceive;
		cbBytesRet = Receive(bp, cbLeftToReceive);

		// test for errors and get out if they occurred
		if (cbBytesRet == SOCKET_ERROR || cbBytesRet == 0)
		{
			int iErr = ::GetLastError();
			TRACE("GetFileFromRemoteSite returned a socket error while getting file length\n""\tNumber of Bytes received (zero means connection was closed) = %d\n""\tGetLastError = %d\n", cbBytesRet, iErr);

			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}

		// good data was retrieved, so accumulate
		// it with already-received data
		cbLeftToReceive -= cbBytesRet;

	} while (cbLeftToReceive > 0);

	dataLength = ntohl(dataLength);

	// now get the file in RECV_BUFFER_SIZE chunks at a time

	recdData = new byte[RECV_BUFFER_SIZE];
	cbLeftToReceive = dataLength;

	do
	{
		int iiGet, iiRecd;

		iiGet = (cbLeftToReceive<RECV_BUFFER_SIZE) ?
			cbLeftToReceive : RECV_BUFFER_SIZE;
		iiRecd = Receive(recdData, iiGet);

		// test for errors and get out if they occurred
		if (iiRecd == SOCKET_ERROR || iiRecd == 0)
		{
			int iErr = ::GetLastError();
			TRACE("GetFileFromRemoteSite returned a socket error while getting chunked file data\n"	"\tNumber of Bytes received (zero means connection was closed) = %d\n""\tGetLastError = %d\n", iiRecd, iErr);

			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}

		// good data was retrieved, so accumulate
		// it with already-received data

		destFile.Write(recdData, iiRecd); // Write it
		cbLeftToReceive -= iiRecd;

	} while (cbLeftToReceive > 0);

PreReturnCleanup: // labelled "goto" destination

				  // free allocated memory
				  // if we got here from a goto that skipped allocation,
				  // delete of NULL pointer
				  // is permissible under C++ standard and is harmless
	delete[] recdData;

	if (bFileIsOpen)
		destFile.Close();
	// only close file if it's open (open might have failed above)

	return bRet;
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
