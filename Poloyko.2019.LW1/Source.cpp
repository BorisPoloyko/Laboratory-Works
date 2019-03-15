
#include <iostream>
#include "cmath"
#include "ArrayLibrary.h"


using namespace std;
using namespace ArrayExtention;

typedef bool(*predicate)(double, double);

void mergeSort(double*, int, int, predicate);
void merge(double*, int, int, int, predicate);

bool ifNumberOfOnesGreater(double, double);
bool ifNumberFits(double, int, int);
int inputSize();
int numberOnes(double);
int numberZeroes(double);
void swap(double&, double&);
int inputNumberOfOnes();
int inputNumberOfZeroes();


int n = inputSize();

int main()
{
		          
	int ones = inputNumberOfOnes(), zeroes = inputNumberOfZeroes();

	int lengthOfNewArray;

	double* array = allocateMemory(n);

	inputArray(array, n);

	displayArray(array, n);

	mergeSort(array, 0, n - 1, ifNumberOfOnesGreater);

	cout << "Sorted array: ";

	displayArray(array, n);

	double* new_array = createArray(array, n, lengthOfNewArray, ones, zeroes, ifNumberFits);

	cout << "Copied elements:";

	displayArray(new_array, lengthOfNewArray);

	cout << "Array without elements that were chosen: ";

	array = deleteElements(array, n, ones, zeroes, ifNumberFits);

	displayArray(array, n);

	system("pause");

	return 0;
}

bool ifNumberFits(double n, int a, int b)
{
	return (numberOnes(n) == a && numberZeroes(n) == b);
}

bool ifNumberOfOnesGreater(double a, double b)
{
	return (numberOnes(a) > numberOnes(b));
}

int inputSize()
{
	int n;
	while (true)
	{
		cout << "Please enter the size of the array, n = ";
		cin >> n;
		if (n > 0)
		{
			return n;
		}
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}
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

void swap(double& a, double&b)
{
	double c = a;
	a = b;
	b = c;
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

	double *temp = allocateMemory(right - left + 1);

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
