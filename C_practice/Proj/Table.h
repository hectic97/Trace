#ifndef __TABLE_H__
#define __TABLE_H__
#include "Slot.h"
#define MAX_TBL 100

typedef int (*HashFunc)(Key K); //�Լ� ������ (HashFunc)
typedef struct _table
{
	Slot tbl[MAX_TBL];
	HashFunc* hf;   // hf = Hashfunc �Լ��� ����Ű�� ������ (�Լ��� ����Ǿ�� �Ѵ�)
}Table;

void TBLInit(Table* pt, HashFunc* f)
{
	int i;
	for (i = 0; i < MAX_TBL; i++)
		(pt->tbl[i]).status = EMPTY;
	pt->hf = f;
}
void TBLInsert(Table *pt,Key k,Value v)
{
	int hv = pt->hf(k); //hash key
	pt->tbl[hv].val = v;
	pt->tbl[hv].key = k;
	pt->tbl[hv].status = INUSE;

}

Value TBLDelete(Table* pt, Key k)
{
	int hv = pt->hf(k);

	if ((pt->tbl[hv]).status != INUSE)
	{
		return NULL;
	}
	else
	{
		(pt->tbl[hv]).status = DELETED;
		return (pt->tbl[hv]).val;
	}

}
Value TBLSearch(Table* pt, Key k)
{
	int hv = pt->hf(k);
	if ((pt->tbl[hv]).status != INUSE)
		return NULL;
	else
		return (pt->tbl[hv]).val;
}
#endif // !__TABLE_H__
