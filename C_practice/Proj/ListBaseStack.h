#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
typedef int Data;
typedef struct _node
{
	Data data;
	struct _node* next;
	
}Node;

typedef struct _listStack
{
	Node* head;
}ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack)
{
	pstack->head = NULL;
}
int SIsEmpty(Stack* pstack)
{
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;
}
Data SPop(Stack* pstack)
{
	Data rdata;
	Node* rnode;
	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);
	return rdata;

}
Data SPeek(Stack* pstack)
{
	if (SIsEmpty(pstack)) {
		printf("Stack Memory Error!");
		exit(-1);
	}
	return pstack->head->data;
}

#endif // !__LB_STACK_H__
