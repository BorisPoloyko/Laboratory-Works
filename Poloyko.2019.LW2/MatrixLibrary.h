#pragma once

namespace MatrixExtension
{
	typedef double(*MatrixType)(int, int);

	double** createMatrix(int, int);

	void displayMatrix(double**, int, int);

	double** fillMatrix(double**, int,int, MatrixType);

	double matrixComparisonByDifference(double** , double** , int, int);
}
