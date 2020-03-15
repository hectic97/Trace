#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef char Data;

typedef struct _node
{
	Data data;
	struct _node* next;
}Node;

typedef struct que
{
	Node* front;
	Node* rear;
	int numOfData;
}Queue;

void QueueInit(Queue* q)
{
	q->front = NULL;
	q->rear = NULL;
	q->numOfData = 0;
}

int QIsEmpty(Queue* q)
{
	if (q->front == NULL)
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue* q, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = data;
	if (QIsEmpty(q))
	{
		q->front = newNode;
		q->rear = newNode;

	}
	else
	{
		q->rear->next = newNode;
		q->rear = newNode;
	}
	(q->numOfData)++;
}

Data Dequeue(Queue* q)
{
	Node* delNode;
	Data retData;

	if (QIsEmpty(q))
	{
		return '-1';
	}
	delNode = q->front;
	retData = q->front->data;
	q->front = q->front->next;
	free(delNode);
	(q->numOfData)--;
	return retData;

}

Data QPeek(Queue* q,char position)
{
	if (q->numOfData == 0)
		return '-1';
	if (position = 'F')
	{
		return q->front->data;
	}
	else
		return q->rear->data;
}