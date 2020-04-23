#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct _st
{
	int coef;
	int exp;
}Ce;

typedef Ce Data;

void MergeTwoArea(Data arr[], int left, int mid, int  right)
{
	int fidx = left;
	int ridx = mid + 1;
	int i;

	Data* sortArr = (Data*)malloc(sizeof(Data) * (right + 1));
	int sidx = left;

	while (fidx <= mid && ridx <= right)
	{
		if (arr[fidx].exp >= arr[ridx].exp)
			sortArr[sidx] = arr[fidx++];
		else
			sortArr[sidx] = arr[ridx++];
		sidx++;
	}

	if (fidx > mid)
	{
		for (i = ridx; i <= right; i++, sidx++)
			sortArr[sidx] = arr[i];
	}
	else
	{
		for (i = fidx; i <= mid; i++, sidx++)
			sortArr[sidx] = arr[i];
	}
	for (i = left; i <= right; i++)
		arr[i] = sortArr[i];
	free(sortArr);

}

void MergeSort(Data arr[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}
typedef struct _node
{
	int coef;
	int exp;
	
	struct _node* next;
}Node;

typedef struct linkedlist
{
	Node* head;
	Node* tail;
	int numofData;
}List;

int Empty(List* lst)
{
	if (lst->numofData == 0)
		return 1;
	else
		return 0;
}
void initLinkedList(List *lst)
{
	lst->numofData = 0;
	lst->tail = NULL;
	lst->head = NULL;
}

void Push(List* lst, int coef, int exp)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->coef = coef;
	newNode->exp = exp;
	
	
	if (Empty(lst))
	{
		lst->head = newNode;
		lst->tail = newNode;
		
	}
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
	newNode->next = NULL;
	(lst->numofData)++;
}

void PrintList(List* lst)
{
	Node* ptr = lst->head;
	if (Empty(lst))
	{
		printf("Empty List\n");
		return;
	}
	while (ptr != NULL)
	{
		if (ptr->coef == 0)
		{
			
			if (ptr == lst->head)
			{
				lst->head =lst->head->next;
				
			}
			
			
		}
		else if (ptr->coef == 1)
		{
			if (ptr == lst->head)
			{
				
					printf("x^%d", ptr->exp);
				
			}
			else
			{
				if (ptr->coef >= 0)
					printf("+x^%d", ptr->exp);
				
			}
			
		}
		else if (ptr->coef == -1)
		{
			if (ptr == lst->head)
			{
				
				
					printf("-x^%d",  ptr->exp);
			}
			else
			{
				
					printf("-x^%d",  ptr->exp);
			}
		}
		else
		{
			if (ptr == lst->head)
			{
				if (ptr->coef >= 0)
					printf("%dx^%d", ptr->coef, ptr->exp);
				else
					printf("%dx^%d", ptr->coef, ptr->exp);
			}
			else
			{
				if (ptr->coef >= 0)
					printf("+%dx^%d", ptr->coef, ptr->exp);
				else
					printf("%dx^%d", ptr->coef, ptr->exp);
			}
		}
		
		ptr = ptr->next;
			
	}

}
Ce Delete(List* lst)
{
	Node* rpos = lst->head;
	Ce rdata = { rpos->coef,rpos->exp };

	if (Empty(lst))
	{
		printf("error");
		return rdata;
	}
	else if (rpos->next == NULL)
	{
		lst->head = NULL;
		lst->tail = NULL;
	}
	else
	{
		lst->head = lst->head->next;
	}
	free(rpos);
	(lst->numofData)--;
	return rdata;
		
		
}
void Merge2List(List* lst1, List* lst2, List* resultlst)
{
	Node* ptr1 = lst1->head;
	Node* ptr2 = lst2->head;
	Ce deldata,deldata2;
	
	while (1)
	{
		if (ptr1->exp > ptr2->exp)
		{
			deldata = Delete(lst1);
			Push(resultlst, deldata.coef, deldata.exp);
			ptr1 = lst1->head;
		}
		else if (ptr1->exp < ptr2->exp)
		{
			deldata2 = Delete(lst2);
			Push(resultlst, deldata2.coef, deldata2.exp);
			ptr2 = lst2->head;
		}
		else
		{
			deldata = Delete(lst1);
			deldata2 = Delete(lst2);
			Push(resultlst, deldata.coef + deldata2.coef, deldata.exp);
			ptr1 = lst1->head;
			ptr2 = lst2->head;
		}
		if (ptr1 == NULL)
		{
			while (lst2->numofData != 0)
			{
				deldata2 = Delete(lst2);
				Push(resultlst, deldata2.coef, deldata2.exp);
				ptr2 = lst2->head;
			}
			break;
		}
		if (ptr2 == NULL)
		{
			while (lst1->numofData != 0)
			{
				deldata = Delete(lst1);
				Push(resultlst, deldata.coef, deldata.exp);
				ptr1 = lst1->head;
			}
			break;
		}
	}
	
	
}

