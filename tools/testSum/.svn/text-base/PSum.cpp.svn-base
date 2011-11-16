#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParaHeader.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define MAX_NUM 1 << 24 // max data size
#define MAX_RADIX 1 << 4	// max raidx
#define MAX_PROCESS  2// number of process
int *data, *tmp_data;
int cnt[MAX_PROCESS][MAX_RADIX];
vector<int> record[MAX_PROCESS][MAX_RADIX];

//int next[MAX_NUM];
int num;	//size of data
int radix;	//the radix for sort
int log2_radix; //log(radix)
double TMP = 1e6;
//get the element of data

timeval ss[MAX_PROCESS], se[MAX_PROCESS];

double getTime()
{
	struct timeval start, end;
	start.tv_sec = start.tv_usec = INT_MAX;
	end.tv_sec = end.tv_usec = 0;
	
	for(int i = 0; i < MAX_PROCESS; i++)
	{
			if(ss[i].tv_sec < start.tv_sec || (ss[i].tv_sec == start.tv_sec && ss[i].tv_usec < start.tv_usec)) start = ss[i];
			if(se[i].tv_sec > end.tv_sec   || (se[i].tv_sec == end.tv_sec   && se[i].tv_usec > end.tv_usec))   end = ss[i];
	}
	//printf("getTime : %.6lf\n", ((end.tv_sec - start.tv_sec) * TMP + (end.tv_usec - start.tv_usec)) / TMP); 
	return ((end.tv_sec - start.tv_sec) * TMP + (end.tv_usec - start.tv_usec)) / TMP;
}

void getData()
{
	data = new int [MAX_NUM];
	tmp_data = new int [MAX_NUM];
	
	//here here here
	num = MAX_NUM;
	log2_radix = 4;
	radix = MAX_RADIX;
	srand(time(NULL));
	for(int i = 0; i < num; i++)
		tmp_data[i] = data[i] = rand() & 65535;
}

void radixSort(int begin, int end, int id, int itr)
{
	struct timeval ts, te;
	struct timezone tz;
	gettimeofday(&ts, &tz);
	
	itr *= log2_radix;
	int t = radix - 1;
	for(int i = begin; i < end; i++)
	{
		int tmp = (data[i] >> itr) & 15;
		record[id][tmp].push_back(data[i]);		
	}
	gettimeofday(&te, &tz);
	ss[id] = ts, se[id] = te;
	//printf("radixSort %.0lf %.0lf\n", ts.tv_sec * TMP + ts.tv_usec, te.tv_sec * TMP + te.tv_usec);
}

void _fake_radixSort_2(int begin, int end, int id, int itr, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_radixSort_1(int begin, int end, int id, int itr, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_radixSort_2(begin, end, id, itr, pCtxt);
}

void writeBack(int begin, int end, int id)
{
	struct timeval ts, te;
	struct timezone tz;
	gettimeofday(&ts, &tz);
	for(int i = 0; i < radix; ++i)
		for(int j = 0, x = cnt[id][i], t = record[id][i].size(); j < t; ++j) 
			tmp_data[x++] = record[id][i][j];
	gettimeofday(&te, &tz);
	ss[id] = ts, se[id] = te;
}

void _fake_writeBack_2(int begin, int end, int id, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_writeBack_1(int begin, int end, int id, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_writeBack_2(begin, end, id, pCtxt);
}

void calCount()
{
	struct timeval ts, te;
	struct timezone tz;
	gettimeofday(&ts, &tz);
	
	for(int i = 0; i < MAX_PROCESS; i++)
		for(int j = 0; j < radix; j++)
			cnt[i][j] = record[i][j].size();

	for(int i = 0; i < radix; i++)
	{
		if(i) cnt[0][i] += cnt[MAX_PROCESS - 1][i - 1];
		for(int j = 1; j < MAX_PROCESS; j++)
			cnt[j][i] += cnt[j - 1][i];
	}
	for(int i = radix - 1; i >= 0; i--)
	{
		for(int j = MAX_PROCESS - 1; j > 0; j--)
			cnt[j][i] = cnt[j - 1][i];
		if(i == 0) break;
		cnt[0][i] = cnt[MAX_PROCESS - 1][i - 1];
	}
	cnt[0][0] = 0;
	gettimeofday(&te, &tz);
	printf("calCount : %.6lf\n", ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
}

void output()
{
	//cout << endl;
	//for(int i = 0; i < num; i++) printf("%d ", data[i]); cout << endl;
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
	double userTime = 0;
	
	
	utl::startLogInfrastrue("log.txt",40000);
	getData();
	output();
	struct timeval ts, te;
	struct timezone tz;
	gettimeofday(&ts, &tz);
	//gettimeofday(&ts, &tz);
	//sort(tmp_data, tmp_data + num);
	//gettimeofday(&te, &tz);
	//printf("sort : %.6lf\n",  ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP);
	
	
	ActionScope s_main(1);
	for(int i = 0; i < 16 / log2_radix; i++)	
	{
		//start = clock();
		for(int a = 0; a < MAX_PROCESS; a++)
			for(int b = 0; b < radix; b++)
			{ record[a][b].clear();	}	
			
		{
			ActionScope s_radixSort(2);
			//parallel radixSort R;
			for(int j = 0, d = (num + MAX_PROCESS - 1) / MAX_PROCESS, b = 0; j < MAX_PROCESS; j++, b += d) 
			{
				//R(b, min(b + d, num), j, i);
				FuncContext *pCtxt = new FuncContext(s_radixSort, (void *)radixSort, "radixSort");	
				_fake_radixSort_1(b, min(b + d, num), j, i, pCtxt);		
				parallelFunc(pCtxt);
			}
			s_radixSort.exitScope();
		}
		userTime += getTime();
		calCount();
		//printf("%d %d %d %.6lf\n", MAX_PROCESS, num, radix, (clock() - start) / (double)CLOCKS_PER_SEC);		
		//start = clock();
		{
			ActionScope s_writeBack(3);
			for(int j = 0, d = (num + MAX_PROCESS - 1) / MAX_PROCESS, b = 0; j < MAX_PROCESS; j++, b += d)
			{
				FuncContext *pCtxt = new FuncContext(s_writeBack, (void *)writeBack, "writeBack");	
				_fake_writeBack_1(b, min(b + d, num), j, pCtxt);		
				parallelFunc(pCtxt);
																																																																																							
			}
			s_writeBack.exitScope();
			swap(data, tmp_data);
		}
		userTime += getTime();
		//printf("%d %d %d %.6lf\n", MAX_PROCESS, num, radix, (clock() - start) / (double)CLOCKS_PER_SEC);		
	}
	s_main.exitScope();
	gettimeofday(&te, &tz);
	printf("total : %d %.6lf\n", MAX_PROCESS, ((te.tv_sec - ts.tv_sec) * TMP + (te.tv_usec - ts.tv_usec)) / TMP); 
	printf("userTime : %.6lf\n", userTime);
	return 0;
}
