import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class BitReverseProcessor  implements Runnable{
	
	public FFTData fft;
	int begin;
	int end;
	int bit_len;
	
	public BitReverseProcessor(FFTData fft_, int begin_, int end_, int bit_len_){
		begin = begin_;
		end = end_;
		bit_len = bit_len_;
		fft = fft_;
	}
	
	public void run()
	{
		fft.processBitReverse(begin, end, bit_len);
	}
}
