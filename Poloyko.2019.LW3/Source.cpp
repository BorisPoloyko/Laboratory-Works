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

void sortMatrix(double**,  int , int* , int*);

bool ifNumberFits(double, int, int);
bool ifNumberOfOnesGreater(double, double);
int numberOnes(double);
int numberZeroes(double);
int inputNumberOfOnes();
int inputNumberOfZeroes();

int main()
{
	int rows = inputRows();
	int* dimensions = inputDimensions(rows);
	double** matrix = allocateMemory(rows, dimensions);
	fillMatrix(matrix, rows, dimensions);
	cout << "Your Matrix: " << endl;
	displayMatrix(matrix, rows, dimensions);
	int* rowsToSort = InputRowsToSort(rows);
	int ones = inputNumberOfOnes(), zeroes = inputNumberOfZeroes();

	sortMatrix(matrix, rows, dimensions, rowsToSort);
	cout << "Sorted Matrix: " << endl;
	displayMatrix(matrix, rows, dimensions);

	cout << "Matrix without chosen elements in chosen rows: " << endl;
	matrix = deleteElementsInMatrix(matrix,  rows, dimensions,  ones,  zeroes, rowsToSort, ifNumberFits);
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
	cout << "Enter number of the rows to sort: ";
	int numberOfRows;
	cin >> numberOfRows;
	if (numberOfRows > rows)
	{
		throw invalid_argument("Number of the rows to sort can not be more than number of rows.");
	}
	int* rowsToSort = new int[numberOfRows];
	cout << "Enter indexes of the rows to sort(starting with 1)" << endl;
	for (int i = 0; i < numberOfRows; i++)
	{
		cout << "Inputting the " << i + 1 << " index: ";
		int currentIndex;
		cin >> currentIndex;
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

void sortMatrix(double** matrix, int rows, int* dimensions, int* rowsToSort)
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

int inputNumberOfOnes()
{
	int a;
	while (true)
	{
		cout << "Please enter the number of 1 in the number to be copied, a = ";
		cin >> a;
		if (a >= 0)
		{
			return a;
		}
		throw std::invalid_argument("Number of 1 can not be less or equal 0.");
	}
}

int inputNumberOfZeroes()
{
	int b;
	while (true)
	{
		cout << "Please enter the number of 0 in the number to be copied, b = ";
		cin >> b;
		if (b >= 0)
		{
			return b;
		}
		throw std::invalid_argument("Number of 0 can not be less or equal 0.");
	}
}

bool ifNumberFits(double n, int a, int b)
{
	return (numberOnes(n) == a && numberZeroes(n) == b);
}
