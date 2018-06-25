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
	m_nNumQuestions = 0;
	m_nLhNumber = 0;
	m_nRhRange = 0;
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
	DDX_Control(pDX, IDC_QUESTION, m_editQuestion);
	DDX_Control(pDX, IDC_OPERATION, m_cbOperation);
	DDX_Text(pDX, IDC_NUM_QUESTIONS, m_nNumQuestions);
	DDX_Text(pDX, IDC_LH_NUMBER, m_nLhNumber);
	DDX_Text(pDX, IDC_RH_RANGE, m_nRhRange);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMathMachineDlg, CDialog)
	//{{AFX_MSG_MAP(CMathMachineDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_OPERATION, OnSelchangeOperation)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_CBN_EDITCHANGE(IDC_OPERATION, OnEditchangeOperation)
	ON_BN_CLICKED(IDC_LAST_REPORT, OnLastReport)
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

	// Seed the random-number generator with current time
	srand( (unsigned)time( NULL ) );
	m_nNumSessions   = 0 ;

	initSessionVars();
	initFonts( MATH_MACHINE_DEFAULT_COMBO_HEIGHT, MATH_MACHINE_DEFAULT_EDIT_HEIGHT );
	// set the Combo boxes to their default values
	initCBs( MATH_MACHINE_DEFAULT_OP_INDEX );

	return TRUE ; // return TRUE unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CMathMachineDlg MEMBER FUNCTIONS

void CMathMachineDlg::initFonts( int cbHeight, int editHeight )
{
	m_fontCombo.CreateFont( cbHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET,
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
							DEFAULT_PITCH | FF_ROMAN, MATH_MACHINE_DEFAULT_FONT );
	m_cbOperation.SetFont( &m_fontCombo );

	m_fontEdit.CreateFont( editHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET,
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
							DEFAULT_PITCH | FF_ROMAN, MATH_MACHINE_DEFAULT_FONT );
	m_editQuestion.SetFont( &m_fontEdit );
	m_editResponse.SetFont( &m_fontEdit );
}

void CMathMachineDlg::initCBs( int opIndex )
{
	m_cbOperation.SetCurSel( opIndex );
	m_cbOperation.GetLBText( opIndex, m_strSessionOperation );
}

void CMathMachineDlg::initSessionVars()
{
	m_boolInSession  = false ;
	m_boolErrorState = false ;
	m_nResponseCount = 0 ;
	m_nErrorCount    = 0 ;
}

void CMathMachineDlg::OnSelchangeOperation() 
{
  // get the session operation
  int nIndex = m_cbOperation.GetCurSel();
  if( nIndex != CB_ERR )
  {
	  m_cbOperation.GetLBText( nIndex, m_strSessionOperation );

#ifdef MATH_MACHINE_DEBUG
	  CString opString = "OnSelchangeOperation is " + m_strSessionOperation ;
	  AfxMessageBox( opString );
#endif
  }
}

// in case the user enters a value directly in the Op edit box
void CMathMachineDlg::OnEditchangeOperation() 
{
	CString strEditOp ;
	CComboBox* pCb = (CComboBox*)GetDlgItem( IDC_OPERATION );
	pCb->GetWindowText( strEditOp );

	int nIndex = m_cbOperation.FindStringExact( 0, strEditOp );
	if( nIndex == CB_ERR )
	  nIndex = 0 ;// set to default

	m_cbOperation.SetCurSel( nIndex );
    m_cbOperation.GetLBText( nIndex, m_strSessionOperation );
}

void CMathMachineDlg::OnStart()
{
  // see if user is trying to re-start from a running session
  if( m_boolInSession )
	{
		m_strCaption.LoadString( IDS_NOTICE );
		m_strMesg.LoadString( IDS_REQUEST_RESTART );
		int response = MessageBox( m_strMesg, m_strCaption,
									 MB_YESNO | MB_ICONQUESTION );
		if( response == IDYES )
		{
			// re-start
			initSessionVars();
			OnStart();
		}
		else // just go back to the answer box
			GotoDlgCtrl( GetDlgItem(IDC_RESPONSE) );
	}
	else
		{	// start a new session
		    m_boolInSession = true ;
			getAndValidateData();

			m_odtStart = COleDateTime::GetCurrentTime();

			if( m_strSessionOperation == "-" )
			{
				// session range will be from 'number' to 'number + RhRange' 
				m_nSessionRange = m_nSessionNumber + m_nRhRange ;
				for( int i=m_nSessionRange ; i>=m_nSessionNumber ; --i )
					mar_nResponseStatus[i] = RESP_DO_THIS ;
				for( int j=m_nSessionNumber-1 ; j>0 ; --j )
				  mar_nResponseStatus[j] = RESP_DONT_DO_THIS ;
			}
			else
				{
					// session range will be from 0 to the chosen range
	  				m_nSessionRange = m_nRhRange ;
					for( int i=0; i<=m_nRhRange; i++ )
						mar_nResponseStatus[i] = RESP_DO_THIS ;
					for( int j=m_nRhRange+1; j<=MINUS_RANGE; j++ )
						mar_nResponseStatus[j] = RESP_DONT_DO_THIS ;
				}

			displayQuestion();
		}
}

