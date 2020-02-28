#include <stdio.h>
#include <stdlib.h>
typedef struct _loc
{
	int x;
	int y;
}Loc;
void MergeTwoArea(Loc arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	Loc* sortArr = (Loc*)malloc(sizeof(Loc) * (right + 1));
	int sIdx = left;

	while (fIdx <= mid && rIdx <= right)
	{
		if (arr[fIdx].y < arr[rIdx].y)
			sortArr[sIdx] = arr[fIdx++];
		else if (arr[fIdx].y == arr[rIdx].y && arr[fIdx].x < arr[rIdx].x)
			sortArr[sIdx] = arr[fIdx++];
		else if (arr[fIdx].y == arr[rIdx].y && arr[fIdx].x > arr[rIdx].x)
			sortArr[sIdx] = arr[rIdx++];

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
void MergeSort(Loc* arr, int left, int right)
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

	int i, iter, n;
	scanf("%d", &iter);
	Loc* locations = (Loc*)malloc(sizeof(Loc) * iter);
	for (i = 0; i < iter; i++)
	{
		scanf("%d %d", &locations[i].x, &locations[i].y);
	}
	MergeSort(locations, 0, iter - 1);
	for (i = 0; i < iter; i++)
	{
		printf("%d %d\n", locations[i].x, locations[i].y);
	}
	return 0;

}