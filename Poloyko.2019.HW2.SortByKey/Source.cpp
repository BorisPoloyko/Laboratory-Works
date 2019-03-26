#include <iostream>
#include "StringLibrary.h"

using namespace std;
using namespace StringExtention;

typedef int(*Key)(char*);
void quickSort(char**, int, int, Key);

int byAlphabetFirtsLetter(char*);

int main()
{
	char string[] = "why?. are .!/ we still:' here";
	int n = strlen(string);
	cout << n;
	char** words = obtainWords(string, n);
	displayWords(words, n);
	quickSort(words, 0, n-1, byAlphabetFirtsLetter);
	displayWords(words, n);

	system("pause");
	return 0;
}

void quickSort(char** words, int left, int right, Key key)
{
	if (words == nullptr)
	{
		throw std::invalid_argument("Matrix can not be null.");
	}
	int i = left, j = right;
	char* pivot = words[(left + right) / 2]; 
	while (i <= j)
	{
		while (key(words[i]) < key(pivot))
		{
			i++;
		}
		while (key(words[j]) > key(pivot))
		{
			j--;
		}
		if (i <= j)
		{
			std::swap(words[i], words[j]);
			i++;
			j--;
		}
	}
	if (left < j)
	{
		quickSort(words, left, j, key);
	}
	if (right > i)
	{
		quickSort(words, j, right, key);
	}
}


int byAlphabetFirtsLetter(char* string)
{
	if (string == nullptr)
	{
		throw std::invalid_argument("String can not be null.");
	}
	return (int)string[0];
}
