// Solver.cpp: implementation of the CSolver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Suduc.h"
#include "Solver.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolver::CSolver()
{
	m_naAns=(int (*)[9])&m_nAns;
	m_aprobVal=(CProbVal (*)[9])&m_probVal;
	m_baOccupy=(BOOL (*)[9])&m_bOccupy;
	memset(m_nAns,0xff,sizeof(m_nAns));
	memset(m_bOccupy,0,sizeof(m_bOccupy));
	m_nRecurDepth=81;
	m_nDeepest=0;

	//initialize the question by assistant variables
/*	FixVal(0,0,0);	FixVal(0,1,3); FixVal(0,6,1);
	FixVal(1,2,8);
	FixVal(3,8,8);
	FixVal(4,4,7);
	FixVal(5,2,5);	FixVal(5,3,1); 
	FixVal(7,1,2);	FixVal(7,4,4); FixVal(7,7,6);
	FixVal(8,5,0);*/

/*	FixVal(0,0,6-1);	FixVal(0,4,7-1);	FixVal(0,7,9-1);
	FixVal(1,5,5-1);	FixVal(1,8,8-1);
	FixVal(2,1,3-1);	FixVal(2,2,2-1);	FixVal(2,4,8-1);	FixVal(2,6,4-1);
	FixVal(3,2,6-1);	FixVal(3,6,5-1);
	FixVal(4,1,1-1);	FixVal(4,4,2-1);	FixVal(4,5,7-1);	FixVal(4,8,6-1);	
	FixVal(5,1,8-1);	FixVal(5,3,6-1);	FixVal(5,7,1-1);	
	FixVal(6,0,7-1);	FixVal(6,3,4-1);	FixVal(6,5,2-1);	
	FixVal(7,0,5-1);	FixVal(7,4,9-1);	FixVal(7,7,4-1);	
	FixVal(8,1,2-1);	FixVal(8,3,5-1);	FixVal(8,7,7-1);	
	
	FixVal(0,0,2);	FixVal(0,1,5);	FixVal(0,3,0);	FixVal(0,5,3);	FixVal(0,6,4);	
	FixVal(1,2,8);		
	FixVal(2,8,7);		
	FixVal(3,0,0);	FixVal(3,3,1);	FixVal(3,7,8);	
	FixVal(4,2,4);	FixVal(4,6,7);	
	FixVal(5,1,3);	FixVal(5,5,5);	FixVal(5,8,6);	
	FixVal(6,0,1);		
	FixVal(7,6,5);	
	FixVal(8,2,7);	FixVal(8,3,8);	FixVal(8,5,6);	FixVal(8,7,2);	FixVal(8,8,4);	*/
}

CSolver::~CSolver()
{

}

BOOL CSolver::IsValid(int nr, int nc)
{
	int i,j,n,m,tst[9];

	m=m_naAns[nr][nc];
	
	memset(tst,0,sizeof(tst));
	for (i=0;i<9;i++)
	{
		n=m_naAns[nr][i];
		if (n>=0)
		{
			tst[n]++;
		}
		if (i!=nc&&n==m)
		{
			return FALSE;
		}
	}
	for (i=0;i<9;i++)
	{
		if (tst[n]>1)
		{
			return FALSE;
		}
	}
	
	memset(tst,0,sizeof(tst));
	for (i=0;i<9;i++)
	{
		n=m_naAns[i][nc];
		if (n>=0)
		{
			tst[n]++;
		}
		if (i!=nr&&n==m)
		{
			return FALSE;
		}
	}
	for (i=0;i<9;i++)
	{
		if (tst[n]>1)
		{
			return FALSE;
		}	
	}
	
	memset(tst,0,sizeof(tst));
	for (i=nr/3*3;i<nr/3*3+3;i++)
	{
		for (j=nc/3*3;j<nc/3*3+3;j++)
		{
			n=m_naAns[i][j];
			if (n>=0)
			{
				tst[n]++;
			}
			if (i!=nr&&j!=nc&&n==m)
			{
				return FALSE;
			}
		}
	}
	for (i=0;i<9;i++)
	{
		if (tst[n]>1)
		{
			return FALSE;
		}	
	}

	return TRUE;
}

void CSolver::FixVal(int nr, int nc, int nVal)
{
	Remove(nr,nc,nVal);//remove reference cubic with nVal first
	m_naAns[nr][nc]=nVal;//then specify it
	m_baOccupy[nr][nc]=TRUE;

	m_aprobVal[nr][nc].FixVal(nVal);
	m_nRecurDepth--;
}

void CSolver::Resume(int nr, int nc, int nVal)
{
	int i,j,row,clm;

	m_naAns[nr][nc]=nVal;//resume this value form answer
	if (!m_baOccupy[nr][nc])
	{
		m_aprobVal[nr][nc].Resume(nVal);
	} 
	else
	{
		return;
	}
	
	for (i=0;i<9;i++)
	{
		if (i!=nc)
		{
			if (!m_baOccupy[nr][i])
			{
				m_aprobVal[nr][i].Resume(nVal);
			}
		}
	}
	
	for (i=0;i<9;i++)
	{
		if (i!=nr)
		{
			if (!m_baOccupy[i][nc])
			{
				m_aprobVal[i][nc].Resume(nVal);
			}
		}
	}

	row=nr/3*3+3;
	clm=nc/3*3+3;
	for (i=nr/3*3;i<row;i++)
	{
		for (j=nc/3*3;j<clm;j++)
		{
			if (i!=nr&&j!=nc)
			{
				if (!m_baOccupy[i][j])
				{
					m_aprobVal[i][j].Resume(nVal);
				}
			}
		}
	}
}

