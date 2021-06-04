#include <iostream>
#include "traditionMM.h"
using namespace std;

/**
 * @brief traditional matrix multiplication
 *
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result
 */
int** tradMatrixMulti(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n]();
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

