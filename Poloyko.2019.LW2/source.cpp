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

	double** matrixA = createSquareMatrix(n);

	matrixA = fillSquareMatrix(matrixA, n, inbuilt);

	displaySquareMatrix(matrixA, n);

	cout << endl;

	double** matrixB = createSquareMatrix(n);

	matrixB = fillSquareMatrix(matrixB, n, taylor);

	displaySquareMatrix(matrixB, n);

	cout << endl;

	double comparison = matrixComparison(matrixA, matrixB, n, matrixNorm);

	cout << comparison << endl;

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
		cout << "Invalid data! Try again, n =  ";
	}
}

double inbuilt(int i, int j)
{
	return (i == j) ? i+1 : (sin(2 * (i+1)*(j+1)) + sin(i+1)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);
}

double taylor(int i, int j)
{
	return (i == j) ? i+1 : (customSin(2 * (i + 1)*(j + 1), accuracy) + customSin((i + 1), accuracy)) / (((i + 1) - (j + 1) - 4) ^ 3 + ((i + 1) + (j + 1)) ^ 2);

}

double customSin(double from, double accuracy)
{
	from = (double)fmod(from, 3.14*2);
	double sin = 0.0, term = from;
	int i = 1;
	while (fabs(term)>accuracy)
	{
		sin += term;
		term *= -1.0*(from*from) / (2 * i) / (2 * i + 1);
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
		cout << "Invalid data! Try again, accuracy =  ";
	}
}
