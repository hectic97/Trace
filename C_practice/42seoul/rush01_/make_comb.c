#ifndef COMB
#define COMB
#include <stdio.h>
#include "check.c"
#include <memory.h>
#include <stdlib.h>
#include <string.h>

int check(int line[],int num);
int line[4];
int arr[4];
int data[4] = {1, 2, 3, 4};
int ct = 0;
char all_comb[24][5];
int comb_index=0;
int m = 0;
void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}
char single[5];
void copyArr(int org[],int all_comb[])
{
    int *cp = malloc(4*sizeof(*cp));
    for(int i=0;i<4;i++)
    {
        cp[i] = org[i];
        all_comb[comb_index++] = cp[i];
    }
    printf("COMB_INDEX: %d\n",comb_index);
    // free(cp);
}

void process(void)
{
    int* stack = malloc(sizeof(int)*4);
    for(int i = 3; i>= 0; i--){
            // printf("%d ", arr[3-i]);
            line[i] = arr[3-i];
            // all_comb[comb_index++] = arr[3-i];
            // copyArr(line,all_comb);
            // memcpy(all_comb[comb_index++],line,sizeof(line));
            single[i] = arr[3-i]+48;
            
    }
    single[4] = 0;
    strcpy(all_comb[comb_index++],single);
    // printf("\n");
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
// int main(void)
// {
//     int for_check[4];
//     Perm(4, 4); 
//     printf("COUNT:%d\n",ct);
//     for(m=0;m<24;m+=1)
//     {
//             int i;
//             // printf("comb : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
//             for(i=0;i<4;i++)
//                 for_check[i] = all_comb[m][i]-48;
//             if(check(for_check,1))
//                 printf("IF 1 : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
//             else if(check(for_check,2))
//                 printf("IF 2 : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
//             else if(check(for_check,3))
//                 printf("IF 3 : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
//             else if(check(for_check,4))
//                 printf("IF 4 : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);

//     }
//     return 0;
// }
#endif