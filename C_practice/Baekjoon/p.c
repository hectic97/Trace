#include <stdio.h>
typedef struct
{
	int weight;
	int height;
	int rank;
}Info;

int main(void)
{
	int i, iter,j;
	Info info[50];
	scanf("%d", &iter);
	for (i = 0; i < iter; i++)
	{
		scanf("%d %d", &info[i].weight, &info[i].height);
		info[i].rank = 1;
	}
	for (i = 0; i < iter; i++)
	{
		for (j = 0; j < iter; j++)
		{
			if (info[i].weight < info[j].weight&& info[i].height < info[j].height)
				(info[i].rank)++;
		}
	}
	for (i = 0; i < iter; i++)
		printf("%d ", info[i].rank);
	return 0;

}
