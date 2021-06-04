#ifndef TRADITIONMM_H
#define TRADITIONMM_H
int** tradMatrixMulti(int**, int**, int);
template <typename T> T** tradMatrixMulti_2(T**, T**, int);
// 类模板直接在.h中定义，防止报错
template <typename T>
T** tradMatrixMulti_2(T** a, T** b, int n)
{
	T** c = new T * [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new T[n]();
		for (int k = 0; k < n; k++)
		{
			T temp = a[i][k];
			for (int j = 0; j < n; j++)
			{
				c[i][j] += temp * b[k][j];
			}
		}
	}
	return c;
}
#endif

