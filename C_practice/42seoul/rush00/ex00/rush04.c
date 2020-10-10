#include <unistd.h>

void ft_putchar(char c);

void ptr_start_row(int x)
{
	if (x==0){
		return;
	}
	ft_putchar('A');
	if (x==1){
		ft_putchar('\n');
		return;
	}
	while(0<x-2){
		ft_putchar('B');
		x--;
	}
	ft_putchar('C');
	ft_putchar('\n');
}
void ptr_end_row(int x)
{
	if(x==0)
	{
		return;
	}
	ft_putchar('C');
	if(x==1)
	{
		ft_putchar('\n');
		return;
	}
	int i=0;
	while(x-2>0){
		ft_putchar('B');
		x--;
	}
	ft_putchar('A');
	ft_putchar('\n');
}

void ptr_row(int x)
{
	if(x==0){return;}
	ft_putchar('B');
	if(x==1){
		ft_putchar('\n');
		return;
	}
	while(x-2>0)
	{
		ft_putchar(' ');
		x--;
	}
	ft_putchar('B');
	ft_putchar('\n');
}


void rush(int x, int y)
{
	if (y==0){return;}
	ptr_start_row(x);
	if (y==1){	
		return;
	}
	while(y-2>0){
		ptr_row(x);
		y--;
	}
	ptr_end_row(x);
	return;
}


