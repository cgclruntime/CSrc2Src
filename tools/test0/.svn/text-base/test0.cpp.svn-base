#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#include "ParaHeader.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define PROCESS_NUM 128
#define MAX_NUM  (1 << 25)

#define pi 3.14159265354
double data[MAX_NUM][2], tmp[MAX_NUM][2];
int len = 1 << 23;

void complexMul(double a[], double b[], double c[])
{
	double t0, t1;
	t0 = a[0] * b[0] - a[1] * b[1];
	t1 = a[1] * b[0] + a[0] * b[1];
	c[0] = t0, c[1] = t1;
}

void complexAdd(double a[], double b[], double c[])
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
}

void complexSub(double a[], double b[], double c[])
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
}

int bit_reverse(int x, int bit_len)
{
	int res = 0;
	--bit_len;
	for(int i = 0; i <= bit_len; i++)
		if(x & (1 << i)) res |= (1 << (bit_len - i));
	return res;
}



void processBitReverse(int begin, int end, int bit_len)
{
	for(int i = begin; i < end; i++)
	{
		int x = bit_reverse(i, bit_len);
		tmp[x][0] = data[i][0];
		tmp[x][1] = data[i][1];
	}
}

void _fake_processBitReverse_2(int begin, int end, int bit_len, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}


void _fake_processBitReverse_1(int begin, int end, int bit_len, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_processBitReverse_2(begin, end, bit_len, pCtxt);
}



void processFFT(int begin, int end, int m, double wm[])
{
	double w[2] = {1, 0};
	while(begin != end)
	{
		if(begin + m / 2 >= len) break;
		for(int i = 0; i < m / 2; i++)
		{
			double t[2], u[2];
			complexMul(w, data[begin + i + m / 2], t);
			u[0] = data[begin + i][0], u[1] = data[begin + i][1];
			complexSub(u, t, data[begin + i + m / 2]);
			complexMul(w, wm, w);
		}
		begin += m;
	}
}

void _fake_processFFT_2(int begin, int end, int m, double wm[], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_processFFT_1(int begin, int end, int m, double wm[], FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_processFFT_2(begin, end, m, wm, pCtxt);
}




/* len must to be 2 ^ n;
	oper = 1, then convert integer to complex
	oper = -1, convert complex to integer
 */
void FFT(int len, int oper)
{
	int bit_len = 1;
	while((1 << bit_len) < len) bit_len++;
	
	/*len % PROCESS shoudle be 0*/
	{
		//parallel processBitReverse pB;
		ActionScope s0(1);
		for(int i = 0; i < len; i += len / PROCESS_NUM)
		{
			FuncContext *pCtxt = new FuncContext(s0, (void *)processBitReverse, "processBitReverse");	
			_fake_processBitReverse_1(i, i + len / PROCESS_NUM, bit_len, pCtxt);
			parallelFunc(pCtxt);
		}
		s0.exitScope();
	}
	
	memcpy(data, tmp, sizeof(tmp));
	
	for(int i = 1; (1 << i) <= len; i++)
	{
		//cout << i << endl;
		
		int m = 1 << i;
		double wm[2] = {cos(pi * 2 / (double)m), oper * sin(pi * 2 / (double)m)};
		ActionScope s1(2);
		for(int j = 0; j < PROCESS_NUM; j++)
		{
			FuncContext *pCtxt = new FuncContext(s1, (void *)processFFT, "processFFT");	
			_fake_processFFT_1(j * len / PROCESS_NUM, (j + 1) * len / PROCESS_NUM, m, wm, pCtxt);
			parallelFunc(pCtxt);
		}
		s1.exitScope();
	}
}

void generateData(int len)
{
	srand(time(NULL));
	for(int i = 0; i < len; i++)
		data[i][0] = rand() & 15;
}

int main(int argc, char *argv[])
{
	utl::startLogInfrastrue("log.txt",40000);
	if(argc != 2)
	{
		std::cout<<"wrong args!"<<std::endl;
		return -1;
	}
	int iPoolSize = atoi(argv[1]);
	parallelFunc(NULL, iPoolSize);
	
	generateData(len);
	struct timeval ts, te;
	struct timezone tz;
	double TMP = 1e6;
	gettimeofday(&ts, &tz);
	FFT(len, 1);
	gettimeofday(&te, &tz);
	printf("%.5lf\n", ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
	return 0;
}
