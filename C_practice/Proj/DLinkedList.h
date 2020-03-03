#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__
#include <stdlib.h>
#include "Slot2.h"
#define TRUE 1
#define FALSE 0
typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next;
}Node;

typedef struct _linkedList
{
	Node* head;
	Node* cur;
	Node* before;
	int numOfData;
	int (*comp)(LData d1, LData d2);
}LinkedList;

typedef LinkedList List;

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->cur = NULL;
	plist->numOfData = 0;

}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}
int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)
		return FALSE;
	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}
int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}
int LCount(List* plist)
{
	return (plist->numOfData);
}

void SetSortRule(List* plist, int(*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}
void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;
	newNode->data = data;
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}
	newNode->next = pred->next;
	pred->next = newNode;
	(plist->numOfData)++;
}
void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)
		FInsert(plist, data);
	else
		SInsert(plist, data);
}



















#endif 
