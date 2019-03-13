#include <iostream>
#include "MatrixLibrary.h"

using namespace std;

double** MatrixExtension::createSquareMatrix(int n)
{
	double** matrix = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = new double[n];
	}
	return matrix;
}

void  MatrixExtension::displaySquareMatrix(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout.width(15);
			cout << *(*(matrix + i) + j);
		}
		cout << endl;
	}
}

double** MatrixExtension::fillSquareMatrix(double** matrix, int n, MatrixType type)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			*(*(matrix + i) + j) = type(i, j);
		}
	}
	return matrix;
}

double MatrixExtension::matrixNorm(double** matrix, int n)
{
	double maxColumnNorm = 0;
	for (int j = 0; j < n; j++)
	{
		double columnNorm = 0;
		for (int i = 0; i < n; i++)
		{
			columnNorm += abs(*(*(matrix + i) + j));
		}
		if (columnNorm > maxColumnNorm)
		{
			maxColumnNorm = columnNorm;
		}
	}

	double maxRowNorm = 0;
	for (int i = 0; i < n; i++)
	{
		double rawNorm = 0;
		for (int j = 0; j < n; j++)
		{
			rawNorm += abs(*(*(matrix + i) + j));
		}
		if (rawNorm > maxRowNorm)
		{
			maxRowNorm = rawNorm;
		}
	}
	
	return (maxColumnNorm > maxRowNorm) ? maxColumnNorm : maxRowNorm;
}

double MatrixExtension::matrixComparison(double** matrixA, double** matrixB, int n, Attribute attribute)
{
	return  attribute(matrixA, n) - attribute(matrixB, n);
}
