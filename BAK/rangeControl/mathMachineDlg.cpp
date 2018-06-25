// mathMachineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mathMachine.h"
#include "mathMachineDlg.h"

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
// CMathMachineDlg dialog

CMathMachineDlg::CMathMachineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMathMachineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMathMachineDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathMachineDlg)
	DDX_Control(pDX, IDC_ENTER, m_bnEnter);
	DDX_Control(pDX, IDC_RESPONSE, m_editResponse);
	DDX_Control(pDX, IDC_RANGE, m_cbRange);
	DDX_Control(pDX, IDC_QUESTION, m_editQuestion);
	DDX_Control(pDX, IDC_OPERATION, m_cbOperation);
	DDX_Control(pDX, IDC_NUMBER, m_cbNumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMathMachineDlg, CDialog)
	//{{AFX_MSG_MAP(CMathMachineDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_NUMBER, OnSelchangeNumber)
	ON_CBN_SELCHANGE(IDC_OPERATION, OnSelchangeOperation)
	ON_CBN_SELCHANGE(IDC_RANGE, OnSelchangeRange)
	ON_BN_CLICKED(IDSTART, OnStart)
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathMachineDlg message handlers

void CMathMachineDlg::OnSysCommand( UINT nID, LPARAM lParam )
{
	if( (nID & 0xFFF0) == IDM_ABOUTBOX )
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		  CDialog::OnSysCommand( nID, lParam );
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CMathMachineDlg::OnPaint() 
{
	if( IsIconic() )
	{
		CPaintDC dc(this); // device context for painting

		SendMessage( WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0 );

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
		  CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display 
// while the user drags the minimized window.
HCURSOR CMathMachineDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

BOOL CMathMachineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if( pSysMenu != NULL )
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if( !strAboutMenu.IsEmpty() )
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);	 // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

//** MY INITS **

	m_boolInSession = false ;
	m_nResponseCount = 0 ;

	// Seed the random-number generator with current time
  srand( (unsigned)time( NULL ) );

	// init the status array
	mar_nResponseStatus[0] = RESP_DONT_DO_THIS ;
	for( int i=1; i<=MIN_RANGE; i++ )
		 mar_nResponseStatus[i] = RESP_DO_THIS ;
	for( int j=MIN_RANGE+1; j<=MAX_RANGE; j++ )
		 mar_nResponseStatus[j] = RESP_DONT_DO_THIS ;

	initFonts( 30, 50 );
	initCBs( 0, 0, 3 ); // set the Combo boxes to their default values

	return TRUE ; // return TRUE unless you set the focus to a control
}

void CMathMachineDlg::initFonts( int cbHeight, int editHeight )
{
	m_fontCombo.CreateFont( cbHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET,
													OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
													DEFAULT_PITCH | FF_ROMAN, "Times New Roman" );
	m_cbNumber.SetFont( &m_fontCombo );
	m_cbOperation.SetFont( &m_fontCombo );
	m_cbRange.SetFont( &m_fontCombo );

	m_fontEdit.CreateFont( editHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET,
												 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
												 DEFAULT_PITCH | FF_ROMAN, "Times New Roman" );
	m_editQuestion.SetFont( &m_fontEdit );
	m_editResponse.SetFont( &m_fontEdit );
}

void CMathMachineDlg::initCBs( int numIndex, int opIndex, int rangeIndex )
{
	m_cbNumber.SetCurSel( numIndex );
  m_cbNumber.GetLBText( numIndex, m_strSessionNumber );
	m_cbOperation.SetCurSel( opIndex );
  m_cbOperation.GetLBText( opIndex, m_strSessionOperation );
	m_cbRange.SetCurSel( rangeIndex );
  m_cbRange.GetLBText( rangeIndex, m_strSessionRange );
}

void CMathMachineDlg::OnSelchangeNumber() 
{
  // get the Session value
  int nIndex = m_cbNumber.GetCurSel();
  if( nIndex != CB_ERR )
  {
    m_cbNumber.GetLBText( nIndex, m_strSessionNumber );
//    CString numString = "OnSelchangeNumber is " + m_strSessionNumber ;
//    AfxMessageBox( numString );
    m_nSessionNumber = atoi( m_strSessionNumber );
  }
}

void CMathMachineDlg::OnSelchangeOperation() 
{
  // get the Session value
  int nIndex = m_cbOperation.GetCurSel();
  if( nIndex != CB_ERR )
  {
    m_cbOperation.GetLBText( nIndex, m_strSessionOperation );
//    CString opString = "OnSelchangeOperation is " + m_strSessionOperation ;
//    AfxMessageBox( opString );
  }
}

void CMathMachineDlg::OnSelchangeRange() 
{
  // get the Session value
  int nIndex = m_cbRange.GetCurSel();
  if( nIndex != CB_ERR )
  {
    m_cbRange.GetLBText( nIndex, m_strSessionRange );
//    CString rangeString = "OnSelchangeRange is " + m_strSessionRange ;
//    AfxMessageBox( rangeString );
    m_nSessionRange = atoi( m_strSessionRange );
  }
}

void CMathMachineDlg::OnStart() 
{
  if( m_boolInSession )
	{
    int response = AfxMessageBox( "Do you want to re-Start this session?", 3 );
		if( response == IDYES )
		{
			// re-start
			m_boolInSession = false ;
			OnStart();
		}
	}
	else
		{
		  m_boolInSession = true ;
			m_odtStart = COleDateTime::GetCurrentTime();
			m_nSessionRange = atoi( m_strSessionRange );
			for( int i=MIN_RANGE+1 ; i<=m_nSessionRange ; i++ )
				mar_nResponseStatus[i] = RESP_DO_THIS ;
			// NEED A DIFFERENT NUMBER OF EXPECTED RESPONSES OTHER THAN RANGE
			// IN THE CASE OF MINUS
			if( m_strSessionOperation == "-" )
			{
				if( m_nSessionNumber > m_nSessionRange/2 )
					m_nSessionNumber = m_nSessionRange/2 ;
				for( int j=1 ; j<=m_nSessionNumber ; j++ )
				  mar_nResponseStatus[j] = RESP_DONT_DO_THIS ;
			}
			displayQuestion();
		}
}

void CMathMachineDlg::OnEnter() 
{
	CString strEnter ;
  m_editResponse.GetWindowText( strEnter );
	m_nCurrentResponse = atoi( strEnter );
//	strEnter += " received by Enter." ;
//  AfxMessageBox( strEnter );

	processResponse();

	// see if we are finished the session
  if( m_nResponseCount < m_nSessionRange )
		displayQuestion();
	else
		  endSession();

  // clear the box
  m_editResponse.SetWindowText( "" );
}

void CMathMachineDlg::displayQuestion()
{
	CString strQuestion ;
	
	while( mar_nResponseStatus[m_nCurrentRhv = ((rand() % m_nSessionRange)+1)] != RESP_DO_THIS )
	{// try again
/*		m_nCurrentRhv = (rand() % m_nSessionRange) ;
		char s[MAX_RANGE] = {0}; 
		sprintf( s, "%d", m_nCurrentRhv );
		CString test = s ;
		test += " = m_nCurrentRhv" ;
		AfxMessageBox( test );
		if( mar_nResponseStatus[m_nCurrentRhv] == RESP_DO_THIS )
			AfxMessageBox( "mar_nResponseStatus[m_nCurrentRhv] == RESP_DO_THIS" );
		else
			  AfxMessageBox( "mar_nResponseStatus[m_nCurrentRhv] != RESP_DO_THIS" );
*/	}
	
	char s[MAX_RANGE] = {0};
	sprintf( s, "%d", m_nCurrentRhv );
	CString strRhv = s ;
	if( m_strSessionOperation == "-" )
		strQuestion = strRhv + m_strSessionOperation + m_strSessionNumber + " = " ;
	else
			strQuestion = m_strSessionNumber + m_strSessionOperation + strRhv + " = " ;

	m_editQuestion.SetWindowText( strQuestion );

	GotoDlgCtrl( GetDlgItem(IDC_RESPONSE) );
}

void CMathMachineDlg::processResponse()
{
	bool Ok = false ;

	switch( m_strSessionOperation[0] )
	{
		case '+' :
			if( m_nCurrentResponse == m_nSessionNumber + m_nCurrentRhv )
				Ok = true ;

		case '-' :
			if( m_nCurrentResponse == m_nCurrentRhv - m_nSessionNumber )
				Ok = true ;

		case '*' :
			if( m_nCurrentResponse == m_nSessionNumber * m_nCurrentRhv )
				Ok = true ;
	}//switch

	mar_nResponseStatus[m_nCurrentRhv] = Ok ? RESP_DONE_RIGHT : m_nCurrentResponse ;

	m_nResponseCount++ ;
}

void CMathMachineDlg::endSession()
{
	m_odtEnd = COleDateTime::GetCurrentTime();
	COleDateTimeSpan duration = m_odtEnd - m_odtStart ;
	CString min = duration.Format( "%M" );
	CString sec = duration.Format( "%S" );
	AfxMessageBox( "Time taken was " + min + " minutes & " + sec + " seconds." );

	// EVENTUALLY, PRESENT THE RESULTS AND RE-DO ERRORS
	// FOR NOW, JUST CLEAR AND ASK TO DO A NEW SESSION
	AfxMessageBox( "Please start a new session." );

	for( int i=1; i<=m_nSessionRange; i++ )
		 mar_nResponseStatus[i] = RESP_DO_THIS ;

	m_nResponseCount = 0 ;
	m_boolInSession = false ;
}
