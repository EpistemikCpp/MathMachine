// mathMachineDlg.h : header file
//

#if !defined(AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_)
#define AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// MACROS & GLOBAL VARS

#define MATH_MACHINE_DEFAULT_FONT "Times New Roman"

const int MATH_MACHINE_DEFAULT_COMBO_HEIGHT = 30 ;
const int MATH_MACHINE_DEFAULT_EDIT_HEIGHT  = 50 ;
const int MATH_MACHINE_DEFAULT_OP_INDEX  = 0 ;

// values from the Data boxes
const int     MIN_LH_NUMBER =  0 ;
const int     MAX_LH_NUMBER = 30 ;
const int DEFAULT_LH_NUMBER = 15 ;

const int     MIN_NUM_QUESTIONS = 10 ;
const int     MAX_NUM_QUESTIONS = 25 ;
const int DEFAULT_NUM_QUESTIONS = 15 ;

const int     MIN_RH_RANGE =  10 ;
const int     MAX_RH_RANGE = 120 ;
const int DEFAULT_RH_RANGE =  99 ;

const int MINUS_RANGE = MAX_LH_NUMBER + MAX_RH_RANGE ;//12 + DEFAULT_RANGE ;

const int MAX_NUM_DIGITS = 6 ;

// values for the response status array
const int RESP_DONT_DO_THIS = -100 ;
const int RESP_DO_THIS      = -10 ;
const int RESP_DONE_RIGHT   = -1 ;
// if 'DONE_WRONG', QUESTION WILL BE REPEATED
// [OLD -- value in array will be the actual response entered]

/////////////////////////////////////////////////////////////////////////////
// CMathMachineDlg dialog

class CMathMachineDlg : public CDialog
{
// Construction
public:
	CMathMachineDlg( CWnd* pParent = NULL );// standard constructor

// Dialog Data
	//{{AFX_DATA(CMathMachineDlg)
	enum { IDD = IDD_MATHMACHINE_DIALOG };
	CButton	     m_bnEnter;
	CEdit	     m_editResponse;
	CEdit	     m_editQuestion;
	CComboBox    m_cbOperation;
	int		     m_nNumQuestions;
	int			 m_nLhNumber;
	int			 m_nRhRange;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathMachineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:
	// session report
	CString			m_strTimeTaken;
	CString			m_strScore;

	// general dlg control vars
	int				m_nNumSessions;
	bool			m_boolInSession ;
	bool			m_boolErrorState;
	CString			m_strCaption;
	CString			m_strMesg;
	COleDateTime	m_odtStart;
	COleDateTime	m_odtEnd;

	// cb vars
	CString			m_strSessionNumber;
	int				m_nSessionNumber;
	CString			m_strSessionOperation;
	int				m_nSessionRange;

	// question & response vars
	int				m_nErrorCount;
	CString			m_strQuestion;
	CString			m_strResponse;
	int				m_nCurrentResponse;
	int				m_nCurrentRhv;
	int				m_nResponseCount ;
	int				mar_nResponseStatus[ MINUS_RANGE + 1 ];
	
	// Fonts
	CFont			m_fontCombo;
	CFont			m_fontEdit;

	// icon (automatically generated)
	HICON	 m_hIcon;

//** FUNCTIONS

	void	initSessionVars();
	void	initCBs( int opIndex );
	void	initFonts( int cbHeight, int editHeight );
	void	displayQuestion( bool newRhv = true );
	bool	processResponse();
	void	endSession();
	void	showReport();
	bool	getAndValidateData();

	// Generated message map functions
	//{{AFX_MSG(CMathMachineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeOperation();
	afx_msg void OnStart();
	afx_msg void OnEnter();
	afx_msg void OnEditchangeOperation();
	virtual void OnCancel();
	afx_msg void OnLastReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_)
