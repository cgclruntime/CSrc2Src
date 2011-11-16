#include "ParaHeader.h"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

#define PB push_back
#define MP make_pair
#define two(a) (1LL << (a))
#define contain(a, b)  ((a & two(b)) != 0)
#define SIZE(a) ((int)(a.size()))
#define lowbit(a) ((a) & -(a))
#define left(a) (((a) << 1) + 1)
#define right(a) (left(a) + 1)

#define pre(a) (((a) - 1) >> 1)

typedef long long LL;
typedef pair<int, int> PII;
const double eps = 1e-7;
const double PI = 2 * acos(0.0);
using namespace std;

const int MAX = two(6);
const int sizeOfMatrix = 1 << 11;
const int sizeOfBlock = 1 << 11;
const int numOfBlock = sizeOfMatrix / sizeOfBlock;

double tmp[numOfBlock * numOfBlock][sizeOfBlock][sizeOfBlock];
double _L[sizeOfBlock][sizeOfBlock], _U[sizeOfBlock][sizeOfBlock], D[sizeOfMatrix][sizeOfMatrix];
double A[sizeOfMatrix][sizeOfMatrix];
double B[sizeOfMatrix][sizeOfMatrix], C[sizeOfMatrix][sizeOfMatrix];



void Init()
{
	srand(time(NULL));
	for(int i = 0; i < sizeOfMatrix; i++)
		for(int j = 0; j < sizeOfMatrix; j++)
			A[i][j] = rand() + 1;
}

void getInverseL(int x)
{
	for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
		_L[i][j] = 0;

	for(int i = 0; i < sizeOfBlock; i++) _L[i][i] = 1;
	
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < i; j++)
			for(int k = j; k < i; k++)
				_L[i][j] -= A[i + x][k + x] * _L[k][j];
}

void getInverseU(int x)
{
	for(int i = 0; i < sizeOfBlock; i++) 
		for(int j = 0; j < sizeOfBlock; j++)
				_U[i][j] = 0;
	for(int i = 0; i < sizeOfBlock; i++)
		_U[i][i] = 1 / A[i + x][i + x];
	
	for(int i = sizeOfBlock - 1; i >= 0; --i)
		for(int j = sizeOfBlock - 1; j > i; --j)
		{
			double tmp = 0;
			for(int k = j; k >= i + 1; --k)
				tmp += _U[k][j] * A[x + i][x + k];
			_U[i][j] = tmp;
		}
	
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = i + 1; j < sizeOfBlock; j++)
			_U[i][j] *= _U[i][i];
}

void LUDecompose(int x)
{
	int m = sizeOfBlock + x;
	for(int i = x; i < m; i++)	
	{
		for(int j = i + 1; j < m; j++) A[j][i] /= A[i][i];
		
		for(int j = i + 1; j < m; j++)
			for(int k = i + 1; k < m; k++)
				A[j][k] -= A[j][i] * A[i][k];
	}
}

void updateL(int x, int y, double tmp[][sizeOfBlock])
{
	for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
		tmp[i][j] = 0;
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			for(int k = 0; k < sizeOfBlock; k++)
				tmp[i][j] += _L[i][k] * A[k + x][j + y];
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			A[i + x][j + y] = tmp[i][j];
}

void updateU(int x, int y, double tmp[][sizeOfBlock])
{
	for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
		tmp[i][j] = 0;
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			for(int k = 0; k < sizeOfBlock; k++)
				tmp[i][j] += A[i + x][k + y] + _U[k][j];

	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			A[i + x][j + y] = tmp[i][j];
}

void updateLU(int x, int y, double tmp[][sizeOfBlock])
{
	updateL(x, y, tmp);
	updateU(y, x, tmp);
}

void _fake_updateLU_2(int x, int y, double tmp[][sizeOfBlock], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_updateLU_1(int x, int y, double tmp[][sizeOfBlock], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_updateLU_2(x, y, tmp, pCtxt);
}

void updateD(int x, int y, int b, double tmp[][sizeOfBlock])
{
	for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
		tmp[i][j] = 0;
	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			for(int k = 0; k < sizeOfBlock; k++)
				tmp[i][j] += A[i + x][b + k] * A[b + k][j +y];

	for(int i = 0; i < sizeOfBlock; i++)
		for(int j = 0; j < sizeOfBlock; j++)
			A[i + x][j + y] -= tmp[i][j];
}

void _fake_updateD_2(int x, int y, int b, double tmp[][sizeOfBlock], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_updateD_1(int x, int y, int b, double tmp[][sizeOfBlock], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_updateD_2(x, y, b, tmp, pCtxt);
}

int main(int argc, char **argv)
{
	double TMP = 1e6;
	utl::startLogInfrastrue("log.txt",40000);
	struct timeval ts, te;
	struct timezone tz;
	
	if(argc != 2)
	{
		std::cout<<"wrong args!"<<std::endl;
		return -1;
	}
	int iPoolSize = atoi(argv[1]);
	parallelFunc(NULL, iPoolSize);
	
	Init();
	memcpy(D, A, sizeof(A));

	gettimeofday(&ts, &tz);
	for(int i = 0; i < sizeOfMatrix; i += sizeOfBlock)
	{
		LUDecompose(i);
		getInverseL(i);
		getInverseU(i);
		int id = 0;
		PFID myPFID;
		ActionScope s1(i);
		for(int j = i + sizeOfBlock; j < sizeOfMatrix; j += sizeOfBlock)
		{
			
			FuncContext *pCtxt = new FuncContext(s1, (void *)updateLU, "radixSort");	
			_fake_updateLU_1(i, j, tmp[id], pCtxt);
			parallelFunc(pCtxt);
			if(j == i + sizeOfBlock) myPFID = pCtxt->getPFID(); 
			id++;
		}
		id = 0;
		for(int j = i + sizeOfBlock; j < sizeOfMatrix; j += sizeOfBlock)
			for(int k = i + sizeOfBlock; k < sizeOfMatrix; k += sizeOfBlock)
			{
				FuncContext *pCtxt = new FuncContext(s1, (void *)updateD, "radixSort");	
				WaitCondBase *tt = new AllWaitCond(myPFID);
				pCtxt->addWaitCond(tt);
				_fake_updateD_1(j, k, i, tmp[id++], pCtxt);
				parallelFunc(pCtxt);
			}
		s1.exitScope();
	}
	gettimeofday(&te, &tz);
	printf("total time %.5lf\n", ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
	return 0;
}