// ProbVal.h: interface for the CProbVal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROBVAL_H__41EC78DC_7977_46D7_A660_29430EB0D348__INCLUDED_)
#define AFX_PROBVAL_H__41EC78DC_7977_46D7_A660_29430EB0D348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProbVal  
{
public:
	void Reset();
	int GetProbCnt();
	void FixVal(int nVal);
	BOOL Resume(int nVal);
	BOOL Remove(int nVal);
	BOOL IsFixed();
	BOOL IsValid();
	int operator[](int n);
	CProbVal();
	virtual ~CProbVal();

protected:
	int m_nFix;//initial value if defined
	int m_nVal[9];
	int m_nCnt;
};

#endif // !defined(AFX_PROBVAL_H__41EC78DC_7977_46D7_A660_29430EB0D348__INCLUDED_)
