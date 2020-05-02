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
	Node* newNode =
		(Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}
void Remove(Node* head)
{
	Node* start = head;
	Node* ptr = (Node*)malloc(sizeof(Node));
	Node* before;
	while (start->next != NULL)
	{
		
		ptr = start;
		while (ptr->next != NULL)
		{
			before = ptr;
			ptr = ptr->next;
			if (start->data == ptr->data)
			{
				if (ptr->next != NULL)
				{
					before->next = ptr->next;
					free(ptr);
				}
				else
				{
					free(ptr);
					before->next = NULL;
				}
				ptr = malloc(sizeof(Node));
				ptr = before;
			}
		}
		if (start->next == NULL)
			break;
		start = start->next;
	}
}s
int main()
{
	int N, list[100];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
	Node* head = NULL;
	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	printList(head);
	Remove(head);
	printList(head);
	return 0;
}