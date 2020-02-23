#include <stdio.h>
#include <stdlib.h>
int* MakePsm(void)
{
	static int Psm[102];
	for (int i = 0; i < 102; i++)
		Psm[i] = i * i;
	return Psm;
}
int main(void)
{
	int m, n;
	scanf("%d %d",&m,&n);
	int* Psm = MakePsm();
	int i = 0;
	int j = 100;
	while (Psm[i] < m)
		i++;
	while (Psm[j] > n)
		j--;
	if (Psm[i] > n || Psm[j] < m)
	{
		printf("%d", -1);
		return 0;
	}
	int sum = 0;
	int smallest = Psm[i];
	for (; i <= j; i++)
		sum += Psm[i];
	printf("%d\n%d", sum,smallest);
	return 0;

	
}