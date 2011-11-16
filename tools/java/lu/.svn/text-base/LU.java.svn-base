import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class LU {

	public static void main(String args[])
	{
		LUData lu = new LUData();
		lu.Init();
		
		//memcpy(D, A, sizeof(A));
		System.arraycopy(lu.A, 0, lu.D, 0, lu.A.length);
		
		long begintime = System.currentTimeMillis();
		
		try{
			
		Vector thrds = new Vector();
		
		
		for(int i = 0; i < lu.sizeOfMatrix; i += lu.sizeOfBlock)
		{
			lu.LUDecompose(i);
			//lu.getInverseL(i);
			//lu.getInverseU(i);
			
			int id = 0;
			
			for(int j = i + lu.sizeOfBlock; j < lu.sizeOfMatrix; j += lu.sizeOfBlock)
			{
				//lu.updateLU(i, j, lu.tmp[id]);
				Thread t1 = new Thread(new LUUpdater(lu, i, j, lu.tmp[id]));
				thrds.addElement(t1);
				t1.start();
				id ++;
			}
			
			for(int k = 0; k<thrds.size(); ++k)
			{
				((Thread)thrds.get(k)).join();
			}
			thrds.clear();
			
			
			id = 0; 
			for(int j = i+lu.sizeOfBlock; j< lu.sizeOfMatrix; j+= lu.sizeOfBlock)
				for(int k = i+lu.sizeOfBlock; k < lu.sizeOfMatrix; k += lu.sizeOfBlock)
				{
					//lu.updateD(j, k, i, lu.tmp[id++]);
					Thread t1 = new Thread(new DUpdater(lu, j, k, i, lu.tmp[id++]));
					thrds.addElement(t1);
					t1.start();
				}
			
			for(int k = 0; k<thrds.size(); ++k)
			{
				((Thread)thrds.get(k)).join();
			}
			thrds.clear();
		}
		}catch(Exception e){
			System.out.println("Exception ");
		}
		long endtime = System.currentTimeMillis();
		
		long costtime = endtime - begintime ;
		
		System.out.println("Over, running time is ");
		System.out.println(1.0 * costtime/1000);
		
		
		for(int i = 0; i < lu.sizeOfMatrix; i++)
		{
			lu.B[i][i] = 1;
			for(int j = 0; j < i; j++)
				lu.B[i][j] = lu.A[i][j];
			for(int j = i; j < lu.sizeOfMatrix; j++)
				lu.C[i][j] = lu.A[i][j];
		}
		for(int i = 0; i < lu.sizeOfMatrix; i++)
			for(int j = 0; j < lu.sizeOfMatrix; j++)
				for(int k = 0; k < lu.sizeOfMatrix; k++)
					lu.D[i][j] -= lu.B[i][k] * lu.C[k][j];
		for(int i = 0; i < lu.sizeOfMatrix; i++)
			for(int j = 0; j < lu.sizeOfMatrix; j++) if(Math.abs(lu.D[i][j]) < 100)
				System.out.println("Error!");
		System.out.println("Right!");
	}
}