void CMathMachineDlg::displayQuestion( bool newRhv )
{
	if( newRhv )// need a new question
	{
		// get a random value in the range that hasn't been used yet in this session
		while( mar_nResponseStatus[m_nCurrentRhv = (rand()%(m_nSessionRange+1))]
						!= RESP_DO_THIS )
		{ /* try again */ }
	}
	
	// need the current Rhv int as a string to display
	char s[MINUS_RANGE] = {0};
	sprintf( s, "%d", m_nCurrentRhv );
	CString strRhv = s ;

#ifdef MATH_MACHINE_DEBUG
	AfxMessageBox( "CurrentRhv = " + strRhv );
#endif

	if( m_strSessionOperation == "-" )
	  m_strQuestion = strRhv + m_strSessionOperation + m_strSessionNumber ;
	else
		m_strQuestion = m_strSessionNumber + m_strSessionOperation + strRhv ;

	m_editQuestion.SetWindowText( m_strQuestion + " = " );

	GotoDlgCtrl( GetDlgItem(IDC_RESPONSE) );
}

// 'Enter' button is the default 
//  - if user presses Enter after a response, processing will begin here
void CMathMachineDlg::OnEnter() 
{
  if( m_boolInSession )
	{
		m_editResponse.GetWindowText( m_strResponse );

#ifdef MATH_MACHINE_DEBUG
		m_strResponse += " received by Enter." ;
		AfxMessageBox( m_strResponse );
#endif

		if( m_strResponse.GetLength() == 0 )// i.e. NO text entered (string = "\0")
		  m_strResponse = "0" ;
		m_nCurrentResponse = atoi( m_strResponse );

		bool newRhv = processResponse();// return indicates if response was correct

		// see if we are finished the current session
		if( m_nResponseCount < m_nNumQuestions )
		  displayQuestion( newRhv );// repeat question (newRhv == false) if response was wrong
		else
			{
				endSession();
				GotoDlgCtrl( GetDlgItem(IDC_NUM_QUESTIONS) );
			}

		// clear the response box
		m_editResponse.SetWindowText( "" );
	}
	else // NOT in a session yet
		{
			m_strCaption.LoadString( IDS_NOTICE );
			m_strMesg.LoadString( IDS_REQUEST_SESSION );
			MessageBox( m_strMesg, m_strCaption, MB_OK | MB_ICONINFORMATION );
			GotoDlgCtrl( GetDlgItem(IDC_NUM_QUESTIONS) );
		}
}

bool CMathMachineDlg::processResponse()
{
	bool Ok = false ;
	CString msg2, msg3 ;

#ifdef MATH_MACHINE_DEBUG
	CString test = "Op is " ;
	test += m_strSessionOperation[0] ;
	AfxMessageBox( test );
#endif

	switch( m_strSessionOperation[0] )
	{
		case '+' :
			if( m_nCurrentResponse == m_nSessionNumber + m_nCurrentRhv )
			  Ok = true ;

#ifdef MATH_MACHINE_DEBUG
			MessageBox( "Op +" );
#endif
			break ;

		case '-' :
			if( m_nCurrentResponse == m_nCurrentRhv - m_nSessionNumber )
			  Ok = true ;
			break ;

		case '*' :
			if( m_nCurrentResponse == m_nSessionNumber * m_nCurrentRhv )
			  Ok = true ;
			break ;

		default : // SHOULD NEVER HAPPEN
				m_strCaption.LoadString( IDS_WARNING );
				m_strMesg.LoadString( IDS_BAD_OPERATION );
				MessageBox( m_strSessionOperation + m_strMesg, m_strCaption,
							MB_OK | MB_ICONEXCLAMATION );

	}//switch

	// notify with a MessageBox if response was erroneous
	if( !Ok )
	{
		MessageBeep( MB_OK );// sound cue for WRONG answer
		if( !m_boolErrorState )
		{
			m_nErrorCount++ ;
			m_boolErrorState = true ;
		}
		m_strCaption.LoadString( IDS_ERROR );
		m_strMesg.LoadString( IDS_SORRY );
		msg2.LoadString( IDS_NOT_EQUAL );
		msg3.LoadString( IDS_TRY_AGAIN );
		MessageBox( m_strMesg + m_strQuestion + msg2 + m_strResponse + msg3,
					m_strCaption, MB_OK | MB_ICONERROR );
	}
	else
		{
			MessageBeep( MB_ICONHAND );// sound cue for RIGHT answer
			m_boolErrorState = false ;
			// set the Ok flag
			mar_nResponseStatus[m_nCurrentRhv] = RESP_DONE_RIGHT ;
			m_nResponseCount++ ;
		}

	return Ok ;// will repeat the current question if response was incorrect
}

