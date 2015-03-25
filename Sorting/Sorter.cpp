#include "Sorter.h"
 /* 
	References
		 Insertion Sort: http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Insertion_sort
		 Insertion Sort: http://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif
		 Merge Sort: http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Merge_sort
		 Quick Sort: Hal O'Connel's lecture slides from Data Structures (Prog 2400, 2015)
		 Bubble Sort: Hal O'Connel's lecture slides from Data Structures (Prog 2400, 2015)
		 Shell Sort: Hal O'Connel's lecture slides from Data Structures (Prog 2400, 2015)
		 External Merge Sort: Original
*/

/*
	TODO
		 1. Remove the linesRemain function and replace it with a seek or EOF in the main external merge.
		 2. Implement some exception handling: especially where I'm playing loose with files and array indexing.
		 3. Rename some counter variables and temp variables to be more descriptive. No one likes reading "j".
		 4. Break out the print functionality into a separate class.
		 5. Comment the steps involved with external merge sort.
*/

// createArray()
// ============================================
// Fill the array with random numbers 
// ranging from 0 to the maximum defined
// as a constant within the sorter.
// ============================================
void Sorter::createArray(num * array, int size)
{
	for (int i = 0; i < size; i++)
		array[i] = rand() % MAX_NUMBER;
}

// copyArray()
// ============================================
// Make a copy of the array so that we can maintain
// the randomized array for sorting.
// ============================================
void Sorter::copyArray(num * src, num * dest, int size)
{
	memcpy(dest, src, size *sizeof(num));
}

// bubbleSort()
// ============================================
// Check each position to see if the element
// after the current position is greater than
// the element being checked. If it is greater
// then the current element then swap them.
// ============================================
void Sorter::bubbleSort(num * array, int size)
{
	int i, j, tmp;

	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}

// selectionSort()
// ============================================
// Check each position to see if the element
// after the current position is greater than
// the element being checked. If it is greater
// than the current element then swap them. The
// tail of the list will hold the next highest
// element until the list is sorted.
// ============================================
void Sorter::selectionSort(num * array, int size)
{
	int max, i, temp;

	while (size > 0)
	{
		max = 0; // holds maximum value
		for (i = 1; i < size; i++) // check all but last
		if (array[i] > array[max]) // find the max
			max = i; // get index of highest value

		temp = array[size - 1]; // take the element displaced
		array[size - 1] = array[max]; // move the highest to last
		array[max] = temp; // the old number is moved
		size--; // move the index one back 
	}
}


void Sorter::shellSort(num a[], int length)
{
	int i, j, increment;
	num temp;

	for (increment = length / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < length; i++)
		{
			temp = a[i];
			for (j = i; j >= increment; j -= increment)
			{
				if (temp < a[j - increment])
				{
					a[j] = a[j - increment];
				}
				else
				{
					break;
				}
			}
			a[j] = temp;
		}
	}
}


// insertionSort()
// ============================================
// Iterate through the array from the element 
// proceeding the first to the end of the list.
// For each element check each element before it
// and find its position within the sorted list.
// The sorted portion of the list will continue
// to grow as the elements at the front of the 
// list are pushed into their proper place in 
// the list.
// ============================================
void Sorter::insertionSort(num * array, int length)
{

	int j, value;

	// start at index one within the list
	for (int i = 1; i < length; i++)
	{
		// 1. Start from the position after the first element.
		// and iterate through each element.
		value = array[i]; 

		// 2. Compare each proceeding element and see if it is
		//    larger than the element that we are current looking
		//    at. If it is larger then we move it ahead by one position
		//    and after we have finished moving larger items ahead by 
		//    one position we insert the element being looked at (i)
		//    into its proper position within the list of elements from
		//    i to 0.

		for (j = i - 1; j >= 0 && array[j] > value; j--)
		{
			array[j + 1] = array[j];
		}

		//  3. (The key to this final decrement is the fact that j
		//     is declared outside the loop so it gets reduced by one.
		//     After all the shifts the value gets placed in its correct
		//     spot (one less than the last element examined).
		

		array[j + 1] = value;
	}
};


