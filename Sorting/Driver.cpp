#include "Driver.h"

void Driver::runSorts()
{
	srand(time(NULL)); // seed random number generator
	
	num array[arraySize]; // create the array
	sorter.createArray(array, arraySize); // randomize the contents of the array

	std::cout << "\tWriting Unsorted Array to Original." << SOURCE_FILE << std::endl;
	sorter.writeArray(array, arraySize, SOURCE_FILE);

	/// run through all sorts
	runSort(&Sorter::bubbleSort, array, arraySize, "BubbleSort.txt");
	runSort(&Sorter::selectionSort, array, arraySize, "SelectionSort.txt");
	runSort(&Sorter::insertionSort, array, arraySize, "InsertionSort.txt");
	runSort(&Sorter::quickSort, array, arraySize, "QuickSort.txt");
	runSort(&Sorter::mergeSort, array, arraySize, "MergeSort.txt");
	runSort(&Sorter::shellSort, array, arraySize, "ShellSort.txt");
	runSort(&Sorter::externelMergeSort, array, arraySize, FINAL_OUT_FILE);

};


void Driver::runSort(SortFunction function, num * array, int size, string name)
{

	std::cout << "=============== Routine Starting ========= \n" << std::endl;
	std::cout << "\tCopying Original Array" << std::endl;

	/// copy original array to avoid modifying it
	num * copy = new num[size]; 

	if (function != &Sorter::externelMergeSort)
	sorter.copyArray(array, copy, arraySize);

	std::cout << "\tPerforming Sort" << std::endl;

	/// start the timer and execute sort
	start = std::chrono::system_clock::now();
	(sorter.*function)(copy, size);
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	/// write the results of the sort to file
	std::cout << "\tFinished Sort." << std::endl;

	/// display the total time taken
	std::cout << "\tTotal sort time: " << elapsed_seconds.count()
		<< " seconds" << std::endl; // show time

	std::cout << "\tWriting results to: " << name << std::endl;

	if (function != &Sorter::externelMergeSort)
		sorter.writeArray(copy, arraySize, name);


	std::cout << "\n=========================================" << std::endl;
	std::cout << "\n Press Any Key to Continue\n" << std::endl;

	_getch();

	delete[] copy;

}

