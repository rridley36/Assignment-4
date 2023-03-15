void bubbleSort(int* pData, int n)
{
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if (pData[j] > pData[j+1]){
				int temp = pData[j];
				extraMemoryAllocated = sizeof(temp);
				pData [j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}