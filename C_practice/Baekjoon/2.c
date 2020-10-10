#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_HEAP 100

typedef enum { false, true } bool;

typedef struct {
	char small;
	char middle;
	char large;
} Penta_num;
typedef struct {
	Penta_num data; // This is a priority as well as data
} PNode;
typedef struct {
	PNode items[MAX_HEAP+ 1];
	int num;
} Heap;
void InitHeap(Heap* pheap);
bool IsEmpty(Heap* pheap);
bool IsFull(Heap* pheap);
void Insert(Heap* pheap, Penta_num data);
Penta_num Delete(Heap* pheap);
void HeapSort(Penta_num a[], int n);
Penta_num* CreatePentaNum(int n);
void GetInput();
int main() {
	GetInput();
	/*
	5
	0E0
	321
	EEE
	CCC
	3D0
	*/
	return 0;
}
void HeapSort(Penta_num a[], int n) {
	Heap heap;
	InitHeap(&heap);
	// Insert all elements to the heap.
	for (int i = 0; i < n; i++)
		Insert(&heap, a[i]);
	// Remove all elements from the heap.
	for (int i = 0; i <= n - 1; i++)
		a[i] = Delete(&heap);
	for (int i = 0; i < n; i++)
		printf("%c%c%c\n", a[i].large, a[i].middle, a[i].small);
}
Penta_num* CreatePentaNum(int n){
	char a[4];
	Penta_num* res = (Penta_num*)malloc(sizeof(Penta_num) * (n));
	for (int i = 0; i < n; i++) {
		scanf("%s", a);
		res[i].large = a[0];
		res[i].middle = a[1];
		res[i].small = a[2];
	}
	return res;
}
void GetInput() {
	int n;
	Penta_num* data;
	scanf("%d", &n);
	data = CreatePentaNum(n);
	HeapSort(data, n);
}
/* Modify from here */
void InitHeap(Heap* pheap)
{
	pheap->num = 0;
}

bool IsEmpty(Heap* pheap)
{
	return pheap->num == 0;
}

bool IsFull(Heap* pheap)
{
	return pheap->num == MAX_HEAP;
}

bool PriorityCheck(Penta_num data1, Penta_num data2) 
{
	if (data1.large > data2.large)
		return false;
	else if (data1.large < data2.large)
		return true;
	else if (data1.middle > data2.middle)
		return false;
	else if (data1.middle < data2.middle)
		return true;
	else if (data1.small > data2.small)
		return false;
	else if (data1.small < data2.small)
		return true;
	
	return true;
}

void Insert(Heap* pheap, Penta_num data)
{
	PNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap))
		exit(1);
	while (idx > 1)
	{
		int parent = idx / 2;
		if (PriorityCheck(data, pheap->items[parent].data))
		{
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else
			break;
	}
	newNode.data = data;
	pheap->items[idx] = newNode;
	pheap->num++;
}

int WhoFirst(Heap* pheap,int idx)
{
	if (idx * 2 > pheap->num)
		return 0;
	else if (idx * 2 == pheap->num)
		return idx * 2;
	else
	{
		if (PriorityCheck(pheap->items[idx * 2 + 1].data, pheap->items[idx * 2].data))
			return idx * 2 + 1;
		else
			return idx * 2;
	}
}

Penta_num Delete(Heap* pheap)
{
	Penta_num del = pheap->items[1].data;
	PNode last = pheap->items[pheap->num];
	int parent = 1;
	int child;
	while (child = WhoFirst(pheap, parent))
	{
		if (PriorityCheck(last.data, pheap->items[child].data))
			break;
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->num -= 1;
	return del;
}
/* Modify to here */