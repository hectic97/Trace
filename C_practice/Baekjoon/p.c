#include <stdio.h>
int main(void)
{
	int a,num;
	num = 0;
	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &a);
		num += a * a;
	}
	printf("%d", num % 10);
	return 0;
}