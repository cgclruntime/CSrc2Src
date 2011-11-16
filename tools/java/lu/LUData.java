import java.math.*;
import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.io.File;
import java.*;
import java.io.*;
import java.util.*;


public class LUData {
	public int sizeOfMatrix = 1 << 10;
	public int sizeOfBlock = 1 << 10;
	public int numOfBlock = sizeOfMatrix / sizeOfBlock;
	
	double tmp[][][];
	double _L[][];
	double _U[][];
	double D[][];
	double A[][];
	double B[][];
	double C[][];
	
	public void Init()
	{
		sizeOfMatrix = 1 << 10;
		sizeOfBlock = 1 << 6;
		numOfBlock = sizeOfMatrix / sizeOfBlock;
		
		tmp = new double[numOfBlock * numOfBlock][sizeOfBlock][sizeOfBlock];
		_L = new double[sizeOfBlock][sizeOfBlock];
		_U = new double[sizeOfBlock][sizeOfBlock];
		D = new double[sizeOfMatrix][sizeOfMatrix];
		A = new double[sizeOfMatrix][sizeOfMatrix];
		B = new double[sizeOfMatrix][sizeOfMatrix];
		C = new double[sizeOfMatrix][sizeOfMatrix];
		
		Random ra = new Random();
		for(int i = 0; i < sizeOfMatrix; i ++)
		{
			for(int j = 0; j < sizeOfMatrix; j++)
				A[i][j] = ra.nextInt() & 15;
		}
	}
	
	public void getInverseL(int x)
	{
		for(int i = 0; i < sizeOfBlock; ++i)
			for(int j = 0; j < sizeOfBlock; ++j)
				_L[i][j] = 0;
		
		for(int i = 0; i < sizeOfBlock; i++)
			_L[i][i] = 1;
		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < i; j++)
				for(int k = j; k < i; k++)
					_L[i][j] -= A[i + x][k + x] * _L[k][j];
	}
	
	public void getInverseU(int x)
	{
		for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
			_U[i][j] = 0;
		for(int i = 0; i < sizeOfBlock; i++) _U[i][i] = 1 / A[i + x][i + x];
		
		for(int i = sizeOfBlock - 1; i >= 0; i--)
			for(int j = sizeOfBlock - 1; j > i; j--)
				for(int k = i + 1; k <= j; k++)
					_U[i][j] -= A[i + x][k + x] * _U[k][j];

		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = i + 1; j < sizeOfBlock; j++)
				_U[i][j] *= _U[i][i];
	}
	
	public void LUDecompose(int x)
	{
		int m = sizeOfBlock + x;
		for(int i = x; i < m; i++)	
		{
			for(int j = i + 1; j < m; j++) A[j][i] /= A[i][i];
			
			for(int j = i + 1; j < m; j++)
			for(int k = i + 1; k < m; k++)
				A[j][k] -= A[j][i] * A[i][k];
		}
	}
	public void updateL(int x, int y, double tmp[][])
	{
		for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
			tmp[i][j] = 0;
		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				for(int k = 0; k < sizeOfBlock; k++)
					tmp[i][j] += _L[i][k] * A[k + x][j + y];
		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				A[i + x][j + y] = tmp[i][j];
	}
	
	public void updateU(int x, int y, double tmp[][])
	{
		for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
			tmp[i][j] = 0;
		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				for(int k = 0; k < sizeOfBlock; k++)
					tmp[i][j] += A[i + x][k + y] * _U[k][j];

		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				A[i + x][j + y] = tmp[i][j];
	}
	
	public void updateLU(int x, int y, double tmp[][])
	{
		updateL(x, y, tmp);
		updateU(y, x, tmp);
	}
	
	public void updateD(int x, int y, int b, double tmp[][])
	{
		for(int i = 0; i < sizeOfBlock; i++) for(int j = 0; j < sizeOfBlock; j++)
			tmp[i][j] = 0;
		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				for(int k = 0; k < sizeOfBlock; k++)
					tmp[i][j] += A[i + x][b + k] * A[b + k][j +y];

		for(int i = 0; i < sizeOfBlock; i++)
			for(int j = 0; j < sizeOfBlock; j++)
				A[i + x][j + y] -= tmp[i][j];
	}
	
	
}
