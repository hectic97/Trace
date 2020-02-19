#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__
#define TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <stdio.h>

typedef int Data;
typedef struct _node
{
	Data data;
	struct _node* next;
}Node;
typedef struct _clinkedlist
{
	Node* tail;
	Node* cur;
	Node* before;
	int numOfData;
}CLinkedList;

typedef CLinkedList List;

void ListInit(List* plist)
{
	plist->before = NULL;
	plist->cur = NULL;
	plist->tail = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->tail == NULL)
	{
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
		plist->tail= newNode;
	}
	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)
		return FALSE;
	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)
		return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	if (rpos == plist->tail)
	{
		if (plist->tail == plist->tail->next)
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	free(rpos);
	(plist->numOfData)--;
	return rdata;
}


#endif // !__C_LINKED_LIST_H__
