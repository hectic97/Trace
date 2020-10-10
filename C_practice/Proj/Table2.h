#ifndef __TABLE2_H__
#define __TABLE2_H__
#include "Slot2.h"
#include "DLinkedList.h"
#define MAX_TBL 100

typedef int (*HashFunc) (int k);

typedef struct _table
{
	List tbl[MAX_TBL];
	HashFunc* hf;
}Table;

void TBLInit(Table* pt, HashFunc* f)
{
	int i;
	for (i = 0; i < MAX_TBL; i++)
		ListInit(&(pt->tbl[i])); //Each Table - linkedlist
	pt->hf = f;
}



Value TBLDelete(Table* pt, Key k)
{
	int hv = pt->hf(k);
	Slot cSlot;

	if (LFirst(&(pt->tbl[hv]), &cSlot))
	{
		if (cSlot.key == k)
		{
			LRemove(&(pt->tbl[hv]));
			return cSlot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &cSlot))
			{
				if (cSlot.key == k)
				{
					LRemove(&(pt->tbl[hv]));
					return cSlot.val;
				}
			}
		}
	}
	return NULL;
}

Value TBLSearch(Table* pt, Key k)
{
	int hv = pt->hf(k);
	Slot cSlot;

	if (LFirst(&(pt->tbl[hv]), &cSlot))
	{
		if (cSlot.key == k)
		{
			
			return cSlot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &cSlot))
			{
				if (cSlot.key == k)
				{
					
					return cSlot.val;
				}
			}
		}
	}
	return NULL;
}

void TBLInsert(Table* pt, Key k, Value v)
{
	
	int hv = pt->hf(k);
	Slot ns = { k,v };

	if (TBLSearch(pt, k) != NULL)
	{
		printf("Key Interrupted\n");
		return;
	}
	else
		LInsert(&(pt->tbl[hv]), ns);
}
#endif // !__TABLE2_H__
