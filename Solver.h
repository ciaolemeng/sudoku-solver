// Solver.h: interface for the CSolver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLVER_H__10930293_DFA6_4F7C_9AED_A249096978EC__INCLUDED_)
#define AFX_SOLVER_H__10930293_DFA6_4F7C_9AED_A249096978EC__INCLUDED_

#include "ProbVal.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSolver  
{
public:
	BOOL CheckInput();
	void Reset();
	double GetCalcTime();
	int GetPosVal(int pos);
	int GetMinProb(int &probcnt);
	BOOL FindRslt(int lyr=0);
	void PrintAll(BOOL bIsAns=TRUE);
	void Remove(int nr, int nc, int nVal);
	void Resume(int nr,int nc,int nVal);
	void FixVal(int nr,int nc,int nVal);
	BOOL IsValid(int nr,int nc);
	CSolver();
	virtual ~CSolver();
	int m_nDeepest;

protected:
	BOOL IsValid(int nr, int nc,int nv);
	CProbVal m_probVal[81];
	CProbVal (*m_aprobVal)[9];
	int m_nAns[81];
	int (*m_naAns)[9];
	int m_nRecurDepth;
	BOOL m_bOccupy[81];
	BOOL (*m_baOccupy)[9];
	DWORD m_dwTick;
};

#endif // !defined(AFX_SOLVER_H__10930293_DFA6_4F7C_9AED_A249096978EC__INCLUDED_)