int main(void)
{
	char ch1[1000];
	int arr[100];
	char ch2[1000];
	int arr2[100];
	scanf("%s", ch1);
	scanf("%s", ch2);
	int size = strlen(ch1);
	int i;
	int j = 0;
	for (i = 0; i < size; i++)
	{
		if (i==0 && ch1[i] == 'x')
		{
			arr[j++] = 1;
			
			continue;
		}
		if (ch1[i - 1] == '+' && ch1[i] == 'x')
		{
			arr[j++] = 1;
			continue;
		}
			
		if (ch1[i - 1] == '-' && ch1[i] == 'x')
		{
			arr[j++] = -1;
			continue;
		}
			
		if (i > 0 && isdigit(ch1[i - 1]))
			continue;
		if (isdigit(ch1[i]))
		{
			int num = strtol(&ch1[i], NULL, 10);
			if (i > 0 && ch1[i - 1] == '-')
				num *= -1;
			arr[j++] = num;
		}
	}
	int arrlen = j;
	j = 0;
	size = strlen(ch2);
	for (i = 0; i < size; i++)
	{
		if (i==0 && ch2[0] == 'x')
		{
			arr2[j++] = 1;
			continue;
		}
		if (ch2[i - 1] == '+' && ch2[i] == 'x')
			arr2[j++] = 1;
		if (ch2[i - 1] == '-' && ch2[i] == 'x')
			arr2[j++] = -1;
		if (i > 0 && isdigit(ch2[i - 1]))
			continue;
		if (isdigit(ch2[i]))
		{
			int num2 = strtol(&ch2[i], NULL, 10);
			if (i > 0 && ch2[i - 1] == '-')
				num2 *= -1;
			arr2[j++] = num2;
		}
	}
	for (i = 0; i < arrlen; i++)
		printf("arr:%d ", arr[i]);
	int arr2len = j;
	Ce ce1[50];
	Ce ce2[50];
	for (j=0,i = 0; i < arrlen;)
	{
		ce1[j].coef = arr[i++];
		ce1[j++].exp = arr[i++];
	}
	for (j=0,i = 0; i < arr2len;)
	{
		ce2[j].coef = arr2[i++];
		ce2[j++].exp = arr2[i++];
	}
	MergeSort(ce1, 0, arrlen / 2 - 1);
	MergeSort(ce2, 0, arr2len / 2 - 1);
	for (j=0,i = 0; i < arrlen; )
	{
		arr[i++] = ce1[j].coef;
		arr[i++] = ce1[j++].exp;
	}
	for (j = 0, i = 0; i < arr2len; )
	{
		arr2[i++] = ce2[j].coef;
		arr2[i++] = ce2[j++].exp;
	}
	
	List lst1, lst2,resultlst;
	initLinkedList(&lst1);
	initLinkedList(&lst2);
	initLinkedList(&resultlst);
	
	for (i = 0; i < arrlen;)
	{
		Push(&lst1, arr[i], arr[i + 1]);
		i += 2;
	}
	for (i = 0; i < arr2len;)
	{
		Push(&lst2, arr2[i], arr2[i + 1]);
		i += 2;
	}
	
	PrintList(&lst1);
	printf("\n");
	PrintList(&lst2);
	printf("\n");
	Merge2List(&lst1, &lst2, &resultlst);
	PrintList(&resultlst);
	return 0;


	
		
}