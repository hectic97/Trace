#include <stdio.h>
#include "check.c"
#include <memory.h>
#include <stdlib.h>

int check(int line[],int num);
int stack_1[6];
int stack_2[11];
int stack_3[24];
int stack_4[4];
int stack_1_index=0;
int stack_2_index=0;
int stack_3_index=0;
int stack_4_index=0;
int line[4];
int arr[4];
int line_ind = 0;
int data[4] = {1, 2, 3, 4};
int ct = 0;

void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void process(void)
{
    int* stack = malloc(sizeof(int)*4);
    for(int i = 3; i>= 0; i--){
            printf("%d ", arr[3-i]);
            line[i] = arr[3-i];
            
    }
    printf("\n");
    if(check(line,1))
    {
        // printf("CHECK: %d %d %d %d\n",line[0],line[1],line[2],line[3]);
        ct++;
        
        memcpy(stack,line,sizeof(line));
        line_ind = 0;
        while(line_ind<=3)
        {
            stack_1[stack_1_index++] = stack[line_ind++];
        }
        line_ind = 0;
    }
    else if (check(line,2))
    {

        
        memcpy(stack,line,sizeof(line));
        line_ind = 0;
        while(line_ind<=3)
        {
            stack_2[stack_2_index++] = stack[line_ind++];
        }
        line_ind = 0;

    }
    if (check(line,3))
    {
        memcpy(stack,line,4*4);
        
        while(line_ind<=3)
        {
            stack_3[stack_3_index++] = stack[line_ind++];
        }
        line_ind = 0;
    }
    else if (check(line,4))
    {
        memcpy(stack,line,4*4);
        while(line_ind<=3)
        {

            stack_4[stack_4_index++] = stack[stack_ind++];
            
            printf("SAVED %d %d\n",stack_4_index-1,stack_4[stack_4_index-1]);
        }
        
        // printf("svae? %d %d %d %d\n",stack_4[0],stack_4[1])
        line_ind = 0;
    }

    // 4-> 1 3 -> 6  2->11 1->6 따로 계산하는 .c파일 필요
 
}
void print_all(void)
{
    int p =0;
    for(p=0;p<stack_1_index;p+=4)
        printf("CHECK 1 : %d%d%d%d\n",stack_1[p],stack_1[p+1],stack_1[p+2],stack_1[p+3]);
    for(p=0;p<stack_2_index;p+=4)
        printf("CHECK 2 : %d%d%d%d\n",stack_2[p],stack_2[p+1],stack_2[p+2],stack_2[p+3]);
    for(p=0;p<stack_3_index;p+=4)
        printf("CHECK 3 : %d%d%d%d\n",stack_3[p],stack_3[p+1],stack_3[p+2],stack_3[p+3]);
    for(p=0;p<stack_4_index;p+=4)
        printf("CHECK 4 :%d %d%d%d%d\n",p,stack_4[0],stack_4[1],stack_4[2],stack_4[3]);
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
int main(void){
    Perm(4, 4); 
    printf("COUNT:%d",ct);
    print_all();
    return 0;
}