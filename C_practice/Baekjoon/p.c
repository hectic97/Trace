#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct _node
{
	int data;
	struct _node* next;
	struct _node* before;
}Node;
typedef struct _stack
{
	Node* head;
	Node* tail;
	int numOfData;

}Stack;

void InitStack(Stack* st)
{
	st->head = NULL;
	st->tail = NULL;
	st->numOfData = 0;
}

void Push(Stack* st, int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	
	if (st->numOfData == 0)
	{
		st->head = newNode;
		newNode->before = NULL;
	}
		
	else
	{
		newNode->before = st->tail;
		st->tail->next = newNode;
	}
		
	
	st->tail = newNode;
	(st->numOfData)++;
}

int Size(Stack* st)
{
	return st->numOfData;
}

int Empty(Stack* st)
{
	if (Size(st) == 0)
		return 1;
	else
		return 0;
}

int Top(Stack* st)
{
	if (Empty(st))
		return -1;
	return st->tail->data;
}

int Pop(Stack* st)
{
	if (Empty(st))
		return -1;
	Node* dNode;
	dNode = st->tail;
	int ddata = dNode->data;
	
	if (st->tail->before ==NULL)
	{
		st->head = NULL;
		st->tail = NULL;
		
		
	}
	else {
		st->tail = st->tail->before;
		st->tail->next = NULL;
	}
	
	free(dNode);
	(st->numOfData)--;
	
	return ddata;

}
int getnum(char input[])
{
	int len = strlen(input)-1;
	double num = 0,i=0;
	for (;len>=5;len--)
	{
		num += pow(10, i) * (input[len] - 48);
		i++;
	}
	return num;
}
int main(void)
{
	int iter;
	scanf("%d",&iter);
	
	
	
	Stack stack;
	InitStack(&stack);
	char input[13];
	for (int i = 0; i < iter; i++)
	{
		while (getchar() != '\n');
		scanf("%[^\n]s",input);
		
		if (input[1] == 'u')
			Push(&stack, getnum(input));
		else if (input[0] == 't')
			printf("%d\n", Top(&stack));
		else if (input[0] == 's')
			printf("%d\n", Size(&stack));
		else if (input[0] == 'e')
			printf("%d\n", Empty(&stack));
		else
			printf("%d\n", Pop(&stack));
		
		
	}
	return 0;
}
