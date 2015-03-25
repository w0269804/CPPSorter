#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <conio.h>
#include <time.h>  
#include <stdlib.h> 
#include <string>
#include <fstream>
using std::string;


#define DEBUG

/*
	Constants used throughout the program.
*/
typedef unsigned long num;
const int MAX_NUMBER = 1000;
const int arraySize = 10000;
const string SOURCE_FILE = "Source.txt";
const string FILE_ONE = "FileOne.txt";
const string FILE_TWO = "FileTwo.txt";
const string FILE_THREE = "FileThree.txt";
const string FILE_FOUR = "FileFour.txt";
const string FINAL_OUT_FILE = "Sorted.txt";
const char LINE_DELIMITER = '|';
const int BUFFER_SIZE = 5;

struct Line
{
	num data;
	int lineNumber;
};

/*
	Used to implement various sort routines
	such as bubble, selection, insertion, shell
	and merge. The various methods take in the 
	array by reference so a copy of the array 
	to be sorted should be passed in if you
	want to re-use the same arrays.
*/
class Sorter
{

private:

	void mergeSort(num * array, int low, int high); // merge sort routine
	void merge(num * array, const int low, const int mid, const int high); // merge array parts
	void quickSort(num *array, int beg, int end, int size); // quick sort the array
	int partition(num * array, int beg, int end, int size); // return the pivot for quick sort

public:

	// helpers
	void createArray(num * array, int size); // randomizes the array
	void printArray(num * array, int size); // prints the array to the console
	void writeArray(num * array, int size, string fileName); // write array to file
	void writeLine(std::ofstream & outStream, Line line); // write a line to a file
	void copyArray(num * src, num * dest, int size); // copies the array
	bool linesRemain(std::ifstream & ifStream); // checks if there is a next line
	Line getNextLine(std::ifstream & ifStream); // gets next line from file

	// internal sorts
	void bubbleSort(num * array, int size);
	void selectionSort(num * array, int size);
	void insertionSort(num * array, int length);

	void quickSort(num * array, int length);
	void mergeSort(Line * array, int length);
	void mergeSort(num * array, int length);
	void insertionSort(Line * array, int length);
	void shellSort(num *, int length);
	bool linesRemain(string fileName);

	// external sorts
	void createInitialList(string sourceFile, num * array, int size); // creates initial list
	void externelMergeSort(num * array, int length); // the initial call to external merge sort	
	void splitInitialList(string sourceFile, string outFileOne, string outFileTwo); // splits initial list
	void finishExternalMergeSort(string sourceFileOne, string sourceFileTwo, string outFile, int buffer); // last combination of files
	void combineFiles(string sourceFileOne, string sourceFileTwo, string outFileOne, string outFileTwo, int buffer); // each round of combining files

};

#endif