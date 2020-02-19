#include <stdio.h>

void Swap(int arr[], int idx1, int idx2)
{
	int temp;
	temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
	return;
}

int Partition(int arr[], int left, int right)
{
	
	
	int pivot = arr[left];
	int low = left + 1;
	int high = right;
	
	printf("pivot:%d\n", pivot);
	
	while (low <= high)
	{
		while (pivot >= arr[low] && low<=right)
			low++;
		while (pivot <= arr[high] && high>=(left+1))
			high--;
		if (low <= high)
			Swap(arr, low, high);
	}
	Swap(arr, left, high);;
	return high;
}

void QuickSort(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
		
	}
}
int mai2n(void)
{
	int arr[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int len = sizeof(arr) / sizeof(int);
	int i;

	QuickSort(arr, 0, sizeof(arr) / sizeof(int) - 1);

	for (i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}