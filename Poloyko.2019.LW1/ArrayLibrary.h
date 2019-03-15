#pragma once

namespace ArrayExtention
{
	typedef bool(*conditionToIncludeOrDelete)(double, int, int);


	double* allocateMemory(int);

	void inputArray(double*, int);

	void displayArray(double*, int);

	void randomArray(double*, int);

	double* deleteElements(double*, int&, int, int, conditionToIncludeOrDelete);

	double* createArray(double*, int, int&, int,int, conditionToIncludeOrDelete);

}