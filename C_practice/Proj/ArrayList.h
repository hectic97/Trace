#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__
#define TRUE 1
#define FALSE 0
#define LIST_LEN 100
typedef int LData;
typedef struct __ArrayList
{
	LData arr[LIST_LEN];
	int numOfData;
	int curPosition;

}ArrayList;

typedef ArrayList List;
void ListInit(List* plist)
{
	(plist->numOfData) = 0;
	(plist->curPosition) = -1;
}
void LInsert(List* plist, LData data)
{
	if (plist->numOfData>=LIST_LEN)
	{
		puts("저장이 불가능 합니다.");
		return;
	}
	plist->arr[plist->numOfData] = data;
	(plist->numOfData)++;
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->numOfData == 0)
		return FALSE;
	(plist->curPosition) = 0;
	*pdata = plist->arr[0]; 
	return TRUE;
}
int LNext(List* plist, LData* pdata)
{
	if (plist->curPosition>=(plist->numOfData)-1)
		return FALSE;
	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List* plist)
{
	int rpos = plist->curPosition;
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];
	(plist->numOfData)--;
	(plist->curPosition)--;
	return rdata;
}
int LCount(List* plist)
{
	return plist->numOfData;
}

#endif