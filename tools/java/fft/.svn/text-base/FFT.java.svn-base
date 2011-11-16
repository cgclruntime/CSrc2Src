import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


/*usage
 * 
 *  ./FFT max_num process_num len
 */
public class FFT {
	public static void main(String args[])
	{
		if(args.length!=3)
		{
			System.out.println("wrong args!  Usage \n ./FFT max_num process_num len");
			return ;
		}
		int max_num = Integer.valueOf(args[0]);
		int process_num = Integer.valueOf(args[1]);
		int len = Integer.valueOf(args[2]);
		
		
		FFTData fft = new FFTData(max_num, process_num, len);	//FFTData(int max_num, int process_num, int len_)
		
		fft.generateData(len);
		
		long begintime = System.currentTimeMillis();
		
		fft.FFT(len, 1);
		long endtime = System.currentTimeMillis();
		
		long costtime = endtime - begintime ;
		
		System.out.println(1.0*costtime / 1000);
	}
}
