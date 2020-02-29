#include <stdio.h>
int Isinpl(int cx, int cy, int cr, int x, int y)
{
	if ((cx - x) * (cx - x) + (cy - y) * (cy - y) < cr * cr)
		return 1;
	else
		return 0;
}
typedef struct _planetary
{
	int cx;
	int cy;
	int cr;
}Pl;
int main(void)
{
	int i, iter,plnum,x1,x2,y1,y2,count;
	scanf("%d", &iter);
	for (i = 0; i < iter; i++)
	{
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		Pl pl[50] = { 0,0,0, };
		scanf("%d", &plnum);
		count = 0;
		for (int j = 0; j < plnum; j++)
		{
			scanf("%d %d %d", &pl[j].cx, &pl[j].cy, &pl[j].cr);
			if (Isinpl(pl[j].cx, pl[j].cy, pl[j].cr, x1, y1) && Isinpl(pl[j].cx, pl[j].cy, pl[j].cr, x2, y2))
				continue;
			else if (!Isinpl(pl[j].cx, pl[j].cy, pl[j].cr, x1, y1) && !Isinpl(pl[j].cx, pl[j].cy, pl[j].cr, x2, y2))
				continue;
			else
				count++;

		}
		printf("%d\n", count);

		

	}
	return 0;
	
	


	
}