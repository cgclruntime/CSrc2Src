import java.math.*;
import java.io.*;
import java.util.Scanner;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class RadixSorter implements Runnable {

	RadixData m_oRadix;
	int m_iBegin;
	int m_iEnd;
	int m_iId;
	int m_iItr;
	
	
	public RadixSorter(RadixData radix_data, int begin, int end, int id, int itr){
		m_oRadix = radix_data;
		m_iBegin = begin;
		m_iEnd = end;
		m_iId = id;
		m_iItr = itr;
	}
	public void run(){
		m_oRadix.radixSort(m_iBegin, m_iEnd, m_iId, m_iItr);
	}
}
