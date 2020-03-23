#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int day;
	int pay;
}Cs;
int MaximizeIncome(Cs* cs, int from, int end)
{
	
	if (from >= end)
	{
		if (cs[from].day == 1)
		{
			
			return cs[from].pay;
		}
			
		else
		{
			
			return 0;
		}
			
	}
		
	if (from + cs[from].day - 1 > end)
		return	MaximizeIncome(cs, from + 1, end);
	else if (MaximizeIncome(cs, from + 1, end) > cs[from].pay+MaximizeIncome(cs, from + cs[from].day, end))
		return MaximizeIncome(cs, from + 1, end);
	else
		return cs[from].pay+MaximizeIncome(cs, from + cs[from].day, end);
		 
}
int main(void)
{
	int n,i;
	scanf("%d",&n);
	Cs* cs = (Cs*)malloc(sizeof(Cs) * n);
	for (i = 0; i < n; i++)
		scanf("%d %d",&cs[i].day,&cs[i].pay);
	printf("%d", MaximizeIncome(cs, 0, n - 1));
	return 0;


	
}