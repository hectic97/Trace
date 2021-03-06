#include <stdio.h>
#include <stdlib.h>
typedef int Data;
void MergeTwoArea(Data arr[], int left, int mid, int  right)
{
	int fidx = left;
	int ridx = mid + 1;
	int i;

	Data* sortArr = (Data*)malloc(sizeof(Data) * (right + 1));
	int sidx = left;

	while (fidx <= mid && ridx <= right)
	{
		if (arr[fidx] <= arr[ridx])
			sortArr[sidx] = arr[fidx++];
		else
			sortArr[sidx] = arr[ridx++];
		sidx++;
	}

	if (fidx > mid)
	{
		for (i = ridx; i <= right; i++, sidx++)
			sortArr[sidx] = arr[i];
	}
	else
	{
		for (i = fidx; i <= mid; i++, sidx++)
			sortArr[sidx] = arr[i];
	}
	for (i = left; i <= right; i++)
		arr[i] = sortArr[i];
	free(sortArr);

}

void MergeSort(Data arr[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}