void CMathMachineDlg::endSession()
{
	// elapsed time
	CString timemsg ;
	timemsg.LoadString( IDS_TIME_TAKEN );
	m_odtEnd = COleDateTime::GetCurrentTime();
	COleDateTimeSpan duration = m_odtEnd - m_odtStart ;
	CString min = duration.Format( "%M" );
	CString sec = duration.Format( "%S" );
	m_strTimeTaken = timemsg + min + " minutes & " + sec + " seconds.\n\n" ;

	// error count
	char g[ MAX_NUM_DIGITS ] = {0} , t[ MAX_NUM_DIGITS ] = {0} ;
	sprintf( g, "%d", m_nNumQuestions - m_nErrorCount );
	CString good = g ;
	sprintf( t, "%d", m_nNumQuestions );
	CString tot = t ;
	m_strScore = "You got " + good + " right out of " + tot + "!\n\n" ;
  
	// present the results
	showReport();
#ifdef MATH_MACHINE_DEBUG
	MessageBox( "after showReport()", "DEBUG", MB_OK | MB_ICONEXCLAMATION );
#endif

	initSessionVars();
  
	// clear the question box
	m_editQuestion.SetWindowText( "" );

	m_nNumSessions++ ;

#ifdef MATH_MACHINE_DEBUG
	MessageBox( "END endSession()", "DEBUG", MB_OK | MB_ICONEXCLAMATION );
#endif
}

void CMathMachineDlg::OnCancel() 
{
	// confirm exit
	m_strCaption.LoadString( IDS_WARNING );
	m_strMesg.LoadString( IDS_CONFIRM_EXIT );
	int response = MessageBox( m_strMesg, m_strCaption,
								MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION );
	if( response == IDYES )
	  CDialog::OnCancel();
	else
		GotoDlgCtrl( GetDlgItem(IDC_RESPONSE) );
}

void CMathMachineDlg::OnLastReport() 
{
	// make sure we have some session data before reporting
	if( m_nNumSessions > 0 )
	  showReport();
	else
		MessageBox( "NO Results yet", "Problem", MB_OK | MB_ICONEXCLAMATION );
}

void CMathMachineDlg::showReport()
{
	m_strMesg.LoadString( IDS_REQUEST_NEW );
	m_strCaption.LoadString( IDS_NOTICE );
	CString report = m_strScore + m_strTimeTaken + m_strMesg ;
	MessageBox( report, m_strCaption, MB_OK | MB_ICONEXCLAMATION );
}

bool CMathMachineDlg::getAndValidateData()
{
	// transfer the data from the gui to the vars and check the values
	if( UpdateData() == FALSE )
	{
		m_nNumQuestions = DEFAULT_NUM_QUESTIONS ;
		m_nLhNumber = DEFAULT_LH_NUMBER ;
		m_nRhRange = DEFAULT_RH_RANGE ;

		// update the gui with the default values
		UpdateData( FALSE );

		return false ;
	}

	//** CHECK THE RANGES OF ALL THE VALUES

	if( m_nNumQuestions < MIN_NUM_QUESTIONS  ||  m_nNumQuestions > MAX_NUM_QUESTIONS )
	  m_nNumQuestions = DEFAULT_NUM_QUESTIONS ;

	// have to make sure the range is larger than the number of questions
	if( m_nRhRange <= m_nNumQuestions ) m_nRhRange = m_nNumQuestions + 1 ;

	if( m_nLhNumber < MIN_LH_NUMBER  ||  m_nLhNumber > MAX_LH_NUMBER )
	  m_nLhNumber = DEFAULT_LH_NUMBER ;

	if( m_nRhRange < MIN_RH_RANGE  ||  m_nRhRange > MAX_RH_RANGE )
	  m_nRhRange = DEFAULT_RH_RANGE ;

	// set the session number and string
	m_nSessionNumber = m_nLhNumber ;
	char s[ MAX_NUM_DIGITS ] = {0} ;
	sprintf( s, "%d", m_nSessionNumber );
	m_strSessionNumber = s ;

	return true ;
}
