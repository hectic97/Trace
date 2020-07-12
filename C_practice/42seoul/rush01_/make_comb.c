#include <stdio.h>
#include "check.c"
#include <memory.h>
#include <stdlib.h>

int check(int line[],int num);
int line[4];
int arr[4];
int data[4] = {1, 2, 3, 4};
int ct = 0;
int all_comb[24][4];
int comb_index=0;
int m = 0;
void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void copyArr(int org[],int all_comb[])
{
    int *cp = malloc(4*sizeof(*cp));
    for(int i=0;i<4;i++)
    {
        cp[i] = org[i];
        all_comb[comb_index++] = cp[i];
    }
    printf("COMB_INDEX: %d\n",comb_index);
    free(cp);
}

void process(void)
{
    int* stack = malloc(sizeof(int)*4);
    for(int i = 3; i>= 0; i--){
            printf("%d ", arr[3-i]);
            line[i] = arr[3-i];
            // all_comb[comb_index++] = arr[3-i];
            // copyArr(line,all_comb);
            memcpy(all_comb[comb_index++],line,sizeof(line));
            
    }
    ct++;
    printf("\n");
    // 4-> 1 3 -> 6  2->11 1->6 따로 계산하는 .c파일 필요 
}

void Perm(int n, int r){
    if(r == 0){
        process();
        return;
    }
    for(int i = n-1; i>=0; i--){
        swap(&data[i], &data[n-1]);
        arr[r-1] = data[n-1];		 
        Perm(n-1, r-1);		  	
        swap(&data[i], &data[n-1]);
    }
}
int main(void)
{
    Perm(4, 4); 
    printf("COUNT:%d",ct);
    for(m=0;m<25;m+=1)
        printf("comb : %d %d %d %d\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
    return 0;
}