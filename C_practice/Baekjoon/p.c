#include <stdio.h>
#include <stdlib.h>
int top = -1;
void Push(int* arr, int n)
{
	arr[++top] = n;
}
void Pop(int* arr)
{
	top--;
}
int main(void)
{
	int k, i,n;
	scanf("%d", &k);
	int* arr = (int*)malloc(sizeof(int) * k);
	for (i = 0; i < k; i++)
	{
		scanf("%d", &n);
		if (n == 0)
			Pop(arr);
		else
			Push(arr, n);
	}
	int sum = 0;
	for (i = 0; i <= top; i++)
		sum += arr[i];
	printf("%d", sum);
	return 0;

}