// Suduko.h : main header file for the SUDUKO application
//

#if !defined(AFX_SUDUKO_H__7BEB41D4_0FC2_40DF_9F9C_F9EC3BB89CEB__INCLUDED_)
#define AFX_SUDUKO_H__7BEB41D4_0FC2_40DF_9F9C_F9EC3BB89CEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSudukoApp:
// See Suduko.cpp for the implementation of this class
//

class CSudukoApp : public CWinApp
{
public:
	CSudukoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSudukoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSudukoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUDUKO_H__7BEB41D4_0FC2_40DF_9F9C_F9EC3BB89CEB__INCLUDED_)
