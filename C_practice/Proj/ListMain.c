#include <stdio.h>
#include <stdlib.h>
#include "DBDLinkedList.h"

int main2(void)
{
	List list;
	Data data;
	ListInit(&list);
	LInsert(&list, 11); LInsert(&list, 11);
	LInsert(&list, 22); LInsert(&list, 22);
	LInsert(&list, 33); LInsert(&list, 44);
	printf("현재 데이터의 수 : %d\n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d", data);
		while (LNext(&list, &data))
			printf("%d", data);
		while (LPrevious(&list, &data))
			printf("%d", data);
	}
	printf("\n\n");
	if (LFirst(&list, &data))
	{
		if (data == 22)
			LRemove(&list);
		while (LNext(&list, &data))
		{
			if (data == 22)
				LRemove(&list);
		}
	}
	printf("현재 데이터의 수: %d\n", LCount(&list));
	if (LFirst(&list, &data))
	{
		printf("%d", data);
		while (LNext(&list, &data))
			printf("%d", data);
		while (LPrevious(&list, &data))
			printf("%d", data);
	}
	printf("\n\n");
	return 0;
}