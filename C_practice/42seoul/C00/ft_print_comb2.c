#include <unistd.h>

void ft_print_comb2(void)
{
    // int a=0;
    // int b=0;
    char a = '0';
    char b = '0';
    char c = '0';
    char d = '0';
    char bl = ' ';
    char sc = ',';
    while(((a-48)*10+b-48)<=98)
    {
        if(b == '9')
        {
            c++;
            d = '0';

        }
        else
        {
            d++;
        }
        
        while(((c-48)*10+d-48)<=99)
        {
            write(1,&a,1);
            write(1,&b,1);
            write(1,&bl,1);
            write(1,&c,1);
            write(1,&d,1);
            if(!(a=='9' && b== '8'))
            {
                write(1,&sc,1);
                write(1,&bl,1);
            }
            if(d=='9')
            {
                c+= 1;
                d = '0';
            }
            else
            {
                d+=1;
            }
            
        }
        if(b=='9')
        {
            a += 1;
            b='0';
        }
        else
        {
            b+=1;
        }
        
    }

}
int main(void)
{
    ft_print_comb2();
    return 0;
}