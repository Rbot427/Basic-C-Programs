// Sorting Functions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void mergeSort(float *sort, int size)
{
	float *Half1, *Half2; //Declare our temporary arrays
	int size1, size2, Half1c = 0, Half2c = 0, sortc = 0;
	if(size == 1) //Check to see if you can't spilt anymore, and begin the mergeing process
		return;
	size1 = size/2; size2 = size/2 + size % 2; //Set sizes, the % checks for odds. If it's three, Half1 will take 1 element and H2 will take 2

	Half1 = new float[size1]; Half2 = new float[size2];

	for(int count = 0; count < size1; count++)
		Half1[count] = sort[count];
	for(int count = size1; count < size; count++)
		Half2[count - size1] = sort[count]; //The - size is so you can take the second half of size, but start at element 0 in Half

	mergeSort(Half1, size1);
	mergeSort(Half2, size2);

	for(sortc = 0; sortc < size; sortc++) //Merge the two halfs together
	{
		if(Half1[Half1c] == Half2[Half2c])
		{
			sort[sortc] = Half1[Half1c]; Half1c++; sortc++;
			sort[sortc] = Half2[Half2c]; Half2c++;
		}
		else if(Half1[Half1c] < Half2[Half2c])
		{
			sort[sortc] = Half1[Half1c]; Half1c++;
		}
		else
		{
			sort[sortc] = Half2[Half2c]; Half2c++;
		}
		if(Half1c >= size1 || Half2c >= size2)
			break;
	}
	for(sortc = sortc++; sortc < size; sortc++)
	{
		if(Half1c >= size1 && Half2c < size2) {
			sort[sortc] = Half2[Half2c]; Half2c++; }
		if(Half2c >= size2 && Half1c < size1) {
			sort[sortc] = Half1[Half1c]; Half1c++; }
	}

	delete Half1; //Clear up space!
	delete Half2; 
}

int main()
{
	float *hello;
	int counter = 0;
	std::cout << "Hello there Mr. Wiskers \n"; //Random intro
	std::cout << "Enter in the amount of numbers you want sorted \n";
	std::cin >> counter;

	hello = new float[counter];
	system("cls");

	std::cout << "Now enter in the numbers \n"; //Take input
	for(int count = 0; count < counter; count++) {
	std::cout << "Number: ";
	std::cin >> hello[count];
	system("cls");
	}

	mergeSort(hello, counter);

	for(int count = 0; count < counter; count++) //Display the sorted list
		std::cout << hello[count] << ' ';

	std::cout << "\n";
	system("Pause");

	return 0;
}
