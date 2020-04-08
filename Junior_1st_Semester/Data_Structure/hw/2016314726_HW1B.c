#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 101
typedef char Data;
typedef struct _stack
{
	int top;
	Data stackarr[MAX_LEN];
	
}Stack;
void StackInit(Stack* stack)
{
	stack->top = -1;
}
void Push(Stack* stack, Data data)
{
	stack->top += 1;
	stack->stackarr[stack->top] = data;
}
Data Pop(Stack* stack)
{
	int ridx;
	if (stack->top == -1)
		exit(-1);   //EMPTY STACK ERROR  EXIT
	ridx = stack->top;
	stack->top -= 1;
	return stack->stackarr[ridx];
}

int main(void)
{
	Stack stack;
	StackInit(&stack);
	char sequence[101];
	int count[101] = { 0, };
	char pair_char[101];
	scanf("%s", &sequence);
	int i = 0;
	int len = 0;
	int j;
	while (sequence[i] != '\0')
	{
		Push(&stack, sequence[i]);
		i += 1;
	}
	len = i;
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			if (sequence[i] == sequence[j])
				count[i] += 1;
	Stack single;
	Stack pair;
	StackInit(&single);
	StackInit(&pair);
	for (i = len - 1; i >= 0; i--)
	{
		if (count[i] == 1)
			Push(&single, Pop(&stack));
		else if (count[i] <= 0)
			Pop(&stack);
		else
		{
			if (count[i] % 2 == 0)
			{
				for (j = 0; j < i; j++)
					if (sequence[j] == sequence[i])
						count[j] -= 2;
				Push(&pair, Pop(&stack));
			}
			else
			{
				for (j = 0; j < i; j++)
					if (sequence[j] == sequence[i])
						count[j] -= 1;
				Push(&single, Pop(&stack));
			}
		}
	}
	for (i = 0; i <= pair.top; i++)
		printf("%c", pair.stackarr[i]);
	if (single.top != -1)
		printf("%c", single.stackarr[0]);
	while (pair.top != -1)
		printf("%c", Pop(&pair));

	return 0;
}