import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class RadixData {
	public int MAX_NUM; //max data size
	public int MAX_RADIX; //max radix
	public int MAX_PROCESS; //number of process 

	public int data[];
	public int tmp_data[];
	public int cnt[][];
	
	public int num;	//size of data
	public int radix; //the radix for sort
	public int log2_radix;//log(radix)
	public static double pi = 3.14159265354;
	
	public Vector record[][];
	
	public RadixData(int max_process)
	{
		MAX_NUM = 1<<24; //max data size
		MAX_RADIX = 1<<4; //max radix
		MAX_PROCESS = max_process; //number of process 

		data = new int[MAX_NUM];
		tmp_data= new int[MAX_NUM];
		cnt = new int[MAX_PROCESS][MAX_RADIX];
		
		num = MAX_NUM;
		log2_radix = 4;
		radix = MAX_RADIX;
		
		record = new Vector[MAX_PROCESS][MAX_RADIX];
		for(int i = 0; i<MAX_PROCESS; i++)
			for(int j= 0; j< MAX_RADIX; j++)
			{
				record[i][j] = new Vector();
			}
	}
	public void getData(){

		
		Random ra = new Random();
		for(int i = 0; i<num; i++)
			tmp_data[i] = data[i] = ra.nextInt(0xFFFF);
	}
	
	public void radixSort(int begin, int end, int id, int itr)
	{
		itr *= log2_radix;
		
		//int t = radix -1;
		for(int i = begin; i<end; i++)
		{
			int tmp = (data[i]>> itr)&15;
			record[id][tmp].addElement(data[i]);
		}
	}
	
	public void writeBack(int begin, int end, int id)
	{
		for(int i = 0; i<radix; ++i)
		{
			for(int j = 0, x = cnt[id][i], t = record[id][i].size(); j<t; ++j)
			{
				tmp_data[x++] =  (Integer)record[id][i].elementAt(j);// here may be wrong!!
			}
		}
	}
	
	public void calCount()
	{
		for(int i = 0; i<MAX_PROCESS; i++)
		{
			for(int j = 0; j < radix; j++)
				cnt[i][j] = record[i][j].size();
		}
		
		for(int i = 0; i < radix; i++)
		{
			if(i != 0) // if(i)
				cnt[0][i] += cnt[MAX_PROCESS - 1][i - 1];
			
			for(int j = 1; j < MAX_PROCESS; j++)
				cnt[j][i] += cnt[j - 1][i];
		}
		
		for(int i = radix -1; i>=0; i--)
		{
			for(int j = MAX_PROCESS - 1; j > 0; j--)
				cnt[j][i] = cnt[j-1][i];
			
			if(i == 0) break;
			cnt[0][i] = cnt[MAX_PROCESS - 1][i - 1];
		}
		cnt[0][0] = 0;
	}
	
}
