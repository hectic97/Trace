#ifndef __LB_QUEUE_H__
#define __LB_QUEUE_H__

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

typedef struct _lQueue
{
	Node* front;
	Node* rear;
}LQueue;

typedef LQueue Queue;

void QueueInit(Queue* pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}
int QIsEmpty(Queue* pq)
{
	if (pq->front == NULL)
		return TRUE;
	else
		return FALSE;

}
void Enqueue(Queue* pq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (QIsEmpty(pq))
	{
		pq->front = newNode;
		pq->rear = newNode;
		
	}
	else
	{
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}

Data Dequeue(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}
	Node* delNode = pq->front;
	Data retData = pq->front->data;
	pq->front = pq->front->next;
	free(delNode);
	return retData;
}
Data QPeek(Queue* pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}
	return pq->front->data;
}
#endif // !__LB_QUEUE_H__
