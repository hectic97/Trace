#include <stdio.h> 
#include <stdlib.h>

typedef struct _Node 
{ 
	int data; 
	struct _Node* next; 
}Node;

void printList(Node* head)
{
	Node* ptr = head;
	while (ptr)
	{
		printf("%d ", ptr->data);
		printf("-> ");
		ptr = ptr->next;
	}
	printf("NULL");
	printf("\n");
}
void push(Node** head, int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head; 
	*head = newNode;
}
Node* Reserve(Node* head, int g)
{
	int i, j,temp;
	int remainder = 0;       
	Node* from = head;
	Node* end;
	Node* freeptr = head;
	Node* start;
	
	while (remainder == 0)  //remainder == 0 means absoulte part
	{
		freeptr = from;
	
		
		int count = 1;
		for (i = 0; i < g-1; i++)
		{
			if (freeptr->next == NULL)
			{
				remainder = 1;
				break;
			}
			freeptr = freeptr->next;
			count++;
		}
		
		if (remainder == 0)
		{
			end = freeptr;
			
			start = from;
			for (i = 0; i < g / 2; i++)
			{
				
				freeptr = start;
				temp = from->data;
				for (j = 0; j < g - i-1; j++)
					freeptr = freeptr->next;
				from->data = freeptr->data;
				
				freeptr->data = temp;
				
				from = from->next;
				
			}
			if (end->next == NULL)
				remainder = 1;
			else
				from = end->next;

		}
		else
		{
			end = freeptr;
			start = from;
			
			for (i = 0; i < count / 2; i++)
			{
				freeptr = start;
				temp = from->data;
				for (j = 0; j < count - i-1; j++)
					freeptr = freeptr->next;
				from->data = freeptr->data;
				freeptr->data = temp;
				from = from->next;
				
			}
			
		}
		
	}
	
	return head;
	
	

}
int main()
{
	int N, list[100], g;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
	Node* head = NULL;
	scanf("%d", &g);
	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	printList(head);
	head = Reserve(head, g);
	printList(head);
	return 0;
}