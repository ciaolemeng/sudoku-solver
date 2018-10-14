// SudukoDlg.h : header file
//

#if !defined(AFX_SUDUKODLG_H__1A711F76_79D2_4150_9DD1_EA1C0F4F44D3__INCLUDED_)
#define AFX_SUDUKODLG_H__1A711F76_79D2_4150_9DD1_EA1C0F4F44D3__INCLUDED_

#include "..\Solver.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSudukoDlg dialog

class CSudukoDlg : public CDialog
{
// Construction
public:
	CSudukoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSudukoDlg)
	enum { IDD = IDD_SUDUKO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSudukoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSolver m_slvr;
	BOOL ReadFixVal();
	HICON m_hIcon;
	int m_nVals[81];

	// Generated message map functions
	//{{AFX_MSG(CSudukoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCalc();
	afx_msg void OnCback();
	afx_msg void OnCclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUDUKODLG_H__1A711F76_79D2_4150_9DD1_EA1C0F4F44D3__INCLUDED_)
