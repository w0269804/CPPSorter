#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include "Sorter.h"

using std::chrono::duration;
using std::chrono::time_point;
using std::chrono::system_clock;
typedef unsigned unsigned long int num;

const string BUBBLE_SORT_FILE = "BubbleSort.txt";
const string SELECTION_SORT_FILE = "SelectionSort.txt";
const string QUICKSORT_FILER = "QuickSort.txt";
const string MERGE_SORT_FILER = "MergeSort.txt";



// http://tipsandtricks.runicsoft.com/Cpp/MemberFunctionPointers.html
typedef void(Sorter::*SortFunction)(num *, int);

class Driver
{
private:

	// http://en.cppreference.com/w/cpp/chrono
	std::chrono::time_point<std::chrono::system_clock> start, end;
	Sorter sorter;

public:

	void runSorts();
	void showTime();
	void bubbleSort(num * array, int size);
	void runSort(SortFunction, num *, int);
	void runSort(SortFunction function, num * array, int size, string name);


};

#endif