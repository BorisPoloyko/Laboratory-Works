#pragma once

namespace NonRectangularMatrixExtention
{
	double** allocateMemory(int, int*);

	void displayArray(double* , int);

	void displayMatrix(double**, int, int*);

	void fillMatrix(double**, int, int*);
}