import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class FFTData {
	public double data[][];
	public double tmp[][];
	public int MAX_NUM;
	public int PROCESS_NUM;
	public static double pi = 3.14159265354;
	
	public int len;
	public FFTData(int max_num, int process_num, int len_){
		MAX_NUM = max_num;
		PROCESS_NUM = process_num;
		len = len_;
		data = new double[MAX_NUM][2];
		tmp = new double[MAX_NUM][2];
	}
	
	public void complexMul(double a[], double b[], double c[])
	{
		double t0, t1;
		t0 = a[0] * b[0] - a[1]*b[1];
		t1 = a[1] * b[0] + a[0]*b[1];
		c[0] = t0;
		c[1] = t1;
	}
	
	public void complexAdd(double a[], double b[], double c[])
	{
		c[0] = a[0] + b[0];
		c[1] = a[1] + b[1];
	}
	
	public void complexSub(double a[], double b[], double c[])
	{
		c[0] = a[0] - b[0];
		c[1] = a[1] - b[1];
	}
	
	public int bit_reverse(int x, int bit_len)
	{
		int res = 0;
		--bit_len;
		for(int i = 0; i <= bit_len; i++)
			if((x & (1 << i))!=0) res |= (1 << (bit_len - i));
		return res;
	}
	
	public void processBitReverse(int begin, int end, int bit_len)
	{
		for(int i = begin; i < end; i++)
		{
			int x = bit_reverse(i, bit_len);
			tmp[x][0] = data[i][0];
			tmp[x][1] = data[i][1];
		}
	}
	
	public void processFFT(int begin, int end, int m, double wm[])
	{
		double w[] = {1, 0};
		while(begin != end)
		{
			if(begin + m >= len) break;
			for(int i = 0; i < m / 2; i++)
			{
				double t[]= {0,0};
				double u[]= {0,0};
				complexMul(w, data[begin + i + m / 2], t);
				u[0] = data[begin + i][0];
				u[1] = data[begin + i][1];
				complexSub(u, t, data[begin + i + m / 2]);
				complexMul(w, wm, w);
			}
			begin += m;
		}
	}
	
	public void FFT(int len, int oper)
	{
		int bit_len = 1;
		while((1 << bit_len) < len) bit_len ++;
		
		Vector thrds = new Vector();
		
		try{
			
		
		for(int i = 0; i < len; i += len / PROCESS_NUM)
		{
			//processBitReverse(i, i + len / PROCESS_NUM, bit_len);
			Thread t = new Thread(new BitReverseProcessor(this, i, i + len / PROCESS_NUM, bit_len));
			thrds.addElement(t);
			t.start();
		}
		
		for(int i = 0; i < thrds.size(); i++)
		{
			((Thread)thrds.get(i)).join();
		}
		thrds.clear();
		
		//memcpy(data, tmp, sizeof(tmp));
		double t[][] = tmp;
		tmp = data;
		data = t;
		
		for(int i = 1; (1 << i) <= len; i++)
		{
			int m = 1 << i;
			double wm[] = {Math.cos(pi * 2 / (double)m), oper * Math.sin(pi * 2 / (double)m)};
			
			for(int j = 1; j < PROCESS_NUM; j++)
			{
				//processFFT(j * len / PROCESS_NUM, (j + 1) * len / PROCESS_NUM, m, wm);
				Thread t1 = new Thread(new FFTProcessor(this, j * len / PROCESS_NUM, (j + 1) * len / PROCESS_NUM, m, wm));
				thrds.addElement(t1);
				t1.start();
			}
			
			for(int k = 0; k < thrds.size(); k++)
			{
				((Thread)thrds.get(k)).join();
			}
			thrds.clear();
		}
		}catch(Exception e)
		{
			System.out.println(" catch exception from FFT");
		}
	}
	
	public void generateData(int len)
	{
		Random ra = new Random();
		for(int i = 0; i < len; i++)
			data[i][0] = ra.nextInt() & 15;
	}
}
