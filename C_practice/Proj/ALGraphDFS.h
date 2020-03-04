#ifndef __AL_GRAPH_DFS__
#define __AL_GRAPH_DFS__

#include "DLinkedList.h"
#include "ArrayBaseStack.h"

enum {A,B,C,D,E,F,G,H,I,J};
typedef struct _ual
{
	int numV;
	int numE;
	List* adjList;
	int* visitInfo;
}ALGraph;

int WhoIsPrecede(int data1, int data2);


void GraphInit(ALGraph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;

	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede)
	}
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);// ������ ��ŭ �迭����
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

void GraphDestory(ALGraph* pg)
{
	if (pg->adjList != NULL)
		free(pg->adjList);
	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph* pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]),toV);
	LInsert(&(pg->adjList[toV]),fromV);
	pg->numE += 1;
}

void ShowGraphEdgeInfo(ALGraph* pg)
{
	int i;
	int vx;
	for (i = 0; i < pg->numV; i++)
	{
		printf("%c�� ����� ����: ", i + 65);
		if (LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%c ", vx + 65);

			while (LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		printf("\n");
	}
}
int WhoIsPrecede(int data1, int data2)
{
	if (data1 < data2)
		return 0;
	else
		return 1;
}

int VisitVertex(ALGraph* pg, int visitV)
{
	if (pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;
		printf("%c ", visitV + 65);
		return TRUE;

	}
	return FALSE;
}

void DFShowGraphVertex(ALGraph* pg, int startV)
{
	Stack stack;
	int visitV = startV;
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV); //���� ���� �湮
	SPush(&stack, visitV);

	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;
		if (VisitVertex(pg, nextV) == TRUE) //�湮 ����
		{
			SPush(&stack, visitV);
			visitV = nextV; // ���� ������ ���� Ž���ϱ� ���� ����
			visitFlag = TRUE;
		}
		else //�湮 ����
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) //�ٸ� ���� ã��
			{
				if (VisitVertex(pg, nextV) == TRUE) //�湮 ����
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) // �ƹ� ���� �湮 X (�̾��� ��� ������ �̹� �湮)
		{
			if (SIsEmpty(&stack) == TRUE) // EMPTY STACK == END
				break;
			else
				visitV = SPop(&stack); // Back 
		}
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV); //Ž�� ���� �ʱ�ȭ
}
#endif
