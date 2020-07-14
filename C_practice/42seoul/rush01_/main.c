#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
// #include "check.c"
// #include "make_comb.c"


//func
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
int check(int line[],int num);
int line[4];
int arr[4];
int data[4] = {1, 2, 3, 4};
int ct = 0;
char all_comb[24][5];
int comb_index=0;
int m = 0;
int check_argv_index=8;
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

//func
// extern char all_comb[24][4];
// int check(int line[],int num);

int result[4][4];
int arr_1[6][4];
int arr_2[11][4];
int arr_3[6][4];
int arr_4[1][4];
int for_check[4];
int arr_1_ind=0;
int arr_2_ind=0;
int arr_3_ind=0;
int arr_4_ind=0;
int q=0;
int argv_index=0;
int argv_ind=0;
void make_arr(void)
{
    Perm(4,4);
    for(m=0;m<24;m+=1)
    {
            int i;
            // printf("comb : %c %c %c %c\n",all_comb[m][0],all_comb[m][1],all_comb[m][2],all_comb[m][3]);
            for(i=0;i<4;i++)
                for_check[i] = all_comb[m][i]-48;
            if(check(for_check,1))
            {
                while(q<=3)
                {
                    arr_1[arr_1_ind][q] = all_comb[m][q]-48;
                    q++;
                }
                q=0;
                arr_1_ind++;

            }
            else if(check(for_check,2))
            {
                while(q<=3)
                {
                    arr_2[arr_2_ind][q] = all_comb[m][q]-48;
                    q++;
                }
                q=0;
                arr_2_ind++;

            }
            else if(check(for_check,3))
            {
                while(q<=3)
                {
                    arr_3[arr_3_ind][q] = all_comb[m][q]-48;
                    q++;
                }
                q=0;
                arr_3_ind++;

            }
            else if(check(for_check,4))
            {
                while(q<=3)
                {
                    arr_4[arr_4_ind][q] = all_comb[m][q]-48;
                    q++;
                }
                q=0;
                arr_4_ind++;

            }
    }
}
void make_result(char* argv[],int chk)
{
    if(!chk)
    {
    while(argv_index <= 6)
    {
       
            if(argv[1][check_argv_index]-48 == 1)
            {
                result[0][argv_index/2] = arr_1[arr_1_ind][0];
                result[1][argv_index/2] = arr_1[arr_1_ind][1];
                result[2][argv_index/2] = arr_1[arr_1_ind][2];
                result[3][argv_index/2] = arr_1[arr_1_ind][3]; 
            }
            else if(argv[1][check_argv_index]-48 == 2)
            {
                result[0][argv_index/2] = arr_2[arr_2_ind][0];
                result[1][argv_index/2] = arr_2[arr_2_ind][1];
                result[2][argv_index/2] = arr_2[arr_2_ind][2];
                result[3][argv_index/2] = arr_2[arr_2_ind][3]; 
            }
            else if(argv[1][check_argv_index]-48 == 3)
            {
                result[0][argv_index/2] = arr_3[arr_3_ind][0];
                result[1][argv_index/2] = arr_3[arr_3_ind][1];
                result[2][argv_index/2] = arr_3[arr_3_ind][2];
                result[3][argv_index/2] = arr_3[arr_3_ind][3]; 
            }
            else if(argv[1][check_argv_index]-48 == 4)
            {
                result[0][argv_index/2] = arr_4[arr_4_ind][0];
                result[1][argv_index/2] = arr_4[arr_4_ind][1];
                result[2][argv_index/2] = arr_4[arr_4_ind][2];
                result[3][argv_index/2] = arr_4[arr_4_ind][3]; 
            }
            argv_index+=2;
    }
    }
    else
    {
        printf("argv_ind : %d\n",argv_ind);
        while(argv_ind <= 6)
        {
            

        
         if(argv[1][argv_ind]-48 == 1)
            {
                result[0][argv_ind/2] = arr_1[arr_1_ind][0];
                result[1][argv_ind/2] = arr_1[arr_1_ind][1];
                result[2][argv_ind/2] = arr_1[arr_1_ind][2];
                result[3][argv_ind/2] = arr_1[arr_1_ind][3]; 
            }
            else if(argv[1][argv_ind]-48 == 2)
            {
                result[0][argv_ind/2] = arr_2[arr_2_ind][0];
                result[1][argv_ind/2] = arr_2[arr_2_ind][1];
                result[2][argv_ind/2] = arr_2[arr_2_ind][2];
                result[3][argv_ind/2] = arr_2[arr_2_ind][3]; 
            }
            else if(argv[1][argv_ind]-48 == 3)
            {
                result[0][argv_ind/2] = arr_3[arr_3_ind][0];
                result[1][argv_ind/2] = arr_3[arr_3_ind][1];
                result[2][argv_ind/2] = arr_3[arr_3_ind][2];
                result[3][argv_ind/2] = arr_3[arr_3_ind][3]; 
            }
            else if(argv[1][argv_ind]-48 == 4)
            {
                result[0][argv_ind/2] = arr_4[arr_4_ind][0];
                result[1][argv_ind/2] = arr_4[arr_4_ind][1];
                result[2][argv_ind/2] = arr_4[arr_4_ind][2];
                result[3][argv_ind/2] = arr_4[arr_4_ind][3]; 
            }
            argv_ind+=2;
        }
    }
    
    

}

