#include <stdio.h>
int main(void)
{
	char a[51];
	char b[51];
	scanf("%s %s", a, b);
	int a_len = 0,b_len = 0;
	while (a[a_len] != 0)
		a_len++;
	while (b[b_len] != 0)
		b_len++;
	int i,j;
	int gap = 0;
	int min = 50;
	for (j = 0; j <=( a_len>b_len? a_len - b_len:b_len-a_len); j++)
	{
		gap = 0;
		if (a_len > b_len)
		{
			for (i = 0; i < b_len; i++)
			{
				
				if (a[i+j] != b[i])
					gap++;
				
			}
			if (gap <= min)
				min = gap;
			
		}
			
		else if(a_len<=b_len)
		{
			for (i = 0; i < a_len; i++)
			{
				
				if (a[i] != b[i+j])
					gap++;
				
			}
			if (gap <= min)
				min = gap;
		}
		

	}
	printf("%d", min);
	return 0;

	

}