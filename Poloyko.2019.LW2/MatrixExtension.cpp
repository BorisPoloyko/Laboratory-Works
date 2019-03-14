#include <iostream>
#include "MatrixLibrary.h"

using namespace std;

double** MatrixExtension::createMatrix(int columns, int rows)
{
	if (rows <= 0 || columns <=0)
	{
		throw std::invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
	}
	double** matrix = new double*[columns];
	for (int i = 0; i < columns; ++i)
	{
		matrix[i] = new double[rows];
	}
	return matrix;
}

void  MatrixExtension::displayMatrix(double** matrix,int columns, int rows)
{
	if (rows <= 0 || columns <= 0)
	{
		throw std::invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
	}
	if (matrix == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			cout.width(15);
			cout << *(*(matrix + i) + j);
		}
		cout << endl;
	}
}

double** MatrixExtension::fillMatrix(double** matrix, int columns, int rows, MatrixType type)
{
	if (matrix == nullptr)
	{
		throw invalid_argument("Matrix can not be null.");
	}

	if (rows <= 0 || columns <= 0)
	{
		throw invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
	}

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			*(*(matrix + i) + j) = type(i, j);
		}
	}

	return matrix;
}

double MatrixExtension::matrixComparisonByDifference(double** matrixA, double** matrixB, int columns, int rows)
{
	if (matrixA == nullptr || matrixB == nullptr)
	{
		throw invalid_argument("Matrix can not be null.");
	}

	if (rows <= 0 || columns <= 0)
	{
		throw invalid_argument("Number of rows and columns in a matrix can not be less or equal to 0.");
	}
	double maxDifference = 0;
	for (int i = 0; i < columns; i++)
	{
		double difference = 0;
		for (int j = 0; j < rows; j++)
		{
			difference = *(*(matrixA + i) + j) - *(*(matrixB + i) + j);
			if (difference > maxDifference)
			{
				maxDifference = difference;
			}
		}
	}

	return maxDifference;
}
