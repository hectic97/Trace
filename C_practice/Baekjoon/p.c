#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
	int n, i,j;
	int sx, sy, px, py;
	scanf("%d",&n);
	
	int** arr;
	arr = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}
	
		
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			scanf("%d",&arr[i][j]);
			if (arr[i][j] == 2)
			{
				sx = i, sy = j;
			}
			else if (arr[i][j] == 5)
				px = i, py = j;
		
		}
	
	
	int count = 0;
			
	for (i = sx > px ? px : sx; i <= (sx > px ? sx : px); i++)
		for (j = sy > py ? py : sy; j <= (sy > py ? sy : py); j++)
			if (arr[i][j] == 1)
				count++;
	
	if (count >= 3 && pow(abs(px-sx),2)+pow(abs(py-sy),2)>=25)
		printf("1");
	else
		printf("0");
	return 0;
}