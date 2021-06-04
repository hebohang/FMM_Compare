#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H
#include <iostream>
void print(int**, int);
int** randomMatrix(int);
float** randomMatrix_f(int);
int** Add(int**, int**, int);
int** Sub(int**, int**, int);
int** slice(int**, int, int, int);
template <typename T> bool clearMatrix(T**, int);
template <typename T>
bool clearMatrix(T** a, int n)
{
	try
	{
		for (int i = 0; i < n; i++)
		{
			delete[] a[i];
		}
		delete[] a;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}

#endif