#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int n, m, a, i,j;
	int count = 0;
	int arr[50];
	int arr2[50]; 
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; i++)
		arr[i] = i;
	for (i = 0; i < m; i++)
	{
		scanf("%d", &arr2[i]);

	}
	if (arr2[0] - 1 <= n)
		count += arr2[0] - 1;

	for (i = 0; i < m; i++)
	{
		
	}
	
	
}

