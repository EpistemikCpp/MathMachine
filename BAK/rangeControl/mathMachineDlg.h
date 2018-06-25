// mathMachineDlg.h : header file
//

#if !defined(AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_)
#define AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// values from the Range Combo Box Data
const int MIN_RANGE = 10 ;
const int MAX_RANGE = 16 ;

// values for the response status array
const int RESP_DONT_DO_THIS = -100 ;
const int RESP_DO_THIS      = -10 ;
const int RESP_DONE_RIGHT   = -1 ;
// if DONE_WRONG, val is number entered

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
	CButton	   m_bnEnter;
	CEdit	     m_editResponse;
	CComboBox  m_cbRange;
	CEdit	     m_editQuestion;
	CComboBox  m_cbOperation;
	CComboBox  m_cbNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathMachineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// general dlg control vars
	bool			m_boolInSession ;
	COleDateTime m_odtStart;
	COleDateTime m_odtEnd;

	// cb vars
	CString		m_strSessionNumber;
	int				m_nSessionNumber;
	CString		m_strSessionOperation;
	CString		m_strSessionRange;
	int				m_nSessionRange;

	// question & response vars
	int				m_nCurrentResponse;
	int				m_nNeededResponses;
	int				m_nCurrentRhv;
	int				m_nResponseCount ;
	int				mar_nResponseStatus[ MAX_RANGE + 1 ];
	
	// fonts
	CFont			m_fontCombo;
	CFont			m_fontEdit;

	// icon (automatically generated)
	HICON		m_hIcon;

	// FUNCTIONS
	void		initCBs( int numIndex, int opIndex, int rangeIndex );
	void		initFonts( int cbHeight, int editHeight );
	void		displayQuestion();
	void		processResponse();
	void		endSession();

	// Generated message map functions
	//{{AFX_MSG(CMathMachineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeNumber();
	afx_msg void OnSelchangeOperation();
	afx_msg void OnSelchangeRange();
	afx_msg void OnStart();
	afx_msg void OnEnter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHMACHINEDLG_H__50AD7F18_80DA_41E5_AC65_0CCD508008EA__INCLUDED_)
