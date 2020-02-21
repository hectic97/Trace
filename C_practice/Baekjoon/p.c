#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(void)
{
	int iter;
	int x1,y1,r1,x2,y2,r2;
	scanf("%d",&iter);
	int results[iter];
	for (int i = 0; i < iter; i++)
	{
		scanf("%d %d %d %d %d %d",&x1,&y1,&r1,&x2,&y2,&r2);
		int d = (pow((x2 - x1), 2) + pow((y2 - y1), 2));
		if (x1 == x2 && x2 == y2 && r1 == r2)
			results[i] = -1;
		else if (pow((r2 - r1),2) > d || pow((r1 + r2),2) < d)
			results[i] = 0;
		else if (pow((r1 - r2),2) == d || pow((r1 + r2),2) == d)
			results[i] = 1;
		else
			results[i] = 2;

	}
	for (int i = 0; i < iter; i++)
		printf("%d\n", results[iter]);
	return 0;
}
