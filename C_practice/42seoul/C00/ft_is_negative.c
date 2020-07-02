#include <unistd.h>

void ft_is_negative(int n)
{
    char c = 'P';
    
    if(n<0)
    {
         c = 'N';
    }
    write(1,&c,1);
    

}
