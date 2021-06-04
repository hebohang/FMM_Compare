#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

bool clearMatrix(double** a, int n)
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


double** randomMatrix_double(int n)
{
	srand((unsigned)time(NULL));
	double** a = new double* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() / double(RAND_MAX);
		}
	}
	return a;
}


double** tradMatrixMulti_double(double** a, double** b, double n)
{
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new double[n]();
		for (int k = 0; k < n; k++)
		{
			double temp = a[i][k];
			for (int j = 0; j < n; j++)
			{
				c[i][j] += temp * b[k][j];
			}
		}
	}
	return c;
}

double** tradMatrixMulti_MixedMul(double** a, double** b, double n)
{
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new double[n]();
		for (int k = 0; k < n; k++)
		{
			float temp = a[i][k];
			for (int j = 0; j < n; j++)
			{
				c[i][j] += temp * b[k][j];
			}
		}
	}
	return c;
}


int main()
{
	cout << "==================================Begin Test(s)====================================" << endl;
	cout << setw(16) << "N" /*<< setw(16) << "Traditional"*/ << setw(16) << "double" << setw(16) << "Mixdouble"  << endl;
	double** result;
	// compute    average 3
	for (int i = 2; i < 1024 * 64; i = 2 * i)
	{
		double** a = randomMatrix_double(i);
		//sleep(1);
		double** b = randomMatrix_double(i);

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
			result = tradMatrixMulti_double(a, b, i);
			clearMatrix(result, i);
		}
		end = clock();
		double trad_double = double(end - start) / 1 / CLOCKS_PER_SEC;

		start = clock();
		for (int j = 0; j < 1; j++)
		{
			result = tradMatrixMulti_MixedMul(a, b, i);
			clearMatrix(result, i);
		}
		end = clock();
		double trad_Mix = double(end - start) / 1 / CLOCKS_PER_SEC;



		cout << setw(16) << i /*<< setw(16) << setprecision(4) << fixed << 'trad' */<< setw(16) << setprecision(4) << fixed << trad_double << setw(16) << setprecision(4) << fixed << trad_Mix  << endl;
		clearMatrix(a, i);
		clearMatrix(b, i);
	}


	return 0;
}