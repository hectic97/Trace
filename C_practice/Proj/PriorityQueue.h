#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "UsefulHeap.h"

typedef Heap PQueue;
typedef HData PQData;

void PQueueInit(PQueue* ppq, PriorityComp pc)
{
	HeapInit(ppq, pc);
}
int PQIsEmpty(PQueue* ppq)
{
	return HIsEmpty(ppq);
}
void PEnqueue(PQueue* ppq, PQData data)
{
	HInsert(ppq, data);
}
PQData PDequeue(PQueue* ppq)
{
	return HDelete(ppq);
}
#endif // !__PRIORITY_QUEUE_H__
