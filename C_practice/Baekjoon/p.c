#include <stdio.h>
int main(void)
{
	int n, m,i,j,k;
	int arr[100];
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	int approximation = 0;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			for (k = j + 1; k < n; k++)
			{
				if ((arr[i] + arr[j] + arr[k] <= m) && (arr[i] + arr[j] + arr[k] >= approximation))
				{
					
					approximation = arr[i] + arr[j] + arr[k];
				}
					
			}
	printf("%d", approximation);
	return 0;
}