// Implementation of insertion sort using lines
// Sort algorithm defined above.
void Sorter::insertionSort(Line * array, int length)
{
	int j;
    Line value;

	for (int i = 1; i < length; i++)
	{
		value = array[i]; // capture the current value;

		for (j = i - 1; j >= 0 && array[j].data > value.data; j--)
		{
			array[j + 1] = array[j];
		}

		array[j + 1] = value;
	}
};


// quickSort()
// ============================================
// Initial call to the recursive quick sort 
// algorithm. 
// ============================================
void Sorter::quickSort(num * array, int length)
{
	quickSort(array, 0, length - 1, length);
}

// quickSort()
// ============================================
// Quicksort functions by moving all elements
// to the left of a pivot recursively; each 
// pass terminates when the pivot and the end
// position terminate such that each portion 
// is sorted. The first call continues to the 
// right hand side after the lefthand side has
// finished being sorted.
// ============================================
void Sorter::quickSort(num *array, int beg, int end, int size)
{
	if (beg < end)
	{
		int pivot = this->partition(array, beg, end, size); // move values less than array[beg] to left
															// returns the new position of the pivot after
															// shifting all of the elements to the left.

		quickSort(array, beg, pivot - 1, size);         // sorts the the values left of the pivot using the
														// the same mechanism by continuously moving all values
														// to the left of the pivot. 

		quickSort(array, pivot + 1, end, size);	    // sorts the elements to the right by moving them to the left
													// of the position from the pivot generated from the original
													// sort. 
	}
}

// partition()
// ============================================
// Will move all elements larger than beg to the 
// left of beginning and return the new position
// of the original element after the shift.
// ============================================
int Sorter::partition(num *array, int beg, int end, int size)
{
	int p = beg, pivot = array[beg], location;


	for (location = beg + 1; location <= end; location++)
	{
		if (pivot > array[location])
		{
			array[p] = array[location];
			array[location] = array[p + 1];
			array[p + 1] = pivot;
			p++;
		}

	}

	return p;
}

void Sorter::mergeSort(num * array, int size)
{
	mergeSort(array, 0, size - 1);
}

// mergeSort()
// ========================================================================================
// http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Merge_sort
// This merge sort works by recursively dividing the list into smaller parts
// through calls to the merge sort method. As each call completes the portion
// of sorted pieces grows. When it reaches the bottom of the recursing it will 
// be merging two pieces. After the left hand side has been sorted the last recursive
// call to mergeSort() will hit the right hand merge sort and complete the process
// again. As the recursive calls complete the number of sorted pieces will grow until
// eventually the last call will be the merging of the original call to merge sort
// which will merge from 0 to mid to mid + 1 to high.
// ========================================================================================
void Sorter::mergeSort(num * array, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2; // find the middle position (where to divide the array)
		mergeSort(array, low, mid); // divide the array in half
		mergeSort(array, mid + 1, high); // sort from middle + 1 to end
		merge(array, low, mid, high); // merge the two sorted halves.
	}
}

