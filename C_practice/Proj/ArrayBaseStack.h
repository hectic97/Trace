#ifndef __AB_STACK_H__
#define __AB_STACK_H__
#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef int Data;
typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;

}ArrayStack;

typedef ArrayStack Stack;
void StackInit(Stack* pstack)
{
	pstack->topIndex = -1;
}
int SIsEmpty(Stack* pstack)
{
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data)
{
	pstack->topIndex += 1;
	pstack->stackArr[pstack->topIndex] = data;
}
Data SPop(Stack* pstack)
{
	int rIdx;

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}
	rIdx = pstack->topIndex;
	pstack->topIndex -= 1;
	return pstack->stackArr[rIdx];

}
Data SPeek(Stack* pstack)
{

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}
	
	
	return pstack->stackArr[pstack->topIndex];
}
#endif // !__AB_STACK_H__
