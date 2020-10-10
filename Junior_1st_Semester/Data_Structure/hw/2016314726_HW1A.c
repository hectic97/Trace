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
int PalindromeCheck(Stack* stack)
{
	int i;
	int results = 0;
	for (i = 0; i < ((stack->top) + 1) / 2; i++)
		if (stack->stackarr[i] != Pop(stack))
			results += 2;
	return results;
}
int main(void)
{
	Stack stack;
	StackInit(&stack);
	char sequence[101];
	scanf("%s", &sequence);
	int i = 0;
	while (sequence[i] != '\0')
	{
		Push(&stack, sequence[i]);
		i += 1;
	}
	printf("%d", PalindromeCheck(&stack));
	return 0;
}