void CSolver::Remove(int nr, int nc, int nVal)
{
	int i,j,row,clm;
	
	m_naAns[nr][nc]=-1;//remove this value form answer
	if (!m_baOccupy[nr][nc])
	{
		m_aprobVal[nr][nc].Remove(nVal);
	} 
	else
	{
		return;
	}
	
	for (i=0;i<9;i++)
	{
		if (i!=nc)
		{
			if (!m_baOccupy[nr][i])
			{
				m_aprobVal[nr][i].Remove(nVal);
			}
		}
	}
	
	for (i=0;i<9;i++)
	{
		if (i!=nr)
		{
			if (!m_baOccupy[i][nc])
			{
				m_aprobVal[i][nc].Remove(nVal);
			}
		}
	}
	
	row=nr/3*3+3;
	clm=nc/3*3+3;
	for (i=nr/3*3;i<row;i++)
	{
		for (j=nc/3*3;j<clm;j++)
		{
			if (i!=nr&&j!=nc)
			{
				if (!m_baOccupy[i][j])
				{
					m_aprobVal[i][j].Remove(nVal);
				}
			}
		}
	}
}

void CSolver::PrintAll(BOOL bIsAns)
{
	if (bIsAns)
	{
		printf("output all answers...");
	}
	else
	{
		printf("output all probvals...");
	}

	int i,j;
	for (i=0;i<9;i++)
	{
		if (i%3==0)
		{
			printf("\n");
		}
		for (j=0;j<9;j++)
		{
			if (j%3==0)
			{
				printf("\t");
			}

			if (bIsAns)
			{
				printf("%d ",m_naAns[i][j]+1);
			} 
			else
			{
				printf("%d ",m_aprobVal[i][j].GetProbCnt());
			}
		}
		printf("\n");
	}
}

int CSolver::GetMinProb(int &probcnt)
{
	int i,j,n;

	for (i=0;i<81;i++)
	{
		if (!m_probVal[i].IsFixed()&&m_nAns[i]==-1)//make sure this position hasn't been used
		{
			n=m_probVal[i].GetProbCnt();
			j=i;
			break;
		}
	}
	for (;i<81;i++)
	{
		if (m_probVal[i].IsFixed()||m_nAns[i]>-1)//fixed value or this position has tried with a value
		{
			continue;
		}
		if (m_probVal[i].GetProbCnt()<n)
		{
			n=m_probVal[i].GetProbCnt();
			j=i;
		}
	}

	probcnt=n;
	return j;//position of the firs minimum one
}

BOOL CSolver::FindRslt(int lyr)
{
	if (lyr==m_nRecurDepth)
	{//solve this suduc succeed, basic condition 1
		PrintAll(TRUE);
		int b=IsValid(3,0);
		m_dwTick=GetTickCount()-m_dwTick;
		return TRUE;
	}
	else if (lyr==0)
	{
		if (!CheckInput())
		{
			return FALSE;
		}
		m_dwTick=GetTickCount();
	}

	int pos,i,j,cnt,tmp;
/*
PrintAll(TRUE);
PrintAll(FALSE);*/
	pos=GetMinProb(cnt);//get the first minimum position, then try to fill it
	for (i=j=0;i<9&&j<cnt;i++)
	{
		tmp=m_probVal[pos][i];
		if (tmp<0)//this value can't be filled in current pos
		{
			continue;
		}

		j++;//omit 1 cycle

		//m_naAns[pos/9][pos%9]=tmp;
		if (!IsValid(pos/9,pos%9,tmp))
		{
			m_naAns[pos/9][pos%9]=-1;
			continue;
		}

		Remove(pos/9,pos%9,tmp);//this position has been used now
		m_naAns[pos/9][pos%9]=tmp;
		m_bOccupy[pos]=TRUE;

		if (FindRslt(lyr+1))
		{
			return TRUE;//base condition 2
		}
		
		m_bOccupy[pos]=FALSE;
		Resume(pos/9,pos%9,tmp);//try next probval
		m_naAns[pos/9][pos%9]=-1;
	}

	return FALSE;
}

int CSolver::GetPosVal(int pos)
{
	return m_nAns[pos];
}

double CSolver::GetCalcTime()
{
	double d=m_dwTick/1000.0;
	return d;
}

void CSolver::Reset()
{
	memset(m_nAns,0xff,sizeof(m_nAns));
	memset(m_bOccupy,0,sizeof(m_bOccupy));
	m_nRecurDepth=81;

	for (int i=0;i<81;i++)
	{
		m_probVal[i].Reset();
	}
}

BOOL CSolver::CheckInput()
{
	int i,j,n;
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
			n=m_naAns[i][j];
			if (n>-1)
			{
				m_naAns[i][j]=-1;
				if (!IsValid(i,j,n))
				{
					return FALSE;
				}
				m_naAns[i][j]=n;
			}
		}
	}
	return TRUE;
}

BOOL CSolver::IsValid(int nr, int nc, int nv)
{
	int i,j,n,m;
	
	m=m_naAns[nr][nc];
	if (m==nv)
	{
		return FALSE;
	}
	m=nv;
	
	for (i=0;i<9;i++)
	{
		n=m_naAns[nr][i];
		if (i!=nc&&n==m)
		{
			return FALSE;
		}
	}
	
	for (i=0;i<9;i++)
	{
		n=m_naAns[i][nc];
		if (i!=nr&&n==m)
		{
			return FALSE;
		}
	}
	
	for (i=nr/3*3;i<nr/3*3+3;i++)
	{
		for (j=nc/3*3;j<nc/3*3+3;j++)
		{
			n=m_naAns[i][j];
			if (i!=nr&&j!=nc&&n==m)
			{
				return FALSE;
			}
		}
	}
	
	return TRUE;
}
