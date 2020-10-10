#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


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
		if (arr[fidx] >= arr[ridx])
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
void SearchHeap(int num[], int comb[], int n, int numofdata,int floor,int select_idx[],int version);
void GetComb(int num[], int comb[], int n, int floor, int numofdata, int version)
{
	int a, b, c, d;
	int leftn = n - num[0];
	int idx = 0;
	memset(comb, 0, 5);
	//printf("FLOOR GETCOMB: %d\n", floor);
	comb[0] = num[0];
	
	switch (floor)
	{
	case 2:
		for (a = 1; a < numofdata; a++)
		{
			if (num[a] == leftn && num[a] != num[0])
			{
				comb[0] = num[0];
				comb[1] = num[a];
				int select_idx[5] = { 0,a,-1,-1,-1 };
				SearchHeap(num, comb, n, numofdata, floor, select_idx,version);
			}
			
			memset(comb, 0, 5);
		}
				
				
			
		break;
	case 3:
		for (a = 1; a < numofdata-1; a++)
			for (b = a+1; b < numofdata; b++)
			{
				if (num[a] + num[b]  == leftn && num[0] != num[a] && num[a] != num[b])
				{
					comb[0] = num[0];
					comb[1] = num[a];
					comb[2] = num[b];
					int select_idx[5] = { 0,a,b,-1,-1 };
					SearchHeap(num, comb, n, numofdata, floor, select_idx,version);
				}
				
				memset(comb, 0, 5);

			}
				
		break;
	case 4:
		for (a = 1; a < numofdata - 2; a++)
			for (b = a + 1; b < numofdata - 1; b++)
				for (c = b + 1; c < numofdata; c++)
				{
					if (num[a] + num[b] + num[c]  == leftn && num[0] != num[a] && num[a] != num[b] && num[b] != num[c])
					{
						comb[0] = num[0];
						comb[1] = num[a];
						comb[2] = num[b];
						comb[3] = num[c];
						int select_idx[5] = { 0,a,b,c,-1 };
						SearchHeap(num, comb, n, numofdata, floor, select_idx,version);
					}
					
					memset(comb, 0, 5);

				}
					
		break;
	case 5:
		for (a = 0; a < numofdata - 4; a++)
			for (b = a + 1; b < numofdata - 3; b++)
				for (c = b + 1; c < numofdata - 2; c++)
					for (d = c + 1; d < numofdata-1; d++)
					{
						if (num[a] + num[b] + num[c] + num[d]  == leftn && num[0] != num[a] && num[b] != num[a] && num[c] != num[b] && num[d] != num[c])
						{
							comb[0] = num[0];
							comb[1] = num[a];
							comb[2] = num[b];
							comb[3] = num[c];
							comb[4] = num[d];
							int select_idx[5] = { 0,a,b,c,d };
							SearchHeap(num, comb, n, numofdata, floor,select_idx,version);
						}
						
						memset(comb, 0, 5);

					}
						
		break;
	}
	
		
		
}
void arrayCopy(int a[], int b[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
}
void PrintPreorder(int tree[],int startidx)
{
	if (tree[startidx] == 0)
		return;
	else if (startidx > 30)
		return;
	printf("%d ", tree[startidx]);
	PrintPreorder(tree, 2 * startidx);
	PrintPreorder(tree, 2 * startidx + 1);
}
void SearchHeap(int num[], int comb[], int n, int numofdata, int floor,int select_idx[],int version)
{
	int arr[30] = { 0, };
	arrayCopy(num, arr, numofdata);
	int tree[31] = { 0, };
	int i;
	for (i = 0; i < numofdata; i++)
		if (num[i] == comb[floor - 1])
			break;
	if ((int)pow(2, floor - 1) - 2 >= i)
		i = (int)pow(2, floor - 1) - 1;
	int idx = i + 1;
	int s_idx = 0;
	if (version == 2)
		idx = (int)pow(2, floor) - 1;
	
	for (i = floor; i > 0; i--)
	{
		tree[idx] = comb[i - 1];
		arr[select_idx[s_idx++]] = 0;
		//printf("IDX : %d NUM : %d\n", idx, comb[i - 1]);
		idx = idx / 2;

	}
	
	
	
	int tree_idx = 1;
	int arr_idx = 0;
	int error = 0;
	while (1)
	{
		if (tree[tree_idx] == 0)
		{
			while (arr[arr_idx] == 0)
			{
				arr_idx++;
				if (arr_idx == numofdata)
				{
					error = 1;
					break;
				}
			}
			while (tree[tree_idx / 2] <= arr[arr_idx] || arr[arr_idx]==0)
			{
				
				arr_idx++;
				if (arr_idx == numofdata)
				{
					error = 1;
					break;
				}
			}
			if (error == 1)
				break;
			
				
			tree[tree_idx] = arr[arr_idx];
			//printf("INSERT IDX: %d, VALUE: %d, insertidx :%d\n", tree_idx, arr[arr_idx],arr_idx);
			arr[arr_idx] = 0;
		}
		arr_idx = 0;
		tree_idx++;
		if (tree_idx > numofdata)
			break;
	}
	if (error == 0)
	{
		PrintPreorder(tree, 1);
		exit(0);
	}
		

	
	
}
int main(void)
{
	int num[30];
	int comb[5] = { 0, };
	int n,i;
	int numofdata;
	scanf("%d", &numofdata);
	for (i = 0; i < numofdata; i++)
		scanf("%d",&num[i]);
	scanf("%d", &n);
	
	if (numofdata == 1)
	{
		if (n == num[0])
			printf("%d", num[0]);
		return 0;
	}
	else if (numofdata == 2)
	{
		if (n == num[0] + num[1])
		{
			MergeSort(num,0,numofdata-1);
			printf("%d %d", num[0], num[1]);
		}
		return 0;
	}
	else if (numofdata == 3)
	{
		MergeSort(num,0,numofdata-1);
		if (((num[0] + num[1]) || (num[0] + num[2])) == n)
			printf("%d %d %d", num[0], num[1], num[2]);
		return 0;
	}
	int floor_1 = 0 , floor_2 = 0;
	MergeSort(num,0,numofdata-1);
	for (i = 2; i < 5; i++)
	{
		if (((int)pow(2, i) - 1 < numofdata) && (numofdata <= (int)pow(2, i + 1) - 3))
		{
			floor_1 = i+1;
			floor_2 = i ;
			break;
		}
		else if (((int)pow(2, i + 1) - 3 < numofdata) && (numofdata <= (int)pow(2, i + 1) - 1))
		{
			floor_1 = i + 1;
			break;
		}
			
	}
	//printf("FLOOR: %d\n", floor_1);
	//printf("FLOOR_2 : %d\n", floor_2);
	GetComb(num, comb, n, floor_1, numofdata,1);
	if (floor_2 != 0)
	{
		GetComb(num, comb, n, floor_2, numofdata,2);
	}
		
	return 0;

}