// merge()
// ========================================================================================
// http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Merge_sort
// This method is akin to the external merge sort algorithm, albeit a little
// terser. It will simply take the two chunks, from the lowest to mid and from
// mid + 1 to high and dump them into a new array. If there are no more numbers to
// take from one side then we can simply take the remainder from the other side.
// ========================================================================================
void Sorter::merge(num * arrayToSort, const int low, const int mid, const int high)
{

	num * sortedWhole = new num[high + 1 - low]; // create a new array to hold the sorted parts

	int lowPortionCount, totalElementsAdded, highPortionCount, k;

	lowPortionCount = low; // counter for low portion
	highPortionCount = mid + 1; // counter for high portion
	totalElementsAdded = 0;

	while ((lowPortionCount <= mid) && (highPortionCount <= high))
	{
		if (arrayToSort[lowPortionCount] <= arrayToSort[highPortionCount])
		{
			sortedWhole[totalElementsAdded] = arrayToSort[lowPortionCount];
			lowPortionCount++;
		}
		else
		{
			sortedWhole[totalElementsAdded] = arrayToSort[highPortionCount];
			highPortionCount++;
		}
		totalElementsAdded++;
	}

	if (lowPortionCount > mid)
	{
		for (k = highPortionCount; k <= high; k++)
		{
			sortedWhole[totalElementsAdded] = arrayToSort[k];
			totalElementsAdded++;
		}
	}
	else
	{
		for (k = lowPortionCount; k <= mid; k++)
		{
			sortedWhole[totalElementsAdded] = arrayToSort[k];
			totalElementsAdded++;
		}
	}

	// copy over into the original array
	// which was passed by reference
	for (k = 0; k <= high - low; k++)
	{
		arrayToSort[k + low] = sortedWhole[k];
	}

	delete[] sortedWhole;

}


// printArray
void Sorter::printArray(num * arrayToPrint, int size)
{


	for (int i = 0; i < size; i++)
	{
		std::cout << arrayToPrint[i] << " ";
	}

	std::cout << std::endl;
}

// linesRemain(IFSTREAM)
// ============================================
// Attempts to capture a nextline from the file.
// Returns true if successful or false if not.
// Resets the stream position after the check.
// ============================================
bool Sorter::linesRemain(std::ifstream & ifStream)
{
	string buffer = "";
	bool linesRemain = false;

	std::streampos posOne = ifStream.tellg(); /* tracks the current buffer position */

	if (std::getline(ifStream, buffer))
	{
		linesRemain = true;
		ifStream.seekg(posOne);
	}

	return linesRemain;
}


// linesRemain(STRING)
// ============================================
// Attempts to capture a nextline in a file given
// by name. Returns true if successful or false if not.
// Resets the stream position after the check.
// ============================================
bool Sorter::linesRemain(string fileName)
{
	string buffer = "";
	std::ifstream fileStream(fileName);

	bool linesRemain = false;

	if (std::getline(fileStream, buffer))
		linesRemain = true;

	fileStream.close();

	return linesRemain;
}

// externalMergeSort()
// ============================================
// Creates a text file with lineNumber,value combinations
// and then attempts to sort the list by alternatively 
// creating sorted chunks in two files from source files.
// ============================================
void Sorter::externelMergeSort(num * array, int length)
{

	// Files used in exMerge routine.
	std::string sourceTextOne = FILE_ONE;
	std::string sourceTextTwo = FILE_TWO;
	std::string destFileOne = FILE_THREE;
	std::string destFileTwo = FILE_FOUR;
	
	// The first split of the list is unique in 
	// that it calls out to a sorting routine and 
	// sorts chunk sizes the size of the buffer.
	splitInitialList(SOURCE_FILE, FILE_ONE, FILE_TWO);

	//  This is the sorted chunk size that will
	//  be used in each file on each run. After
	//  each run it will double in size.
	int sizeOfNewRecordSet = BUFFER_SIZE;
	

	do{	
			combineFiles(sourceTextOne, sourceTextTwo, destFileOne, destFileTwo, sizeOfNewRecordSet);

			// rotate sources
			string tempFile = destFileOne;
			destFileOne = destFileTwo;
			destFileTwo = tempFile;

			// swap source and destination
			tempFile = destFileOne;
			destFileOne = sourceTextOne;
			sourceTextOne = tempFile;

			// swap source and destination
			tempFile = destFileTwo;
			destFileTwo = sourceTextTwo;
			sourceTextTwo = tempFile;
				

			sizeOfNewRecordSet *= 2;

	} while (linesRemain(destFileOne) && linesRemain(destFileTwo));


	if (linesRemain(destFileOne))
	{
		remove(FINAL_OUT_FILE.c_str());
		rename(destFileOne.c_str(), FINAL_OUT_FILE.c_str());
	} 
	else
	{
		remove(FINAL_OUT_FILE.c_str());
		rename(destFileTwo.c_str(), FINAL_OUT_FILE.c_str());

	}


}

