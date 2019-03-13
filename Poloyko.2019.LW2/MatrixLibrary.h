#pragma once

namespace MatrixExtension
{
	typedef double(*MatrixType)(int, int);
	typedef double(*Attribute)(double**, int);

	double** createSquareMatrix(int);

	void displaySquareMatrix(double**, int);

	double** fillSquareMatrix(double**, int, MatrixType);

	double matrixNorm(double** , int);

	double matrixComparison(double**, double**, int, Attribute);
}