#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge (int *pData, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Allocate space for holding array
	int leftSide[n1];
	int rightSide[n2];
	extraMemoryAllocated = sizeof(leftSide) + sizeof(rightSide);

	for (i = 0; i < n1; i++){ // Loads data from larger array to smaller arrays
		leftSide[i] = pData[l+i];
	}
	for (j = 0; j < n2; j++){
		rightSide[j] = pData[m + 1 + j];
	}

	i = 0; j = 0; k = l; // Resets variables

	while (i < n1 && j < n2) // Sorts into merged array
    {
        if (leftSide[i] <= rightSide[j])
        {
            pData[k] = leftSide[i];
            i++;
        }
        else
        {
        	pData[k] = rightSide[j];
            j++;
        }
        k++;
    }
	while (i < n1)
	{ // Transfers remaining elements
		pData[k] = leftSide[i];
		i++;
		k++;
	}
	while (j < n2)
	{ // Transfers remaining elements
		pData[k] = rightSide[j];
		j++;
		k++;
	}
}

void mergeSort(int *pData, int l, int r)
{
	if (l < r){
		int m = (l+r) / 2; // Calculates middle index;
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
		merge(pData, l, m, r);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, item, j;	// No extra memory is allocated, such as memory for a holding array or holding variable
	for (i = 1; i < n; i++) {
		item = pData[i];
			for(j=i-1; j>=0; j--) {
				if(pData[j] > item) {
					pData[j+1] = pData[j];
				}
				else {
					break;
				}			
			}
			pData[j+1] = item;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if (pData[j] > pData[j+1]) {
				int temp = pData[j];
				extraMemoryAllocated = sizeof(temp); // Bubble Sort only uses about 4 bytes of memory for a temporary holding variable
				pData [j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	 int i, j, i_min,temp;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        i_min = i;
        for (j = i+1; j < n; j++) {
			if (pData[j] < pData[i_min]) {
				i_min = j;
		  	}
        // Swap the found minimum element with the first element
		}
		if (i_min != i){
				temp = pData[i]; // Swap Data 
				extraMemoryAllocated = sizeof(temp); // Selection Sort only uses about 4 bytes of memory for a temporary holding variable
				pData[i] = pData[i_min];
				pData[i_min] = temp;
		   }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile == NULL){
		printf("Input file cannot be opened.");
		exit(-1);
	}

	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		if (ppData == NULL) {
			printf("Memory allocation failed.");
		}
		for (int i = 0; i < dataSz; i++){
			fscanf(inFile, "%d ", &((*ppData)[i]));
		}
	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
	
		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
}