// combineFiles()
// ============================================
// Will compare the chunks in both files to one another
// and produce a new sorted chunk in alternating destination
// files. The chunks from both files are compared with one
// another and values are pulled from each chunk until both
// chunks are complete.
// ============================================
void Sorter::combineFiles(string sourceFileOne, string sourceFileTwo, string outFileOne, string outFileTwo, int buffer)
{

	std::ifstream fileOneInStream(sourceFileOne);
	std::ifstream fileTwoInStream(sourceFileTwo);
	std::ofstream fileOneOfStream(outFileOne);
	std::ofstream fileTwoOfStream(outFileTwo);
	std::ofstream * curOutStream = &fileTwoOfStream;

	Line fileOneLine;
	Line fileTwoLine;

	std::streampos fileOneStrPos;
	std::streampos fileTwoStrPos;

	int fileOneChunkProgress = 0;
	int fileTwoChunkProgress = 0;

	int linesWritten = 0;

	while (linesRemain(fileOneInStream) || linesRemain(fileTwoInStream))
	{
		// reset the chunk progress from both files
		if (fileOneChunkProgress == buffer && fileTwoChunkProgress == buffer)
		{
			fileOneChunkProgress = 0;
			fileTwoChunkProgress = 0;
		}

		// swap the file being written to
		if (linesWritten == buffer * 2)
		{
			curOutStream = curOutStream == &fileOneOfStream ? &fileTwoOfStream : &fileOneOfStream;
			linesWritten = 0;
		}

		// get next line from file one if lines remain and we haven't taken
		// the full buffer from file one yet. otherwise take the next line
		// from file two and continue the loop.
		if (linesRemain(fileOneInStream) && fileOneChunkProgress != buffer)
		{
			fileOneStrPos = fileOneInStream.tellg();
			fileOneLine = getNextLine(fileOneInStream);
		}
		else
		{
			fileTwoLine = getNextLine(fileTwoInStream);
			writeLine(*curOutStream, fileTwoLine);
			linesWritten++;
			fileTwoChunkProgress++;
			continue;
		}

		// get the next line from file two if lines remain to be taken
		// and we haven't taken a full chunk from file two yet. otherwise
		// write the line from file one taken above
		if (linesRemain(fileTwoInStream) && fileTwoChunkProgress != buffer)
		{
			fileTwoStrPos = fileTwoInStream.tellg();
			fileTwoLine = getNextLine(fileTwoInStream);
		}
		else
		{
			writeLine(*curOutStream, fileOneLine);
			fileOneChunkProgress++;
			linesWritten++;
			continue;
		}

		// if lines are available from both files then we 
		// can simply take the lowest of the two and then 
		// reset the buffer on the file we did not take from
		if (fileOneLine.data <= fileTwoLine.data)
		{
			writeLine(*curOutStream, fileOneLine);
			fileTwoInStream.seekg(fileTwoStrPos);
			fileOneChunkProgress++;
			linesWritten++;
		}
		else
		{
			writeLine(*curOutStream, fileTwoLine);
			fileOneInStream.seekg(fileOneStrPos);
			fileTwoChunkProgress++;
			linesWritten++;
		}

	}

	fileOneInStream.close();
	fileTwoInStream.close();
	fileOneOfStream.close();
	fileTwoOfStream.close();


}

