#include <iostream>
#include "traditionMM.h"
#include "common_func.h"
#include "winogradMatrixMulti.h"
using namespace std;

//Winograd's Variant
int** winogradMatrixMulti(int** op1, int** op2, int n, int flag)
{
	if (n < 500 && !flag)
	{
		return tradMatrixMulti(op1, op2, n);
	}

	if (n == 1)
	{
		int** re = new int* [1];
		re[0] = new int[1];
		re[0][0] = op1[0][0] * op2[0][0];
		return re;
	}


	// Judge n even or odd
	bool isEven = true;
	int** oldOP1 = op1;
	int** oldOP2 = op2;
	// odd condition
	if (n % 2 == 1)
	{
		isEven = false;
		int** newOP1 = new int* [n + 1];
		int** newOP2 = new int* [n + 1];
		for (int i = 0; i < n; i++)
		{
			newOP1[i] = new int[n + 1];
			newOP2[i] = new int[n + 1];
			newOP1[i][n] = 0;
			newOP2[i][n] = 0;
			for (int j = 0; j < n; j++)
			{
				newOP1[i][j] = op1[i][j];
				newOP2[i][j] = op2[i][j];
			}
		}
		newOP1[n] = new int[n + 1]{ 0 };
		newOP2[n] = new int[n + 1]{ 0 };
		op1 = newOP1;
		op2 = newOP2;
		n += 1;
	}

	// create a,b,c,d,e,f,g,h
	int** a = slice(op1, n / 2, 0, 0);
	int** b = slice(op1, n / 2, 0, n / 2);
	int** c = slice(op1, n / 2, n / 2, 0);
	int** d = slice(op1, n / 2, n / 2, n / 2);
	int** e = slice(op2, n / 2, 0, 0);
	int** f = slice(op2, n / 2, 0, n / 2);
	int** g = slice(op2, n / 2, n / 2, 0);
	int** h = slice(op2, n / 2, n / 2, n / 2);

	if (!isEven)
	{
		clearMatrix(op1, n);
		clearMatrix(op2, n);
		op1 = oldOP1;
		op2 = oldOP2;
	}

	// S3
	int** C11 = Sub(a, c, n / 2); // ÐÂ¿ª±Ù¿Õ¼äC11
	//cout << "S3:" << endl;
	//print(C11, n / 2);

	// S1
	// int **S1 = c;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			c[i][j] = c[i][j] + d[i][j];
		}
	}
	//cout << "S1:" << endl;
	//print(S1, n / 2);


	// T1
	int** C22 = Sub(f, e, n / 2);
	//cout << "T1:" << endl;
	//print(C22, n / 2);


	// T3
	// int **T3 = f;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			f[i][j] = h[i][j] - f[i][j];
		}
	}
	//cout << "T3:" << endl;
	//print(T3, n / 2);


	// P7
	C11 = winogradMatrixMulti(C11, f, n / 2, flag);
	// int **P7 = C11;
	//cout << "P7:" << endl;
	//print(P7, n / 2);


	// P1
	e = winogradMatrixMulti(a, e, n / 2, flag);
	// int **P1 = e;
	//cout << "P1:" << endl;
	//print(P1, n / 2);


	// S2
	// int **S2 = a;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			a[i][j] = c[i][j] - a[i][j];
		}
	}
	//cout << "S2:" << endl;
	//print(S2, n / 2);


	// P5
	c = winogradMatrixMulti(c, C22, n / 2, flag);
	// int **P5 = c;
	//cout << "P5:" << endl;
	//print(P5, n / 2);


	// T2
	// int **T2 = C22;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C22[i][j] = h[i][j] - C22[i][j];
		}
	}
	//cout << "T2:" << endl;
	//print(T2, n / 2);


	// P2
	f = winogradMatrixMulti(b, g, n / 2, flag);
	// int **P2 = f;
	//cout << "P2:" << endl;
	//print(P2, n / 2);


	// T4
	// int **T4 = g;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			g[i][j] = C22[i][j] - g[i][j];
		}
	}
	//cout << "T4:" << endl;
	//print(T4, n / 2);


	// P6
	C22 = winogradMatrixMulti(a, C22, n / 2, flag);
	// int **P6 = C22;
	//cout << "P6:" << endl;
	//print(P6, n / 2);


	// S4
	// int **S4 = b;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			b[i][j] = b[i][j] - a[i][j];
		}
	}
	//cout << "S4:" << endl;
	//print(S4, n / 2);


	// P3
	h = winogradMatrixMulti(b, h, n / 2, flag);
	// int **P3 = h;
	//cout << "P3:" << endl;
	//print(P3, n / 2);


	// U1
	// int **U1 = f;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			f[i][j] = e[i][j] + f[i][j];
		}
	}
	//cout << "U1:" << endl;
	//print(U1, n / 2);


	// U2
	// int **U2 = e;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			e[i][j] = e[i][j] + C22[i][j];
		}
	}
	//cout << "U2:" << endl;
	//print(U2, n / 2);



	// U3
	// int **U3 = C11;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C11[i][j] = e[i][j] + C11[i][j];
		}
	}
	//cout << "U3:" << endl;
	//print(U3, n / 2);


	// U4
	// int **U4 = e;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			e[i][j] = e[i][j] + c[i][j];
		}
	}
	//cout << "U4:" << endl;
	//print(U4, n / 2);


	// U7
	// int **U7 = c;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			c[i][j] = C11[i][j] + c[i][j];
		}
	}
	//cout << "U7:" << endl;
	//print(U7, n / 2);


	// U5
	// int **U5 = h;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			h[i][j] = e[i][j] + h[i][j];
		}
	}
	//cout << "U5:" << endl;
	//print(U5, n / 2);


	// P4
	d = winogradMatrixMulti(d, g, n / 2, flag);
	// int **P4 = d;
	//cout << "P4:" << endl;
	//print(P4, n / 2);


	// U6
	// int **U6 = d;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			d[i][j] = C11[i][j] - d[i][j];
		}
	}
	//cout << "U6:" << endl;
	//print(U6, n / 2);


	clearMatrix(C11, n / 2);
	clearMatrix(C22, n / 2);
	clearMatrix(a, n / 2);
	clearMatrix(b, n / 2);
	clearMatrix(e, n / 2);
	clearMatrix(g, n / 2);


	int m = isEven ? n : n - 1;
	int** Res = new int* [m];
	for (int i = 0; i < m; i++)
	{
		Res[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			if (i < n / 2 && j < n / 2)
			{
				Res[i][j] = f[i][j];
			}
			else if (i < n / 2 && j >= n / 2)
			{
				Res[i][j] = h[i][j - n / 2];
			}
			else if (i >= n / 2 && j < n / 2)
			{
				Res[i][j] = d[i - n / 2][j];
			}
			else
			{
				Res[i][j] = c[i - n / 2][j - n / 2];
			}
		}
	}

	clearMatrix(f, n / 2);
	clearMatrix(h, n / 2);
	clearMatrix(d, n / 2);
	clearMatrix(c, n / 2);
	return Res;
}
