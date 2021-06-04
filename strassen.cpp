#include <iostream>
#include "strassen.h"
#include "common_func.h"
#include "traditionMM.h"
using namespace std;


/**
 * @brief StrassenMatrix multiplication
 *
 * @param OP Left
 * @param OP Right
 * @param n size
 * @param flag for distinguish testing and compute, default 0 for compute
 * @return int** result
 */
int** strassenMatrixMulti(int** op1, int** op2, int n, int flag)
{
	if (n < 500 && !flag)
	{
		return tradMatrixMulti(op1, op2, n);
	}

	if (n == 1)
	{
		int** c = new int* [1];
		c[0] = new int[1];
		c[0][0] = op1[0][0] * op2[0][0];
		return c;
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

	// P1
	int** temp = Sub(f, h, n / 2);
	int** P1 = strassenMatrixMulti(a, temp, n / 2, flag);
	clearMatrix(temp, n / 2);

	// P2
	temp = Add(a, b, n / 2);
	int** P2 = strassenMatrixMulti(temp, h, n / 2, flag);
	clearMatrix(temp, n / 2);

	// P3
	temp = Add(c, d, n / 2);
	int** P3 = strassenMatrixMulti(temp, e, n / 2, flag);
	clearMatrix(temp, n / 2);

	// P4
	temp = Sub(g, e, n / 2);
	int** P4 = strassenMatrixMulti(d, temp, n / 2, flag);
	clearMatrix(temp, n / 2);

	// P5
	temp = Add(a, d, n / 2);
	int** temp1 = Add(e, h, n / 2);
	int** P5 = strassenMatrixMulti(temp, temp1, n / 2, flag);
	clearMatrix(temp, n / 2);
	clearMatrix(temp1, n / 2);

	// P6
	temp = Sub(b, d, n / 2);
	temp1 = Add(g, h, n / 2);
	int** P6 = strassenMatrixMulti(temp, temp1, n / 2, flag);
	clearMatrix(temp, n / 2);
	clearMatrix(temp1, n / 2);

	clearMatrix(b, n / 2);
	clearMatrix(d, n / 2);
	clearMatrix(g, n / 2);
	clearMatrix(h, n / 2);

	// P7
	temp = Sub(a, c, n / 2);
	temp1 = Add(e, f, n / 2);
	int** P7 = strassenMatrixMulti(temp, temp1, n / 2, flag);
	clearMatrix(temp, n / 2);
	clearMatrix(temp1, n / 2);

	clearMatrix(a, n / 2);
	clearMatrix(c, n / 2);
	clearMatrix(e, n / 2);
	clearMatrix(f, n / 2);

	// r
	int** r1 = Add(P5, P4, n / 2);
	int** r2 = Sub(r1, P2, n / 2);
	clearMatrix(r1, n / 2);
	int** r = Add(r2, P6, n / 2);
	clearMatrix(r2, n / 2);
	// int **r = Add(Sub(Add(P5, P4, n / 2), P2, n / 2), P6, n / 2);
	int** s = Add(P1, P2, n / 2);
	int** t = Add(P3, P4, n / 2);

	int** u1 = Add(P5, P1, n / 2);
	int** u2 = Sub(u1, P3, n / 2);
	clearMatrix(u1, n / 2);
	int** u = Sub(u2, P7, n / 2);
	clearMatrix(u2, n / 2);
	// int **u = Sub(Sub(Add(P5, P1, n / 2), P3, n / 2), P7, n / 2);

	clearMatrix(P1, n / 2);
	clearMatrix(P2, n / 2);
	clearMatrix(P3, n / 2);
	clearMatrix(P4, n / 2);
	clearMatrix(P5, n / 2);
	clearMatrix(P6, n / 2);
	clearMatrix(P7, n / 2);

	int m = isEven ? n : n - 1;
	int** Res = new int* [m];
	for (int i = 0; i < m; i++)
	{
		Res[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			if (i < n / 2 && j < n / 2)
			{
				Res[i][j] = r[i][j];
			}
			else if (i < n / 2 && j >= n / 2)
			{
				Res[i][j] = s[i][j - n / 2];
			}
			else if (i >= n / 2 && j < n / 2)
			{
				Res[i][j] = t[i - n / 2][j];
			}
			else
			{
				Res[i][j] = u[i - n / 2][j - n / 2];
			}
		}
	}

	clearMatrix(r, n / 2);
	clearMatrix(s, n / 2);
	clearMatrix(t, n / 2);
	clearMatrix(u, n / 2);
	return Res;
}