// createInitialList()
// ============================================
// This method is used to simulate the creation of the 
// text file which would be used in the external merge
// sort. It essential takes an unsorted array and writes
// it out to a text file.
// ============================================
void Sorter::createInitialList(string sourceFile, num * array, int size)
{
	std::ofstream sourceOutStream(sourceFile);
	Line curLine;

	for (int i = 0; i < size; i++)
	{
		curLine.lineNumber = i;
		curLine.data = array[i];
		writeLine(sourceOutStream, curLine);
	}

	sourceOutStream.close();
}

// splitInitialList()
// ============================================
// Takes the source list and splits it out into
// files of sorted chunks. 
// ============================================
void Sorter::splitInitialList(string sourceFile, string outFileOne, string outFileTwo)
{
	// the file streams we'll be working with
	// to split the initial source stream into
	// two sorted chunk files
	std::ofstream fileOneStream(outFileOne);
	std::ofstream fileTwoStream(outFileTwo);
	std::ifstream sourceFileStream(sourceFile);
	std::ofstream * curStream = &fileTwoStream;

	// the buffer which will hold our lines
	// as per external merge sort we can only
	// hold the buffer size
	Line line[BUFFER_SIZE];

	// used to toggle between lines
	bool fileOne = true; 
	
	// used to keep track of how many lines
	// we've added to the current file
	int linesAdded = 0;

	// keep sorting while there are lines 
	// which remain in the source file to 
	// sort
	while (linesRemain(sourceFileStream))
	{
		// handles when our buffer is full. when 
		// the buffer is full then we can sort 
		// the current chunk and dump it into a
		// text file.
		if (linesAdded == BUFFER_SIZE)
		{
			// swap the stream
			curStream = curStream == &fileOneStream ? &fileTwoStream : &fileOneStream;
			
			// sort the chunk
			insertionSort(line, BUFFER_SIZE);

			// write the chunk out to the appropriate file
			for (int i = 0; i < BUFFER_SIZE; i++)
			{
				writeLine(*curStream, line[i]);
			}

			// reset the buffer counter 
			linesAdded = 0;
			
			continue;
		}

		line[linesAdded] = getNextLine(sourceFileStream);
		linesAdded++;
	}
		curStream = curStream == &fileOneStream ? &fileTwoStream : &fileOneStream;
	
	// Take the remainder of the file, sort it and store it 
	// in the appropriate text file.
	if (linesAdded != 0)
	{
		insertionSort(line, linesAdded);

		for (int i = 0; i < linesAdded; i++)
		{
			writeLine(*curStream, line[i]);
		}

	}

	fileOneStream.close();
	fileTwoStream.close();
	sourceFileStream.close();

	}


// writeArray()
// ============================================
// Takes in the array and writes it out to the file
// using the write line method.
// ============================================
void Sorter::writeArray(num * array, int size, string name)
{
	std::ofstream outFileStream(name);

	for (int i = 0; i < size; i++)
	{
		Line curLine;
		curLine.lineNumber = i;
		curLine.data = array[i];
		writeLine(outFileStream, curLine);
	}

	outFileStream.close();
}

	
// getNextLine()
// ============================================
// Creates a line structure out of the line 
// taken from the input file stream. At the moment
// there is no exception handling in place. In the 
// future this should implement some sort of conversion
// error exception. Additionally, a tokenizing routine
// might be useful in the future.
// ============================================
Line Sorter::getNextLine(std::ifstream & ifStream)
{
	// get the next line from the text file	
	string lineBuffer;
	std::getline(ifStream, lineBuffer);
	
	Line line;
	
	// parse out the two values.
	line.lineNumber = std::atoi(lineBuffer.substr(0, lineBuffer.find(LINE_DELIMITER)).c_str());
	line.data = std::atoi(lineBuffer.substr(lineBuffer.find(LINE_DELIMITER) + 1).c_str());
	return line;
}


void Sorter::writeLine(std::ofstream & outStream, Line line)
{
	outStream << line.lineNumber << LINE_DELIMITER << line.data << std::endl;
}

