#include <iostream>
#include "traditionMM.h"
#include "common_func.h"
#include <string>
#include <iomanip>
#include <time.h>
#include <cblas.h>
using namespace std;



// 未优化完全
template <typename T>
T** winograd(T** A, T** B, int n, int range)
{	

	if (n < range)
	{
		return tradMatrixMulti_2(A, B, n);
	}


	T** C = new T * [n / 2]();
	T** D = new T * [n / 2]();
	T** E = new T * [n]();
	T** temp = nullptr;
	for (int i = 0; i < n / 2; i++)
	{
		C[i] = new T[n / 2]();
		D[i] = new T[n / 2]();
	}
	for (int i = 0; i < n; i++)
	{
		E[i] = new T[n]();
	}
	// Matrix C(n / 2, n / 2), D(n / 2, n / 2); //开两个n/2 * n/2的矩阵
	// Matrix E(n, n);
	
	//M1
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i][j] + A[i + n / 2][j + n / 2];
			D[i][j] = B[i][j] + B[i + n / 2][j + n / 2];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i][j] += temp[i][j];
			E[i + n / 2][j + n / 2] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M2
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i + n / 2][j] + A[i + n / 2][j + n / 2];
			D[i][j] = B[i][j];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i + n / 2][j + n / 2] -= temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M3
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i][j];
			D[i][j] = B[i][j + n / 2] - B[i + n / 2][j + n / 2];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i][j + n / 2] += temp[i][j];
			E[i + n / 2][j + n / 2] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M4
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i + n / 2][j + n / 2];
			D[i][j] = B[i + n / 2][j] - B[i][j];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i + n / 2][j] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M5
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i][j] + A[i][j + n / 2];
			D[i][j] = B[i + n / 2][j + n / 2];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i][j] -= temp[i][j];
			E[i][j + n / 2] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M6
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i + n / 2][j] - A[i][j];
			D[i][j] = B[i][j] + B[i][j + n / 2];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i + n / 2][j + n / 2] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;

	//M7
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			C[i][j] = A[i][j + n / 2] - A[i + n / 2][j + n / 2];
			D[i][j] = B[i + n / 2][j] + B[i + n / 2][j + n / 2];
		}
	}
	temp = winograd(C, D, n / 2, range);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			E[i][j] += temp[i][j];
		}
	}
	clearMatrix(temp, n / 2);
	temp = nullptr;


	//for (int i = 0; i < 7; i++)
	//{
	//	initiate(C, D, A, B, n / 2); //初始化
	//	winograd(C, D, n / 2); // 计算Pi，将Pi存在A中
	//	modify(E, C, i); //将Pi矩阵修改到答案中
	//}
	
	clearMatrix(C, n / 2);
	clearMatrix(D, n / 2);

	return E;
}


int main()
{
	const enum CBLAS_ORDER Order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const float alpha = 1;
	const float beta = 0;


	cout << "==================================Begin Test(s)====================================" << endl;
	cout << setw(16) << "N" /*<< setw(16) << "Traditional"*/ << setw(16) << "Traditional_2" << setw(16) << "Strassen_256" << setw(16) << "strassen_512" << setw(16) << "blas" << endl;
	float** result;
	// compute    average 3
	for (int i = 2; i < 1024 * 64; i = 2 * i)
	{
		float** a = randomMatrix_f(i);
		//sleep(1);
		float** b = randomMatrix_f(i);

		clock_t start = clock();
		/*for (int j = 0; j < 1; j++)
		{
			result = tradMatrixMulti(a, b, i);
			clearMatrix(result, i);
		}*/
		clock_t end = clock();
		/*double trad = double(end - start) / 1 / CLOCKS_PER_SEC;*/



		start = clock();
		for (int j = 0; j < 1; j++)
		{
			result = tradMatrixMulti_2(a, b, i);
			clearMatrix(result, i);
		}
		end = clock();
		double trad_2 = double(end - start) / 1 / CLOCKS_PER_SEC;

		start = clock();
		for (int j = 0; j < 1; j++)
		{
			result = winograd(a, b, i, 300);
			clearMatrix(result, i);
		}
		end = clock();
		double stra = double(end - start) / 1 / CLOCKS_PER_SEC;

		start = clock();
		for (int j = 0; j < 1; j++)
		{
			result = winograd(a, b, i, 600);
			clearMatrix(result, i);
		}
		end = clock();
		double winog = double(end - start) / 1 / CLOCKS_PER_SEC;

		//const float* A = static_cast<const float*> (&a[0][0]);
		//const float* B = static_cast<const float*> (&b[0][0]);
		//const float A[4] = { 1, 1, 1, 1 };
		//const float B[4] = { 1, 1, 1, 1 };
		float* A = new float[i * i];
		float* B = new float[i * i];
		for (int k = 0; k < i; k++)
		{
			for (int j = 0; j < i; j++)
			{
				A[k * i + j] = a[k][j];
				B[k * i + j] = b[k][j];
			}
		}
		////const float* A = &a[0][0];
		////const float* B = &b[0][0];
		float* C = new float[i * i]();
		start = clock();
		cblas_sgemm(Order, TransA, TransB, i, i, i, alpha, A, i, B, i, beta, C, i);
		end = clock();
		double blas = double(end - start) / 1 / CLOCKS_PER_SEC;
		delete C;
		delete A;
		delete B;



		cout << setw(16) << i /*<< setw(16) << setprecision(4) << fixed << 'trad' */<< setw(16) << setprecision(4) << fixed << trad_2 << setw(16) << setprecision(4) << fixed << stra << setw(16)  << setprecision(4) << fixed << winog << setw(16) << setprecision(4) << fixed << blas << endl;
		clearMatrix(a, i);
		clearMatrix(b, i);



	}


	return 0;
}