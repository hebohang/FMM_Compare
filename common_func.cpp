#include "common_func.h"
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * @brief print matrix
 *
 * @param a matrix
 * @param n size
 */
void print(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/**
 * @brief generate random matrix (size n)
 *
 * @param n size
 * @return int** matrix pointer
 */
int** randomMatrix(int n)
{
	srand((unsigned)time(NULL));
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 10;
		}
	}
	return a;
}

float** randomMatrix_f(int n)
{
	srand((unsigned)time(NULL));
	float** a = new float* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() / FLT_MAX;
		}
	}
	return a;
}


/**
 * @brief matrix add
 *
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result
 */
int** Add(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

/**
 * @brief matrix sub
 *
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result
 */
int** Sub(int** a, int** b, int n)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}

/**
 * @brief slice of Matrix
 *
 * @param a original matrix
 * @param n size
 * @param startX slice start point X
 * @param startY slice start point Y
 * @return int** result
 */
int** slice(int** a, int n, int startX, int startY)
{
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			c[i][j] = a[startX + i][startY + j];
		}
	}
	return c;
}

/**
 * @brief free the malloc space
 *
 * @param a matrix
 * @param n size
 * @return true Success
 * @return false Error
 */
