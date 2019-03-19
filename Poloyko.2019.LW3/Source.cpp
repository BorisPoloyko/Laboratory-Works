#include <iostream>
#include "NonRectangularMatrixLibrary.h"

using namespace std;
using namespace NonRectangularMatrixExtention;

typedef bool(*predicate)(double, double);

void mergeSort(double*, int, int, predicate);
void merge(double*, int, int, int, predicate);

int inputRows();
int* inputDimensions(int);
int* InputRowsToSort(int);

double* allocateMemoryForArray(int);

void sortMatrix(double**,  int , int* , int* );

bool ifNumberOfOnesGreater(double, double);
int numberOnes(double);
int numberZeroes(double);

int main()
{
	int rows = inputRows();
	int* dimensions = inputDimensions(rows);
	double** matrix = allocateMemory(rows, dimensions);
	fillMatrix(matrix, rows, dimensions);
	displayMatrix(matrix, rows, dimensions);
	int* rowsToSort = InputRowsToSort(rows);
	sortMatrix(matrix, rows, dimensions, rowsToSort);
	displayMatrix(matrix, rows, dimensions);


	system("pause");
	return 0;
}


int inputRows()
{
	int rows;
	cout << "Enter the number of rows: ";
	cin >> rows;
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}
	return rows;
}

int* InputRowsToSort(int rows)
{
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}

	cout << "Enter number of the rows to sort: ";
	int numberOfRows;
	cin >> numberOfRows;
	if (numberOfRows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}
	int* rowsToSort = new int[numberOfRows];

	if (rowsToSort == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}
	cout << "Enter indexes of the rows to sort(starting with 1)" << endl;
	for (int i = 0; i < numberOfRows; i++)
	{
		cout << "Inputting the " << i + 1 << " index: ";
		int currentIndex;
		cin >> currentIndex;
		if (currentIndex <= 0);
		{
			throw std::invalid_argument("Index can not be less than 1.");
		}

		rowsToSort[i] = currentIndex - 1;
		cout << endl;
	}

	return rowsToSort;
}

int* inputDimensions(int rows)
{
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}

	int* dimensions = new int[rows];

	if (dimensions == nullptr)
	{
		throw invalid_argument("The dimension of an array can not be 0.");
	}

	cout << "Initializing number of elements in a row..." << endl;
	for (int i = 0; i < rows; i++)
	{	
		cout << "Row " << i + 1 << ": ";
		cin >> dimensions[i];

		if (dimensions[i] <= 0)
		{
			throw invalid_argument("Number of elements in a row can not be less than 0.");
		}
	}
	return dimensions;
}

void merge(double* array, int left, int mid, int right, predicate condition)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (left < 0 || mid < 0 || right < 0)
	{
		throw std::invalid_argument("Left, mid and right parameters can not be less 0.");
	}

	int pos1 = left, pos2 = mid + 1, pos3 = 0;

	double *temp = allocateMemoryForArray(right - left + 1);

	while (pos1 <= mid && pos2 <= right)
	{
		if (condition(array[pos2], array[pos1]))
		{
			temp[pos3++] = array[pos1++];
		}
		else
		{
			temp[pos3++] = array[pos2++];
		}
	}

	while (pos2 <= right)
	{
		temp[pos3++] = array[pos2++];
	}
	while (pos1 <= mid)
	{
		temp[pos3++] = array[pos1++];
	}

	for (pos3 = 0; pos3 < right - left + 1; pos3++)
	{
		array[left + pos3] = temp[pos3];
	}

	delete[] temp;
}

void mergeSort(double* array, int left, int right, predicate condition)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (left < 0 || right < 0)
	{
		throw std::invalid_argument("Left, mid and right parameters can not be less 0.");
	}

	int mid;

	if (left < right)
	{
		mid = left + (right - left) / 2;
		mergeSort(array, left, mid, condition);
		mergeSort(array, mid + 1, right, condition);
		merge(array, left, mid, right, condition);
	}
	else
	{
		return;
	}

}

void sortMatrix(double** matrix,int rows, int* dimensions, int* rowsToSort)
{
	if (rows <= 0)
	{
		throw invalid_argument("Number of rows in a matrix can not be less or equal to 0.");
	}

	if (matrix == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}
	if (dimensions == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}
	if (rowsToSort == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	for (int i = 0, j = 0; i < rows; i++)
	{
		if (i == rowsToSort[j])
		{
			mergeSort(matrix[i], 0, dimensions[i] - 1, ifNumberOfOnesGreater);
			j++;
		}
	}
}

double* allocateMemoryForArray(int n)
{
	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	if (n <= 0)
	{
		return nullptr;
	}
	double* array = new double[n];
	return array;
}

bool ifNumberOfOnesGreater(double a, double b)
{
	return (numberOnes(a) > numberOnes(b));
}

int numberOnes(double a)
{
	int b = a;
	if (b == 1)
	{
		return 1;
	}
	int count = 0;
	while (abs(b))
	{
		if (abs(b) % 2 == 1)
			count++;
		b /= 2;
	}
	return count;
}

int numberZeroes(double a)
{
	int b = a;

	if (b == 0)
	{
		return 1;
	}
	int count = 0;
	while (abs(b))
	{
		if (abs(b) % 2 == 0)
			count++;
		b /= 2;
	}
	return count;
}