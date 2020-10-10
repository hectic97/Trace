#include <stdio.h>
void De2Bi(int n)
{
	if (n == 0 || n == 1)
		printf("%d", n);
	else
	{
		De2Bi(n / 2);
		printf("%d", n % 2);
	}
}
int main(void)
{
	int n;
	scanf("%d", &n);
	De2Bi(n);
	return 0;
}