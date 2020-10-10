#ifndef  __SIMPLE_HEAP_H__
#define __SIMPLE_HEAP_H__

#define TRUE 1
#define FALSE 0

#define HEAP_LEN 100

typedef char HData;
typedef int Priority;

typedef struct _heapElem
{
	Priority pr;
	HData data;
}HeapElem;

typedef struct _heap
{
	int numOfData;
	HeapElem heaparr[HEAP_LEN];
}Heap;

void HeapInit(Heap* ph)
{
	ph->numOfData = 0;
}
int HIsEmpty(Heap* ph)
{
	if (ph->numOfData)
		return TRUE;
	else
		return FALSE;
}

int GetParantIDX(int idx)
{
	return idx / 2;
}
int GetLChildIDX(int idx)
{
	return idx * 2;
}
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap* ph, int idx)
{
	if (GetLChildIDX(idx) > ph->numOfData)
		return 0;

	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx);

	else
	{
		if (ph->heapArr[GetLChildIDX(idx)].pr > ph->heapArr[GetRChildIDX(idx)].pr)
			return GetRChildIDX(idx);
		else
			return GetLChildIDX(idx);
	}
}
void HInsert(Heap* ph, HData data, Priority pr)
{
	int idx = ph->numOfData + 1;
	HeapElem nelen = { pr,data };

	while (idx != 1)
	{
		if (pr < (ph->heapArr[GetParentIDX(idx)].pr))
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			idx = GetParentIDX(idx);
		}
		else
			break;
	}
	ph->heapArr[idx] = nelem;
	ph->numOfData += 1;
}
HData HDelete(Heap* ph)
{
	HData retData = (ph->heapArr[1]).data;
	HeapElem lastElem = ph->heapArr[ph->numOfData];
	int parantIdx = 1;
	int childIdx;

	while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		if (lastElem.pr <= ph->heapArr[childIdx].pr)
			break;
		ph->heap[parentIdx] = ph->heapArr[childIdx];
		parentIdx = childIdx;
	}
	ph->heapArr[parentIdx] = ph->heapArr[childIdx];
	ph->numOfData -= 1;
	return retData;
}




#endif // ! __SIMPLE_HEAP_H__
