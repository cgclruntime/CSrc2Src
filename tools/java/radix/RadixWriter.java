import java.math.*;
import java.io.*;
import java.util.Scanner;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class RadixWriter implements Runnable {

	RadixData m_oRadix;
	int m_iBegin;
	int m_iEnd;
	int m_iId;
	
	
	public RadixWriter(RadixData radix_data, int begin, int end, int id){
		m_oRadix = radix_data;
		m_iBegin = begin;
		m_iEnd = end;
		m_iId = id;
	}
	public void run(){
		m_oRadix.writeBack(m_iBegin, m_iEnd, m_iId);
	}
}