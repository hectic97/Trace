#ifndef CHECK
#define CHECK

int check(int line[],int num)
{
    int max = 0;
    int i =0;
    int des = 0;
    while (i<=3)
    {
        if (line[i]>=max)
            max = line[i];
        else if (line[i] < max)
            des++;
        i++;
    }
    if (num != 4-des)
        return 0;
    return 1;
}

#endif