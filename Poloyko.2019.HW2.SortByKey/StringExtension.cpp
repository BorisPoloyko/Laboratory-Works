#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "StringLibrary.h"

using namespace std;

char** StringExtention::obtainWords(char * source, int & n)
{
	if (source == nullptr)
	{
		throw std::invalid_argument("Source array of words can not be null.");	
	}
	char* copy = new char[strlen(source) + 1];
	strcpy(copy, source);

	char** words = new char*[strlen(copy) / 2];
	n = 0;
	const char* symbols = "	1234567890-=!@#$%^&*()_+{}|][:;'<>?/., \x22";
	char* pword = strtok(copy, symbols);
	words[n] = new char[strlen(pword) + 1];
	strcpy(words[n], pword);

	n++;
	while (pword)
	{
		pword = strtok('\0', symbols);
		if (pword)
		{
			words[n] = new char[strlen(pword) + 1];
			strcpy(words[n], pword);
			n++;
		}
	}

	delete[] copy;
	return words;
}

void StringExtention::displayWords(char** words, int n)
{
	if (words == nullptr)
	{
		throw std::invalid_argument("Array of words can not be null.");	
	}
	if (n <=0)
	{
		throw std::invalid_argument("Number of words can not be less or equal 0.")
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << (i + 1) << ". " << words[i] << std::endl;
	}
}
