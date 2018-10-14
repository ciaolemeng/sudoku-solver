// ProbVal.cpp: implementation of the CProbVal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Suduc.h"
#include "ProbVal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProbVal::CProbVal()
{
	Reset();
}

CProbVal::~CProbVal()
{

}

BOOL CProbVal::IsValid()
{
	if (m_nCnt<=0)
	{
		if (IsFixed())
		{
			return TRUE;
		} 
		else
		{
			return FALSE;
		}
	}

	if (m_nCnt>0&&m_nCnt<10)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CProbVal::IsFixed()
{
	if (m_nFix>=0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CProbVal::Remove(int nVal)
{
	if (IsFixed())
	{
		return FALSE;
	}

	if (nVal==10)//test
	{
		nVal=nVal;
	}

	if (m_nVal[nVal]>=0)
	{
		m_nVal[nVal]=-1;
		m_nCnt--;
	}

	if (m_nCnt>0&&m_nCnt<9)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CProbVal::Resume(int nVal)
{
	if (IsFixed())
	{
		return FALSE;
	}
	
	if (nVal==10)//test
	{
		nVal=nVal;
	}
	
	if (m_nVal[nVal]<0)
	{
		m_nVal[nVal]=nVal;
		m_nCnt++;
	}
	
	if (m_nCnt>0&&m_nCnt<9)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

void CProbVal::FixVal(int nVal)
{
	m_nCnt=0;
	m_nFix=nVal;
}

int CProbVal::GetProbCnt()
{
	if (IsFixed())
	{
		return 1;
	}

	return m_nCnt;
}


int CProbVal::operator[](int n)
{
	return m_nVal[n];
}

void CProbVal::Reset()
{
	m_nCnt=9;
	m_nFix=-1;
	
	for (int i=0;i<9;i++)
	{
		m_nVal[i]=i;
	}
}
