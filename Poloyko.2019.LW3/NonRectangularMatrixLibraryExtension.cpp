#include <iostream>
#include "NonRectangularMatrixLibrary.h"

using namespace std;


double** NonRectangularMatrixExtention::allocateMemory(int rows, int* dimensions)
{
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}
	if (dimensions == nullptr)
	{
		throw std::invalid_argument("Dimension array can not be null.");
	}

	double** matrix = new double*[rows];

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[dimensions[i]];
	}

	return matrix;
}

void NonRectangularMatrixExtention::displayArray(double* array, int n)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	for (double* p = array; p < array + n; p++)
	{
		std::cout << *p << " ";
	}

	cout << endl;
}

void NonRectangularMatrixExtention::displayMatrix(double** matrix, int rows, int* dimensions)
{
	if (matrix == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}

	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}

	if (dimensions == nullptr)
	{
		throw std::invalid_argument("Dimension array can not be null.");
	}
	
	for (int i = 0; i < rows; i++)
	{
		NonRectangularMatrixExtention::displayArray(matrix[i], dimensions[i]);
		cout <<endl;
	}
}

void NonRectangularMatrixExtention::fillMatrix(double** matrix, int rows, int* dimensions)
{
	if (matrix == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}
	if (dimensions == nullptr)
	{
		throw std::invalid_argument("Dimension array can not be null.");
	}
	for (int i = 0; i < rows; i++)
	{
		cout << "Inputing " << i + 1 << " row: " << endl;
		for (int j = 0; j < dimensions[i]; j++)
		{
			cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> *(*(matrix + i) + j);
			
		}
	}
}

double* NonRectangularMatrixExtention::allocateMemoryForArray(int n)
{
	if (n <= 0)
	{
		throw std::invalid_argument("Number of elements in an array can not be less or equal 0.");
	}

	double* array = new double[n];
	return array;
}

double* NonRectangularMatrixExtention::deleteElementsInArray(double* array, int& n, int ones, int zeroes, ConditionToIncludeOrDelete condition)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	if (ones <= 0 || zeroes <= 0)
	{
		throw std::invalid_argument("Number of ones and zeroes cannot be less or equal 0.");
	}

	int copy = n;
	int length = 0;
	for (double *p = array; p < array + n; p++)
	{
		if (condition(*p, ones, zeroes))
		{
			length++;
		}
	}

	double* newArray = allocateMemoryForArray(length);


	for (int i = 0, j = 0; i < copy; i++)
	{
		if (!(condition(array[i], ones, zeroes)))
		{
			newArray[j] = array[i];
			j++;
		}
		else n--;
	}
	return newArray;
}

double** NonRectangularMatrixExtention::deleteElementsInMatrix(double** matrix, int rows, int* dimensions,int ones, int zeroes, int* rowsToSort,ConditionToIncludeOrDelete condition)
{
	if (matrix == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}
	if (dimensions == nullptr)
	{
		throw std::invalid_argument("Dimension of an array can not be null.");
	}
	if (rowsToSort == nullptr)
	{
		throw std::invalid_argument("Dimension of an array can not be null.");
	}

	for (int i = 0, j = 0; i < rows; i++)
	{
		if (i == rowsToSort[j])
		{
			matrix[i] = deleteElementsInArray(matrix[i], dimensions[i], ones, zeroes, condition);
			j++;
		}
	}
	return matrix;
}
