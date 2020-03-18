#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int i,j,p, n, yoojin;
	scanf("%d %d %d", &n, &yoojin, &p);
	int* ranker = (int*)malloc(sizeof(int) * n);
	if (n == 0)
	{
		printf("1");
		return 0;
	}
		
	for (i = 0; i < n; i++)
		scanf("%d", &ranker[i]);
	int larger = 0,same=0;
	
	for (i = 0; i < n; i++)
	{
		if (ranker[i] > yoojin)
			larger++;
		else if (ranker[i] == yoojin)
			same++;
		else if (ranker[i] < yoojin)
			break;

	}
	if (larger + same < p)
		printf("%d", larger + 1);
	else
		printf("-1");
	return 0;
	

}