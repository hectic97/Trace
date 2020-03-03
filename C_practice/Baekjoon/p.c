#include <stdio.h>
#define ARR_LEN 50
#ifndef __MERGESORT_H__
#define __MERGESORT_H__

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int orgindex;
	int data;
}Num;

void MergeTwoArea(Num arr[], int left, int mid, int right, int ascending)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	Num* sortArr = (Num*)malloc(sizeof(Num) * (right + 1));
	int sIdx = left;
	if (ascending == 1)
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
			if (arr[fIdx].data >= arr[rIdx].data)
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
void MergeSort(Num* arr, int left, int right, int ascending)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(arr, left, mid, ascending);
		MergeSort(arr, mid + 1, right, ascending);

		MergeTwoArea(arr, left, mid, right, ascending);
	}
}
#endif
int main(void)
{
	int iter, i;
	Num A[ARR_LEN];
	Num B[ARR_LEN];
	scanf("%d", &iter);
	for (i = 0; i < iter; i++)
	{
		scanf("%d", &A[i].data);
		A[i].orgindex = i;
	}
	for (i = 0; i < iter; i++)
	{
		scanf("%d", &B[i].data);
		B[i].orgindex = i;
	}
	MergeSort(A, 0, iter - 1, 0);
	MergeSort(B, 0, iter - 1, 1);
	int Final[ARR_LEN];
	int sum = 0;
	for (i = 0; i < iter; i++)
		sum += A[i].data * B[i].data;
	
	printf("%d", sum);
	return 0;


}