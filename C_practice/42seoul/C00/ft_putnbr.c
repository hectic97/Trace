#include <unistd.h>

void prt_num(int n)
{
    char zero = '0';
    int degree = 1000000000;
    char c ='0';
    int start = 0;
    
    while(1)
    {
        
        if((n/degree)!= 0 || start == 1)
        {
            c = n/degree + 48;
            write(1,&c,1);
            start = 1;

        }
        n= n%degree;
        degree /= 10;   
        
        if((n/10 == 0)&& degree==0)
        {
            write(1,&n,1);
            break;
        }
        
    }

}

void ft_putnbr(int nb)
{
    char zero = '0';
    int degree = 1000000000;
    char c ='0';
    if (nb ==0)
    {
        write(1,&zero,1);
    }
    else if (nb >0)
    {
        prt_num(nb);
    }
    else
    {
        char mns = '-';
        write(1,&mns,1);
        prt_num(nb*-1);
    }
    
}
