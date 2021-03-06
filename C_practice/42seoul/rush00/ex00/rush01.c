#include <unistd.h>

void ft_putchar(char c); // from ft_putchar.c

void ptr_start_row(int x) // for first row
{
	if (x==0){    
		return;
	}
	ft_putchar('/'); //first char
	if (x==1){
		ft_putchar('\n'); 
		return;
	}
	while(0<x-2){
		ft_putchar('*'); // middle char
		x--;
	}
	ft_putchar('\\'); // last char
	ft_putchar('\n');
}
void ptr_end_row(int x) //for last row
{
	if(x==0)
	{
		return;
	}
	ft_putchar('\\');
	if(x==1)
	{
		ft_putchar('\n');
		return;
	}
	int i=0;
	while(x-2>0){
		ft_putchar('*');
		x--;
	}
	ft_putchar('/');
	ft_putchar('\n');
}

void ptr_row(int x) // for middle rows
{
	if(x==0){return;}
	ft_putchar('*');
	if(x==1){
		ft_putchar('\n');
		return;
	}
	while(x-2>0)
	{
		ft_putchar(' ');
		x--;
	}
	ft_putchar('*');
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


