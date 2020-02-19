#include <stdio.h>
int main(void)
{
	int x, y, w, h;
	scanf("%d %d %d %d", &x, &y, &w, &h);
	int xdis,ydis;
	xdis = (double)w / 2 > (double)x ? x : w - x;
	ydis = (double)h / 2 > (double)y ? y : h - y;
	printf("%d", xdis < ydis ? xdis : ydis);
	return 0;
}