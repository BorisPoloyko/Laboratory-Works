#pragma once

namespace NonRectangularMatrixExtention
{
	typedef bool(*ConditionToIncludeOrDelete)(double, int, int);


	double** allocateMemory(int, int*);

	void displayArray(double* , int);

	void displayMatrix(double**, int, int*);

	void fillMatrix(double**, int, int*);

	double* allocateMemoryForArray(int);

	double* deleteElementsInArray(double* , int& , int , int , ConditionToIncludeOrDelete);

	double** deleteElementsInMatrix(double** , int , int* , int, int, int*,ConditionToIncludeOrDelete);
}
