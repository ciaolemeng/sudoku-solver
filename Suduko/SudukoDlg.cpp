// SudukoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Suduko.h"
#include "SudukoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSudukoDlg dialog

CSudukoDlg::CSudukoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSudukoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSudukoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudukoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSudukoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSudukoDlg, CDialog)
	//{{AFX_MSG_MAP(CSudukoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCALC, OnCalc)
	ON_BN_CLICKED(IDCBACK, OnCback)
	ON_BN_CLICKED(IDCCLEAR, OnCclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSudukoDlg message handlers

BOOL CSudukoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	memset(m_nVals,0,sizeof(m_nVals));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSudukoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSudukoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudukoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSudukoDlg::ReadFixVal()
{
	int i,len;
	CWnd *pwnd;
	char szVal[128];

	for (i=0;i<81;i++)
	{
		m_nVals[i]=-1;
		pwnd=GetDlgItem(IDC_EDIT1+i);
		len=GetDlgItemText(IDC_EDIT1+i,szVal,128);
		if (len==0)
		{
			continue;
		}

		szVal[len]=0;
		len=atol(szVal);
		if (len<1||len>9)
		{
			sprintf(szVal,"%d行 %d列 非法值%d",i/9,i%9,len);
			AfxMessageBox(szVal);
			return FALSE;
		}
		m_nVals[i]=len;
		m_slvr.FixVal(i/9,i%9,len-1);
	}

	return TRUE;
}

void CSudukoDlg::OnCalc() 
{
	// TODO: Add your control notification handler code here
	if (!ReadFixVal())
	{
		return;
	}

	CWnd *pwnd=GetDlgItem(IDCALC);
	pwnd->EnableWindow(FALSE);
	pwnd=GetDlgItem(IDCBACK);
	pwnd->EnableWindow(TRUE);

	int i;
	char szVal[128];
	BOOL b=m_slvr.FindRslt();

	if (b)
	{
		for (i=0;i<81;i++)
		{
			sprintf(szVal,"%d",m_slvr.GetPosVal(i)+1);
			SetDlgItemText(IDC_EDIT1+i,szVal);
		}
		sprintf(szVal,"计算用时：%.3f秒",m_slvr.GetCalcTime());
	} 
	else
	{
		sprintf(szVal,"此题无解");
	}

	m_slvr.Reset();
	SetDlgItemText(IDC_STATIME,szVal);
}

void CSudukoDlg::OnCback() 
{
	// TODO: Add your control notification handler code here
	int i,n;
	char szVal[128];
	for (i=0;i<81;i++)
	{
		n=m_nVals[i];
		if (n>0&&n<10)
		{
			sprintf(szVal,"%d",n);
			SetDlgItemText(IDC_EDIT1+i,szVal);
		}
		else
		{
			SetDlgItemText(IDC_EDIT1+i,"");
		}
	}
	
	CWnd *pwnd=GetDlgItem(IDCALC);
	pwnd->EnableWindow(TRUE);
	pwnd=GetDlgItem(IDCBACK);
	pwnd->EnableWindow(FALSE);
}

void CSudukoDlg::OnCclear() 
{
	// TODO: Add your control notification handler code here
	int i;
	for (i=0;i<81;i++)
	{
		SetDlgItemText(IDC_EDIT1+i,"");
	}
	m_slvr.Reset();

	CWnd *pwnd=GetDlgItem(IDCALC);
	pwnd->EnableWindow(TRUE);
	pwnd=GetDlgItem(IDCBACK);
	pwnd->EnableWindow(TRUE);
}
