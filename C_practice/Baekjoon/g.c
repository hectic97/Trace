#include <stdio.h>
#include <stdlib.h>

typedef struct poly {
    int degree;  //최고차항 지수 
    int* coef;   // 최고차항지수+1만큼 동적할당  -> 계 수 
}poly;

/*문자상수 -> 숫자 : 문자상수-'0'
문자열 ->정수 :atoi(문자열)*/
int first(char* p);
int cut(char* p, int pos, int* expo);
void add(poly a, poly b);

int main(int argc, char* argv[]) {
    struct poly p, q;
    char str2[100];
    char str[100];
    int i = 0, expo, temp;
    int cnt = 0, j = 0;



    /*; printf(">> ");
     gets(str);   //2x^6-32x^5-4x^3+x-12*/
    printf("식 1 입력:");
    scanf("%s", str);

    printf("식 2 입력 :");
    scanf("%s", str2);

    p.degree = first(str);
    q.degree = first(str2);

    printf("%s\n", str);
    printf("%s\n", str2);

    p.coef = (int*)calloc((p.degree + 1), sizeof(int));
    q.coef = (int*)calloc((q.degree + 1), sizeof(int));


    for (i = 0; i < p.degree; i++) {

        temp = cut(str, i, &expo);
        //printf("i=%d 차수: %d 위치 %d\n",i,expo,p.degree-expo); 
        p.coef[p.degree - expo] = temp;

    }


    for (i = 0; i < q.degree; i++) {

        temp = cut(str2, i, &expo);
        //printf("i=%d 차수: %d 위치 %d\n",i,expo,q.degree-expo); 
        q.coef[q.degree - expo] = temp;

    }


    printf("최고차항 지수 : %d\n", q.degree);
    printf("계수 : { ");
    for (j = 0; j < p.degree + 1; j++) {
        printf("%2d, ", p.coef[j]);
    }
    printf("}\n");

    add(p, q);

    return 0;
}
int first(char* p) {

    int i = 0;

    while (*p != '\0') {

        if (*p == '^') {
            return *(p + 1) - '0';
        }
        i++; p++;

    }

    return 1;

}
int cut(char* p, int pos, int* expo) {

    int i = 0;
    int cnt = -1;
    char temp[10];

    while (*p != '\0') {

        if (pos == 0) {
            while (1) {
                temp[i++] = *p;
                p++;
                if (*p == 'x') {
                    temp[i] = '\0';
                    (*expo) = *(p + 2) - '0';
                    return atoi(temp);
                }
            }
        }

        else {
            while (1) {
                temp[i++] = *p;  p++;
                if (*p == '\0') {
                    temp[i] = '\0';   //x가 없을떄 상수 자르 
                    (*expo) = 0;
                    return atoi(temp);
                }
                if (*p == 'x') break;

            }

            p++;

            if (*p == '^') {
                cnt++;
            }

            if (cnt == pos) {
                temp[i] = '\0';
                (*expo) = *(p + 1) - '0';

                return atoi(temp);
            }

            else if (*p != '^') {//x가 있을때 상수 자르기 

                if (*expo == 1) {
                    i = 0;
                    while (1) {
                        temp[i++] = *p; p++;
                        if (*p == '\0') {
                            temp[i] = '\0';
                            (*expo) = 0;
                            return atoi(temp);
                        }
                    }
                }

                temp[i] = '\0';
                (*expo) = 1;
                return atoi(temp);
            }


            p++; i = 0;       //마지막의 제곱승 



        }

        p++;
    }
}

void add(poly a, poly b) {

    poly c;
    int A_deg = a.degree;
    int B_deg = b.degree;
    int apos = 0, bpos = 0, cpos = 0;
    int i, j;
    int temp = 0;
    char aa[10];
    char str[100];

    if (a.degree > b.degree) {
        c.degree = a.degree;
        c.coef = (int*)calloc((c.degree + 1), sizeof(int));

        for (i = 0; i <= b.degree; i++) {
            c.coef[c.degree - i] = a.coef[a.degree - i] + b.coef[b.degree - i];
        }

        for (i = b.degree + 1; i <= a.degree; i++) {
            c.coef[c.degree - i] = a.coef[a.degree - i];
        }

        for (i = 0; i < c.degree + 1; i++)
            printf(" %2d", c.coef[i]);


    }


    else if (a.degree == b.degree) {
        c.degree = a.degree;
        c.coef = (int*)calloc((c.degree + 1), sizeof(int));

        for (i = 0; i <= a.degree + 1; i++) {
            c.coef[c.degree - i] = a.coef[a.degree - i] + b.coef[b.degree - i];
        }

        for (i = 0; i < c.degree + 1; i++) {
            printf(" %2d", c.coef[i]);

        }

    }


    else if (a.degree < b.degree) {

        c.degree = b.degree;
        c.coef = (int*)calloc((c.degree + 1), sizeof(int));

        for (i = 0; i <= a.degree; i++) {
            c.coef[c.degree - i] = a.coef[a.degree - i] + b.coef[b.degree - i];
        }

        for (i = a.degree + 1; i <= b.degree; i++) {
            c.coef[c.degree - i] = b.coef[b.degree - i];
        }

        for (i = 0; i < c.degree + 1; i++)
            printf(" %2d", c.coef[i]);
    }

    strcpy(str, "\0");
    /* int num=-123;
     char str[10]
     itoa(num, str, 10);
       itoa(정수형데이터, 문자배열, 10);*/

    for (i = 0; i < c.degree - 1; i++) {
        if (c.coef[i] != 0) {
            if (c.coef[i] > 0) strcat(str, "+");
            itoa(c.coef[i], aa, 10);
            strcat(str, aa);
            strcat(str, "x^");
            itoa(c.degree - i, aa, 10);
            strcat(str, aa);
        }
    }

    if (c.coef[c.degree - 1] != 0) {
        if (c.coef[c.degree - 1] > 0) strcat(str, "+");
        itoa(c.coef[c.degree - 1], aa, 10);
        strcat(str, aa);
        strcat(str, "x");
    }

    if (c.coef[c.degree] != 0) {
        if (c.coef[c.degree] > 0) strcat(str, "+");
        itoa(c.coef[c.degree], aa, 10);
        strcat(str, aa);
    }

    printf("\n%s", str);
}
