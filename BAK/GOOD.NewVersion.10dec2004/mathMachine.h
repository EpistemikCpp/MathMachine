// mathMachine.h : main header file for the MATHMACHINE application
//

#if !defined(AFX_MATHMACHINE_H__2BBF8B05_350C_4450_89F5_A02B232EE987__INCLUDED_)
#define AFX_MATHMACHINE_H__2BBF8B05_350C_4450_89F5_A02B232EE987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathMachineApp:
// See mathMachine.cpp for the implementation of this class
//

class CMathMachineApp : public CWinApp
{
public:
	CMathMachineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathMachineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMathMachineApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHMACHINE_H__2BBF8B05_350C_4450_89F5_A02B232EE987__INCLUDED_)
