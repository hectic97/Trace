#include <stdio.h>
int main(void)
{
	int i;
	char str1[201];
	char str2[101];
	printf("Input string1: ");
	fgets(str1, 100, stdin);
	printf("Input string2: ");
	fgets(str2, 100, stdin);

	
	i = 0;
	while (*(str1+i) != 0)
		i++;
	int len1 = i;
	str1[len1 - 1] = ' ';
	i = 0;
	while (1)
	{
		if (*(str2+i) == '\n')
		{
			str1[len1] = 0;
			break;
		}
			
		str1[len1++] = str2[i];
		i++;
	}
		
	printf("Concatenated string: %s", str1);
	return 0;
	

}