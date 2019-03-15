#include <iostream>
#include "ArrayLibrary.h"

using namespace std;

double* ArrayExtention::allocateMemory(int n)
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

void ArrayExtention::inputArray(double* array, int n)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	for (double * p = array, i = 1; p < array + n; p++, i++)
	{
		cout << "a [" << i << "] = ";
		cin >> *p;
	}
}

void ArrayExtention::displayArray(double* array, int n)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	for (double * p = array; p < array + n; p++)
	{
		cout << *p << " ";
	}
	cout << endl;
}

void ArrayExtention::randomArray(double* array, int n)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	for (double * p = array; p < array + n; p++)
	{
		*p = rand() % 20;
	}
}

double* ArrayExtention::deleteElements(double* array, int& n,int ones, int zeroes, conditionToIncludeOrDelete condition)
{
	if (array == nullptr)
	{
		throw std::invalid_argument("Array can not be null.");
	}

	if (n <= 0)
	{
		throw std::invalid_argument("Count of array elements can not be less or equal 0.");
	}

	if (ones <=0 || zeroes <=0)
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

	double* new_array = allocateMemory(length);


	for (int i = 0, j = 0; i < copy; i++)
	{
		if (!(condition(array[i], ones, zeroes)))
		{
			new_array[j] = array[i];
			j++;
		}
		else n--;
	}
	return new_array;
}

double* ArrayExtention::createArray(double* array, int n, int &length, int ones, int zeroes, conditionToIncludeOrDelete condition)
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

	length = 0;
	for (int i = 0; i < n; i++)
	{
		if (condition(array[i], ones, zeroes))
		{
			length++;
		}
	}
	double* new_array = allocateMemory(length);

	for (int i = 0, j = 0; i < n; i++)
	{
		if (condition(array[i], ones, zeroes))
		{
			new_array[j] = array[i];
			j++;
		}
	}

	return new_array;
}
