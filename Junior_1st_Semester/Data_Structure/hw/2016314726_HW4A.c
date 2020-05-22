#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
	int num;
	char str[130];
	int element[35];
	scanf("%d", &num);
	getchar();
	fgets(str, sizeof(str), stdin);
	int size = strlen(str);
	int i;
	int idx = 1;
	for (i = 0; i < 35; i++)
		element[i] = -1;

	for (i = 0; i < size-1; i++)
	{
		if (i > 0 && isdigit(str[i - 1]))
			continue;
		if (isdigit(str[i]))
		{
			int char2int = strtol(&str[i], NULL, 10);
			element[idx++] = char2int;

		}
		else if (str[i] == 'x')
			idx++;
		
		
	
	}
	
	for (i = 2; i <= 16;)
	{
		for (int j = 0; j < i ; j++)
		{
			if (element[i + j] != -1)
			{
				printf("%d ", element[i + j]);
				break;
			}
		}
		i = i * 2;
	}
	printf("\n");
	for (i = 4; i <= 32;)
	{
		for (int j = 0; j < i / 2; j++)
		{
			if (element[i - 1 - j] != -1)
			{
				printf("%d ", element[i - 1 - j]);
				break;
			}
		}
		i = i * 2;
	}
	return 0;
}