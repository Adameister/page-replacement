/*
 * Name: Adam Hudson
 * ID #: 1000991758
 * Programming Assignment 3
 * Description: Create a program to impliment
 *				the FIFO, LRU, LFU, and Optimal
 *				page replacement algorithems
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGE_NUMBER 255

// Code for my first in first out algorithem.
// the code will run through the data in the file
// and loop throgh the pages.
// The pageTableSize holds how big to make the page table.
void fifo( int argc, char *argv[] ){
	char buffer[500];		// Grabs each line from the file
	char token;				// stores the individual page char from the file
	FILE *pageFile;			// the file pointer from the commandline
	int page;				// token casted as an int
	int totalFaults = 0;	// tracker for the total page faults
	int pageTableSize;		// first number from the file
	int i = 0;				// counter var
	int boolean;			// checker var to see if data is already in page table
	int fifoTracker = 0;	// keeps track of who came in first

	// opens the first file from the command line in read-only format
	pageFile = fopen( argv[1], "r" );

	// grab the first entry of the file for the page table size
	fgets( buffer, sizeof buffer, pageFile );
	token = buffer[0];
	// the file has the data in a char, so I cast the char as an int and compensate for ASCII values
	pageTableSize = (int)token - '0';

	// Init the page table with the pageTableSize and -1's for the data in the table
	int pageTable[ pageTableSize ];
	while( i < pageTableSize ){
		pageTable[ i ] = -1;
		i++;
	}

	// this will loop through the page file until there is nothing left in the file
	while( fgets( buffer, sizeof buffer, pageFile ) != NULL ){
		token = buffer[0];
		page = (int)token - '0';

		// loop through the page table to see if page is already in the page table
		i = 0;
		boolean = 0;
		while( i < pageTableSize ){
			if( pageTable[i] == page ){
				// the page is in the page table
				// update the boolean
				// if true, the page is alreay in the page table
				boolean = 1;
			}
			i++;
		}

		// if the boolean comes back false, there is a page fault
		// and the page table needs to be updated accordingly
		if( !boolean ){
			totalFaults++;
			pageTable[ fifoTracker ] = page;
			fifoTracker++;
		}

		// if the fifoTracker has reached the end of the pageTable, reset it to zero
		if( fifoTracker >= pageTableSize ){
			fifoTracker = 0;
		}

		// print the status of the page table upon each iteration of page cycle
		i = 0;
		while( i < pageTableSize ){
			if( pageTable[i+1] == -1 ){
				printf("%d ", pageTable[i]);
			}
			else{
				printf("%d  ", pageTable[i] );
			}
			i++;
		}
		printf("\n");

	}

	fclose(pageFile);

	printf("Page fault of FIFO: %d\n\n", totalFaults);

	// goes back to main
	return;
}

// Code for the least recently used algorithem.
// the function will get the list of pages, as well
// as the size of the page table.
// The code will loop through the pages
// and keep track of which page in the page table has
// been used least recently.
void lru( int argc, char *argv[] ){
	char buffer[500];		// Grabs each line from the file
	char token;				// stores the individual page char from the file
	FILE *pageFile;			// the file pointer from the commandline
	int page;				// token casted as an int
	int totalFaults = 0;	// tracker for the total page faults
	int pageTableSize;		// first number from the file
	int i = 0;				// counter var
	int boolean;			// checker var to see if data is already in page table
	int lruTracker;			// var to keep track of who is the least reciently used page
	int temp;				// temporary var used to move data around in an array

	// opens the first file from the command line in read-only format
	pageFile = fopen( argv[1], "r" );

	// grab the first entry of the file for the page table size
	fgets( buffer, sizeof buffer, pageFile );
	token = buffer[0];
	// the file has the data in a char, so I cast the char as an int and compensate for ASCII values
	pageTableSize = (int)token - '0';

	// Init the page table with the pageTableSize and -1's for the data in the table
	int pageTable[ pageTableSize ];
	while( i < pageTableSize ){
		pageTable[ i ] = -1;
		i++;
	}

	// Created and Init an array to keep track of who is the most reciently used
	int mostRecentlyUsed[ pageTableSize ];
	i = 0;
	while( i < pageTableSize ){
		mostRecentlyUsed[ i ] = -1;
		i++;
	}

	// this will loop through the page file until there is nothing left in the file
	while( fgets( buffer, sizeof buffer, pageFile ) != NULL ){
		token = buffer[0];
		page = (int)token - '0';

		// loop through the page table to see if page is already in the page table
		i = 0;
		boolean = 0;
		while( i < pageTableSize ){
			if( pageTable[i] == page ){
				// the page is in the page table
				// update the boolean
				// if true, the page is alreay in the page table
				boolean = 1;
			}
			i++;
		}

		// if the boolean comes back false, there is a page fault
		// and the page table needs to be updated accordingly
		if( boolean ){
			// if the page is n the table, the logic for the least reciently used
			// still needs to be updated

			// update the most recent used
			// find where the page is currently in the table
			i = 0;
			while( i < pageTableSize ){
				if( mostRecentlyUsed[i] == page ){
					break;
				}
				i++;
			}

			// shift the array so that the least reciently used is at the bottom of the array
			while( i != 0 ){
				mostRecentlyUsed[i] = mostRecentlyUsed[ (i-1) ];
				i--;
			}

			// update the mostRecentlyUsed table
			mostRecentlyUsed[0] = page;
		}
		else{
			totalFaults++;
			i = 0;
			while( i < pageTableSize ){
				if( mostRecentlyUsed[ (pageTableSize-1) ] == pageTable[i] ){
					pageTable[ i ] = page;
					break;
				}
				i++;
			}

			// if there is a page fault, the mostRecentlyUsed table needs to be updated
			// update the most recent used
			// find where the page is currently in the table
			i = 0;
			while( i < pageTableSize ){
				if( mostRecentlyUsed[i] == page ){
					break;
				}
				i++;
			}

			while( i != 0 ){
				mostRecentlyUsed[i] = mostRecentlyUsed[ (i-1) ];
				i--;
			}

			// update the mostRecentlyUsed table
			mostRecentlyUsed[0] = page;

		}

		// print the status of the page table upon each iteration of page cycle
		i = 0;
		while( i < pageTableSize ){
			if( pageTable[i+1] == -1 ){
				printf("%d ", pageTable[i]);
			}
			else{
				printf("%d  ", pageTable[i] );
			}
			i++;
		}
		printf("\n");

	}

	fclose(pageFile);

	printf("Page fault of LRU: %d\n\n", totalFaults);

	return;
}

// this is the code that impliments the least frequently used
// page replacement.
// The code will take in the list of pages from the command prompt, as
// well as the size of the page table.
void lfu( int argc, char *argv[] ){
	char buffer[500];		// Grabs each line from the file
	char token;				// stores the individual page char from the file
	FILE *pageFile;			// the file pointer from the commandline
	int page;				// token casted as an int
	int totalFaults = 0;	// tracker for the total page faults
	int pageTableSize;		// first number from the file
	int boolean;			// checker var to see if data is already in page table
	int boolean2;			// checks to see if the array has -1s in it
	int fifoTracker = 0;	// keeps track of who came in first
	int pageCounter[MAX_PAGE_NUMBER];			// page numbers only go up to 255
												// so the index of this array is the page
												// number and the data value is how many
												// times it has been used
	int leastFreqPage = 0;			// temp var to retain which page to replace
	int currentPage;				// var used to see what page we're looking at
	int i = 0;						// counter var
	int temp;						// teamp var to hold data


	// opens the first file from the command line in read-only format
	pageFile = fopen( argv[1], "r" );

	// grab the first entry of the file for the page table size
	fgets( buffer, sizeof buffer, pageFile );
	token = buffer[0];
	// the file has the data in a char, so I cast the char as an int and compensate for ASCII values
	pageTableSize = (int)token - '0';

	// Init the page table with the pageTableSize and -1's for the data in the table
	int pageTable[ pageTableSize ];
	while( i < pageTableSize ){
		pageTable[ i ] = -1;
		i++;
	}

	// Init the page counts with zeros
	i = 0;
	while( i < MAX_PAGE_NUMBER ){
		pageCounter[i] = 0;
		i++;
	}

	// this will loop through the page file until there is nothing left in the file
	while( fgets( buffer, sizeof buffer, pageFile ) != NULL ){
		token = buffer[0];
		page = (int)token - '0';
		boolean2 = 0;

		// everytime a page is used, inc the count
		pageCounter[ page ]++;

		// debug output for the page counts
		/*i = 0;
		printf("pagecounts:\n");
		while( i < 8 ){
			printf("%d  ", pageCounter[i]);
			i++;
		}
		printf("\n\n");*/

		// loop through the page table to see if page is already in the page table
		i = 0;
		boolean = 0;
		while( i < pageTableSize ){
			if( pageTable[i] == page ){
				// the page is in the page table
				// update the boolean
				// if true, the page is alreay in the page table
				boolean = 1;
			}
			i++;
		}

		// if the boolean comes back false, there is a page fault
		// and the page table needs to be updated accordingly
		if( !boolean ){
			totalFaults++;
			//printf("PAGEFAULT!!!\n");

			i = 0;
			while(  i < pageTableSize  ){
				if( pageTable[i] == -1 ){
					pageTable[i] = page;
					boolean2 = 1;
					break;
				}
				i++;
			}
			if( boolean2 ){
				// do nothing
			}
			else{

				i = 0;

				// the code will change the page table array
				// so these two varables will hold the manipulated
				// data
				currentPage = pageTable[0];
				temp = pageCounter[currentPage];

				// loop through the page table and find
				// the page which as been used the least
				while( i < pageTableSize ){
					currentPage = pageTable[i];

					// if the new page we are looking at has been
					// used less than the page we have
					// we swap out the more used page
					// with the less used page
					if( temp > pageCounter[currentPage] ){
						//printf("%d Page is now the lowest\n", currentPage);
						temp = pageCounter[currentPage];

						// keeps hold of the least used page
						leastFreqPage = i;
					}

					i++;
				}

				i = 0;
				// loop though the page table
				while( i < pageTableSize ){
					// if the page count of the current page
					// is equlivant to the page count of the leastFreqPage
					// then check if the current page has a lower page number
					if( pageCounter[ pageTable[i] ] == pageCounter[ pageTable[ leastFreqPage ] ] ){
						if( pageTable[ i ] < pageTable[ leastFreqPage ] ){
							// if it does, update the leastFreqPage
							leastFreqPage = i;
						}
					}
					i++;
				}

				// update the page table in the correct spot
				pageTable[ leastFreqPage ] = page;
			}
		}

		// print the status of the page table upon each iteration of page cycle
		i = 0;
		while( i < pageTableSize ){
			if( pageTable[i+1] == -1 ){
				printf("%d ", pageTable[i]);
			}
			else{
				printf("%d  ", pageTable[i] );
			}
			i++;
		}
		printf("\n");

	}

	fclose(pageFile);

	printf("Page fault of LFU: %d\n\n", totalFaults);

	// goes back to main
	return;
}

