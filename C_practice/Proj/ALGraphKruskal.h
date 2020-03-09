#ifndef __AL_GRAPH_KRUSKAL__
#define _-AL_GRAPH_KRUSKAL__

#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "ALEdge.h"
#include "ArrayBaseStack.h"
enum{A,B,C,D,E,F,G,H,I,J};

typedef struct _ual
{
	int numV;
	int numE;
	List* adjList;
	int* visitInfo;
	PQueue pqueue;  //간선의 가중치 정보 저장
}ALGraph;

int PQWeightComp(Edge d1, Edge d2)
{
	return d1.weight - d2.weight;
}
void GraphInit(ALGraph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;

	for (i = 0; i < nv; i++)
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede);
	}
	pg->visitInfo = (int*)malloc(sizeof(int) * pg->numV);// 정점수 만큼 배열생성
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	PQueueInit(&(pg->pqueue), PQWeightComp);
}

void GraphDestory(ALGraph* pg)
{
	if (pg->adjList != NULL)
		free(pg->adjList);
	if (pg->visitInfo != NULL)
		free(pg->visitInfo);
}


void AddEdge(ALGraph* pg, int fromV, int toV,int weight)
{
	Edge edge = { fromV,toV,weight };
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;

	PEnqueue(&(pg->pqueue), edge);
}
void ShowGraphEdgeInfo(ALGraph* pg)
{
	int i;
	int vx;
	for (i = 0; i < pg->numV; i++)
	{
		printf("%c와 연결된 정점: ", i + 65);
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
		//printf("%c ", visitV + 65);
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
	VisitVertex(pg, visitV); //시작 정점 방문
	SPush(&stack, visitV);

	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;
		if (VisitVertex(pg, nextV) == TRUE) //방문 성공
		{
			SPush(&stack, visitV);
			visitV = nextV; // 다음 정점에 대해 탐색하기 위해 변경
			visitFlag = TRUE;
		}
		else //방문 실패
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE) //다른 정점 찾기
			{
				if (VisitVertex(pg, nextV) == TRUE) //방문 성공
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		if (visitFlag == FALSE) // 아무 정점 방문 X (이어진 모든 정점을 이미 방문)
		{
			if (SIsEmpty(&stack) == TRUE) // EMPTY STACK == END
				break;
			else
				visitV = SPop(&stack); // Back 
		}
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV); //탐색 정보 초기화
}

void ConKruskalMST(ALGraph* pg)
{
	Edge recvEdge[20];
	Edge edge;
	int eidx = 0;
	int i;

	while (pg->numE + 1 > pg->numV) // 간선의 수 +1 == 정점의 수
	{
		edge = PDequeue(&(pg->pqueue)); //가중치 제일 높은 간선
		RemoveEdge(pg, edge.v1, edge.v2); // 간선을 그래프에서 삭제

		if (!IsConnVertex(pg, edge.v1, edge.v2)) // 삭제후에도 두 정점 연결 간선 있는지 확인
		{
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight); //없으면 복원

			recvEdge[eidx++] = edge; //복원 간선 저장
		}
	}
	for (i = 0; i < eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);
}

void ShowGraphEdgeWeightInfo(ALGraph* pg)
{
	PQueue copyPQ = pg->pqueue;
	Edge edge;
	while (!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%c-%c), w:%d \n", edge.v1 + 65, edge.v2 + 65, edge.weight);
	}
}

void RemoveEdge(ALGraph* pg, int fromV, int toV)
{
	RemoveWayEdge(pg, fromV, toV);
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}
void RemoveWayEdge(ALGraph* pg, int fromV, int toV)
{
	int edge;
	if (LFirst(&(pg->adjList[fromV]), &edge))
	{
		if (edge == toV)
		{
			LRemove(&(pg->adjList[fromV]));
			return;
		}
		while (LNext(&(pg->adjList[fromV]), &edge))
		{
			if (edge == toV)
			{
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
}
void RecoverEdge(ALGraph* pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}
int IsConnVertex(ALGraph* pg, int v1, int v2)
{
	Stack stack;
	int visitV = v1;
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);

	while (LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE; //정점을 찾으면 TRUE반환
		if (nextV == v2)
		{
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV); //초기화 후
			return TRUE;
		}

		if (VisitVertex(pg, nextV) == TRUE)
		{
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else
		{
			while (LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if (nextV == v2)
				{
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}
				if (VisitVertex(pg, nextV) == TRUE)
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}

			}
		}
		if (visitFlag == FALSE)
		{
			if (SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = SPop(&stack);
		}
	}
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE //탐색실패
}
#endif // ! __AL_GRAPH_KRUSKAL__
