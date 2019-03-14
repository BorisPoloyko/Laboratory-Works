#include <iostream>
#include <cmath>
#include "MatrixLibrary.h"

using namespace std;
using namespace MatrixExtension;

int inputSize();
double inputAccuracy();
double inbuilt(int, int);
double taylor(int, int);
double customSin(double, double);

double accuracy = inputAccuracy();

int main()
{
	int n = inputSize();

	double** matrixA = createMatrix(n , n);

	matrixA = fillMatrix(matrixA, n, n, inbuilt);

	displayMatrix(matrixA, n , n);

	cout << endl;

	double** matrixB = createMatrix(n,n);

	matrixB = fillMatrix(matrixB, n,n, taylor);

	displayMatrix(matrixB, n,n);

	cout << endl;

	double comparison = matrixComparisonByDifference(matrixA, matrixB, n,n);

	cout << abs(comparison) << endl;

	system("pause");

	return 0;
}

int inputSize()
{
	int n;
	while (true)
	{
		cout << "Please enter the size of the matrix, n = ";
		cin >> n;
		if (n > 0)
		{
			return n;
		}
		throw out_of_range("Size of the matrix can not be less or equal 0.");
	}
}

double inbuilt(int i, int j)
{
	return (i == j) ? i+1 : (sin(2 *(i+1)*(j+1)) + sin(i+1)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);
}

double taylor(int i, int j)
{
	return (i == j) ? i+1 : (customSin(2 * (i + 1)*(j + 1), accuracy) + customSin((i + 1), accuracy)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);
}

double customSin(double number, double accuracy)
{
	if (accuracy < 0 || accuracy >1)
	{
		throw out_of_range("Accuracy can not be less than 0 or more than 1");
	}
	number = fmod(number, 3.14*2);
	double sin = 0, term = number;
	int i = 1;
	while (abs(term)>accuracy)
	{
		sin += term;
		term *= -1.0*(number * number) / (2 * i) / (2 * i + 1);
		i++;
	}
	return sin;
}

double inputAccuracy()
{
	double n;
	while (true)
	{
		cout << "Please enter the accuracy, accuracy = ";
		cin >> n;
		if (n > 0 && n <= 1)
		{
			return n;
		}
		throw out_of_range("Accuracy can not be less than 0 or more than 1");
	}
}