// code for the optimal page replacement
// This code will look ahead of the pages needed and
// find the page in the page table that will be used the
// farthest in the future as possible.
void optimal( int argc, char *argv[] ){
	char buffer[500];		// Grabs each line from the file
	char token;				// stores the individual page char from the file
	FILE *pageFile;			// the file pointer from the commandline
	int page;				// token casted as an int
	int totalFaults = 0;	// tracker for the total page faults
	int pageTableSize;		// first number from the file
	int i = 0;				// counter var
	int boolean;			// checker var to see if data is already in page table
	int pageArraySize;		// keeps the total amount of pages in the file
	int j = 0;				// keeps track of what future pages to look at
	int k = 0;				// looper through the pageTable
	int tracer;				// tracer is a score; whichever page in the pageTable gets the
							// highest score, gets pagefaulted out
	int tempTracer;			// tracer changes alot, so tempTracer will keep track of the previous score
	int optimalPage = -1;	// keeps hold of the optimal page placement in the pageTable

	// opens the first file from the command line in read-only format
	pageFile = fopen( argv[1], "r" );

	// grab the first entry of the file for the page table size
	fgets( buffer, sizeof buffer, pageFile );
	token = buffer[0];
	// the file has the data in a char, so I cast the char as an int and compensate for ASCII values
	pageTableSize = (int)token - '0';

	// Init the page table with the pageTableSize and -1's for the data in the table
	int pageTable[ pageTableSize ];
	while( i < pageTableSize ){
		pageTable[ i ] = -1;
		i++;
	}

	// this will loop through the page file until there is nothing left in the file
	i = 0;
	while( fgets( buffer, sizeof buffer, pageFile ) != NULL ){
		// i right now has the total number of pages in the file
		i++;
	}
	// update the number of pages
	pageArraySize = i;

	// bring the file pointer back to the top
	rewind( pageFile );

	// declair an array to hold all page table 
	int pageArray[ pageArraySize ];

	// get rid of the first entry, because we already know it
	fgets( buffer, sizeof buffer, pageFile );

	// this reads the data into the page array
	i = 0;
	while( fgets( buffer, sizeof buffer, pageFile ) != NULL ){
		token = buffer[0];
		page = (int)token - '0';
		pageArray[ i ] = page;
		i++;
	}

	i = 0;	// i is checking the current page
	j = 0;	// j is checking the future pages
	// loop through all the pages
	while( i < pageArraySize ){
		k = 0;
		boolean = 0;
		tracer = 0;
		tempTracer = 0;

		// determines if the page is in the table
		while( k < pageTableSize ){
			if( pageTable[k] == pageArray[i] ){
				// the page is in the page table
				// update the boolean
				// if true, the page is alreay in the page table
				boolean = 1;
			}
			k++;
		}

		// if the boolean comes back false, there is a page fault
		// and the page table needs to be updated accordingly
		if( !boolean ){
			totalFaults++;
			k = 0;
			// need to loop though the pages to find the page to best switch out
			while( k < pageTableSize ){
				// reset the tracer score
				tracer = 0;
				// j now equals where the current page is
				j = i;

				// loop though the future pages to check who has the highest score
				while( j < pageArraySize ){
					tracer++;
					if( pageTable[k] == pageArray[j] ){
						// if the page in the future matches the page in the table
						// jump out of the loop
						break;
					}
					j++;
				}

				// if tracer has found a page with a higher score, update the best page
				if( tracer > tempTracer ){
					tempTracer = tracer;
					optimalPage = k;
				}

				k++;

			}

			// at this point, we have seen all of the future pages for
			// all of the pages in the pageTable.
			// optimalPage holds the position for the best page to falut out
			pageTable[ optimalPage ] = pageArray[i];
			
		}

		// this simply loops though the current status of the page table
		k = 0;
		while( k < pageTableSize ){
			if( pageTable[k+1] == -1 ){
				printf("%d ", pageTable[k]);
			}
			else{
				printf("%d  ", pageTable[k] );
			}
			k++;
		}
		printf("\n");
		i++;
	}
	

	fclose(pageFile);

	printf("Page fault of Optimal: %d\n\n", totalFaults);

	// goes back to main
	return;
}


int main( int argc, char *argv[] ){
	
	// the main function is used to call the functions
	// as well as turn functions on and off for debugging purposes

	fifo( argc, argv);
	lru( argc, argv);
	lfu( argc, argv);
	optimal( argc, argv);

	return 0;
}