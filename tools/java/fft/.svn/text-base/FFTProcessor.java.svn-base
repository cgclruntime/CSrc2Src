import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class FFTProcessor implements Runnable {
	FFTData fft;
	int begin;
	int end;
	int m;
	double wm[];
	public FFTProcessor(FFTData fft_, int begin_, int end_, int m_, double wm_[])
	{
		fft = fft_;
		begin = begin_;
		end = end_;
		m = m_;
		wm = wm_;
	}
	
	public void run()
	{
		fft.processFFT(begin, end, m, wm);
	}
}
