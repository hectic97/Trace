#ifndef __MERGESORT_H__
#define __MERGESORT_H__

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int orgindex;
	int data;
}Num;
void MergeTwoArea(Num arr[], int left, int mid, int right, int bydata)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	Num* sortArr = (Num*)malloc(sizeof(Num) * (right + 1));
	int sIdx = left;
	if (bydata == 0)
	{
		while (fIdx <= mid && rIdx <= right)
		{
			if (arr[fIdx].data <= arr[rIdx].data)
				sortArr[sIdx] = arr[fIdx++];

			else
				sortArr[sIdx] = arr[rIdx++];
			sIdx++;
		}

	}
	else
	{
		while (fIdx <= mid && rIdx <= right)
		{
			if (arr[fIdx].orgindex <= arr[rIdx].orgindex)
				sortArr[sIdx] = arr[fIdx++];

			else
				sortArr[sIdx] = arr[rIdx++];
			sIdx++;
		}
	}
	


	if (fIdx > mid)
	{
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}
	else
	{

		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}
	for (i = left; i <= right; i++)
	{
		arr[i] = sortArr[i];
	}
	free(sortArr);
}
void MergeSort(Num* arr, int left, int right, int bydata)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(arr, left, mid,bydata);
		MergeSort(arr, mid + 1, right,bydata);

		MergeTwoArea(arr, left, mid, right,bydata);
	}
}
#endif