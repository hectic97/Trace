#include <stdio.h>
#include <stdlib.h>
typedef int Num;
void MergeTwoArea(Num arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	Num* sortArr = (Num*)malloc(sizeof(Num) * (right + 1));
	int sIdx = left;
	
	while (fIdx <= mid && rIdx <= right)
	{
		if (arr[fIdx] <= arr[rIdx])
			sortArr[sIdx] = arr[fIdx++];

		else
			sortArr[sIdx] = arr[rIdx++];
		sIdx++;
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
void MergeSort(Num* arr, int left, int right)
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
int main(void)
{
	int n, k,i;
	scanf("%d %d",&n,&k);
	int* arr = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d",&arr[i]);
	MergeSort(arr, 0, n - 1);
	printf("%d",arr[k - 1]);
	return 0;
}