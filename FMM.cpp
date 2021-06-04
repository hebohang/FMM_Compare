/**
 * @file matrix.cpp
 * @author wango
 * @brief matrix multiplication
 * @version 0.1
 * @date 2020-03-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <string>
#include <iomanip>
#include <iostream>
#include <time.h>
#include "common_func.h"
#include "traditionMM.h"
#include "strassen.h"
#include "winogradMatrixMulti.h"

using namespace std;









//int main()
//{
//	cout << "==================================Begin Test(s)====================================" << endl;
//	cout << setw(16) << "N" /*<< setw(16) << "Traditional"*/ /*<< setw(16) << "Traditional_2"*/ << setw(16) << "Strassen" /*<< setw(16) << "Winograd"*/ << endl;
//	int** result;
//	// compute    average 3
//	for (int i = 2; i < 1024 * 64; i = 2 * i)
//	{
//		int** a = randomMatrix(i);
//		//sleep(1);
//		int** b = randomMatrix(i);
//
//		clock_t start = clock();
//		/*for (int j = 0; j < 1; j++)
//		{
//			result = tradMatrixMulti(a, b, i);
//			clearMatrix(result, i);
//		}*/
//		clock_t end = clock();
//		/*double trad = double(end - start) / 1 / CLOCKS_PER_SEC;*/
//
//
//
//		/*start = clock();
//		for (int j = 0; j < 1; j++)
//		{
//			result = tradMatrixMulti_2(a, b, i);
//			clearMatrix(result, i);
//		}
//		end = clock();
//		double trad_2 = double(end - start) / 1 / CLOCKS_PER_SEC;*/
//
//		start = clock();
//		for (int j = 0; j < 1; j++)
//		{
//			result = strassenMatrixMulti(a, b, i);
//			clearMatrix(result, i);
//		}
//		end = clock();
//		double stra = double((end - start)) / 1 / CLOCKS_PER_SEC;
//
//		/*start = clock();
//		for (int j = 0; j < 1; j++)
//		{
//			result = winogradMatrixMulti(a, b, i);
//			clearMatrix(result, i);
//		}
//		end = clock();
//		double winog = double((end - start)) / 1 / CLOCKS_PER_SEC;*/
//
//
//		cout << setw(16) << i /*<< setw(16) << setprecision(4) << fixed << 'trad' << setw(16) << setprecision(4) << fixed << trad_2*/ << setw(16) << setprecision(4) << fixed << stra /*<< setw(16)  << setprecision(4) << fixed << winog */<< endl;
//		clearMatrix(a, i);
//		clearMatrix(b, i);
//	}
//
//	//// evaluate the correctness of strassen
//	//cout << "===================Evaluate Correctness====================" << endl;
//	//for (int i = 5; i < 9; i = i + 1)
//	//{
//	//	int** a = randomMatrix(i);
//	//	// for generate different matrix
//	//	// sleep(1);
//	//	int** b = randomMatrix(i);
//	//	int** c = tradMatrixMulti(a, b, i);
//	//	cout << "下面是a:" << endl;
//	//	print(a, i);
//	//	cout << "下面是b" << endl;
//	//	print(b, i);
//	//	cout << "GEMM:" << endl;
//	//	print(c, i);
//	//	int** d = strassenMatrixMulti(a, b, i, 1);
//	//	cout << "strassen:" << endl;
//	//	print(d, i);
//	//	int** e = winogradMatrixMulti(a, b, i, 1);
//	//	cout << "winograd:" << endl;
//	//	print(e, i);
//	//}
//
//	//srand((unsigned)time(NULL));
//	//int** a = new int* [2];
//	//for (int i = 0; i < 2; i++)
//	//{
//	//	a[i] = new int[2];
//	//	for (int j = 0; j < 2; j++)
//	//	{
//	//		a[i][j] = 1;
//	//	}
//	//}
//	//int** b = new int* [2];
//	//for (int i = 0; i < 2; i++)
//	//{
//	//	b[i] = new int[2];
//	//	for (int j = 0; j < 2; j++)
//	//	{
//	//		b[i][j] = 1;
//	//	}
//	//}
//	//int** c = tradMatrixMulti(a, b, 2);
//	//cout << "下面是a:" << endl;
//	//print(a, 2);
//	//cout << "下面是b" << endl;
//	//print(b, 2);
//	//cout << "GEMM:" << endl;
//	//print(c, 2);
//	//int** d = strassenMatrixMulti(a, b, 2, 1);
//	//cout << "strassen:" << endl;
//	//print(d, 2);
//	//int** e = winogradMatrixMulti(a, b, 2, 1);
//	//cout << "winograd:" << endl;
//	//print(e, 2);
//
//
//	return 0;
//}
