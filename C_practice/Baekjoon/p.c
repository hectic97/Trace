#include <stdio.h>
#include <stdlib.h>
void MergeTwoArea(int arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	int* sortArr = (int*)malloc(sizeof(int) * (right + 1));
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
void MergeSort(int* arr, int left, int right)
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
	int arr[1000];
	int arr2[1000];
	int i, n, m;
	scanf("%d %d", &n, &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &arr[i], &arr2[i]);
	}
	MergeSort(arr, 0, m - 1);
	MergeSort(arr2, 0, m - 1);
	int result = 0;
	if (arr[0] < arr2[0]*6)
	{
		result += n / 6 * arr[0];

		if (n % 6 * arr2[0] > arr[0])
			result += arr[0];
		else
			result += n % 6 * arr2[0];
		
	}
	else
	{
		result += arr2[0] * n;
	}
		
	printf("%d", result);
	return 0;


}