int main(int argc,char* argv[]) //colup coldown row left rowright  blank
{
    int chk=0;
    make_arr();
    arr_1_ind = 0;
    arr_2_ind = 0;
    arr_3_ind = 0;
    arr_4_ind = 0;
    make_result(argv,chk);
    int i,j,k,argv_index;
    i=0,j=0,k=0,argv_index=0;
    int for_check_arr[4];
    
    while(check_argv_index<=30)
    {
        for(int p=0;p<=3;p++)
        {
            for(int k=0;k<=3;k++)
            {
                printf("%d ",result[p][k]);
                if(k==3)
                    printf("\n");
            }
        }
        printf("\n");
            
        if (argv[1][check_argv_index]-48<=14)
        {
            for_check_arr[0] = result[3][check_argv_index/2-4];
            for_check_arr[1] = result[2][check_argv_index/2-4];
            for_check_arr[2] = result[1][check_argv_index/2-4];
            for_check_arr[3] = result[0][check_argv_index/2-4];
            argv_ind = 2*(check_argv_index/2-4);
        }
        else if (argv[1][check_argv_index]-48<=22)
        {
            for_check_arr[0] = result[check_argv_index/2-8][0];
            for_check_arr[1] = result[check_argv_index/2-8][1];
            for_check_arr[2] = result[check_argv_index/2-8][2];
            for_check_arr[3] = result[check_argv_index/2-8][3];
            argv_ind = 2*(check_argv_index/2-8);
        }
        else if (argv[1][check_argv_index]-48<=30)
        {
            for_check_arr[0] = result[check_argv_index/2-12][3];
            for_check_arr[1] = result[check_argv_index/2-12][2];
            for_check_arr[2] = result[check_argv_index/2-12][1];
            for_check_arr[3] = result[check_argv_index/2-12][0];
            argv_ind = 2*(check_argv_index/2-12);
        }
        if(!check(for_check_arr,argv[1][check_argv_index]-48))
        {
            // printf("CRASH\n");
            
            if(arr_3_ind<=5)
            {
                arr_3_ind++;
                
                make_result(argv,1);
            }
            else if (arr_2_ind<=10)
            {
                arr_2_ind++;
                make_result(argv,1);
            }
            else if (arr_1_ind<=5)
            {
                arr_1_ind++;
                make_result(argv,1);
            }   
        }
        check_argv_index+=2;
    }
    printf("RESULT\n");
    for(int p=0;p<=3;p++)
        for(int k=0;k<=3;k++)
        {
            printf("%d ",result[p][k]);
            if(k==3)
                printf("\n");
        }
             
}

