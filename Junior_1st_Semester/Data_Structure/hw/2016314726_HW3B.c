#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef char Data;

typedef struct _node
{
	Data data;
	int Calnum;
	struct _node* next;
}Node;

typedef struct _stack
{
	Node* head;
}Stack;

void InitStack(Stack* st)
{
	st->head = NULL;
}

int IsEmpty(Stack* st)
{
	if (st->head == NULL)
		return 1;
	else
		return 0;
}

void Push(Stack* st, Data data)
{
	Node* postNode = (Node*)malloc(sizeof(Node));

	postNode->data = data;
	postNode->next = st->head;
	st->head = postNode;

}

void CalPush(Stack* st, int data)
{
	Node* postNode = (Node*)malloc(sizeof(Node));

	postNode->Calnum = data;
	postNode->next = st->head;
	st->head = postNode;

}

Data Pop(Stack* st)
{
	char rd;
	Node* rnode;

	if (IsEmpty(st))
		exit(-1);
	rd = st->head->data;
	rnode = st->head;

	st->head = st->head->next;
	free(rnode);
	return rd;
}

int CalPop(Stack* st)
{
	int rd;
	Node* rnode;

	if (IsEmpty(st))
		exit(-1);
	rd = st->head->Calnum;
	rnode = st->head;

	st->head = st->head->next;
	free(rnode);
	return rd;
}
Data Peek(Stack* st)
{
	if (IsEmpty(st))
		exit(-1);
	return st->head->data;
}
int CalPeek(Stack* st)
{
	if (IsEmpty(st))
		exit(-1);
	return st->head->Calnum;
}
int Oplevel(char op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	case '(':
		return 1;
	}
	return -1;
}

char* In2Post(char a[])
{
	Stack stack;
	int len = strlen(a);
	char* post = (char*)malloc(2*(len+1));

	int i, idx = 0;
	char b, c;
	memset(post, 0, sizeof(char) * 2*(len + 1));
	InitStack(&stack);

	for (i = 0; i < len; i++)
	{
		b = a[i];
		//printf("B: %c\n", b);
		if (('0' <= b && b <= '9'))
		{
			while ('0' <= a[i] && a[i] <= '9')
			{
				post[idx++] = a[i++];
				//printf("num idx: %d\n", idx-1);

			}
			post[idx++] = ' ';
			i--;
		}
		else if (b == 'x')
		{
			post[idx++] = 'x';
			post[idx++] = ' ';
		}
		else
		{
			switch (b)
			{
			case '(':
				
				Push(&stack, b);
				//printf("STACKIN '(\n");
				break;
			case ')':
				while (1)
				{
					c = Pop(&stack);
					if (c == '(')
						break;
					//printf("PEEK ele:%c\n", Peek(&stack));
					post[idx++] = c;
					post[idx++] = ' ';
					//printf(")STACKOUT\n");
				}
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				while (!IsEmpty(&stack) && (Oplevel(Peek(&stack)) >= Oplevel(b)))
				{
					post[idx++] = Pop(&stack);
					post[idx++] = ' ';
				}
				Push(&stack, b);
				//printf("%c IN STACK!\n", Peek(&stack));
				break;
			}
		}
	}

	while (!IsEmpty(&stack))
	{
		post[idx++] = Pop(&stack);
		post[idx++] = ' ';
	}
	post[idx - 1] = 0;
	return post;
	//strcpy(a, post);
	
}

char* X2int(char post[],char num)
{
	char* x2intpost = malloc(sizeof(char) * 300);
	strcpy(x2intpost, post);
	for (int i = 0; i < strlen(x2intpost); i++)
	{
		if (x2intpost[i] == 'x')
			x2intpost[i] = num;
	}
	return x2intpost;
}

int CalPost(char* post)
{
	
	Stack stack;
	InitStack(&stack);
	int len = strlen(post);
	//printf("LEN OF POST : %d\n", len);
	//printf("STACK : %ld\n", strtol(&post[0], NULL, 10));
	CalPush(&stack, (int)strtol(&post[0], NULL, 10));
	//printf("First word : %c,STACK: %d\n", post[0], CalPeek(&stack));
	//printf("PUSH FIN\n");
	for (int i = 1; i < len; i++)
	{
		//printf("LOOP\n");
		if (post[i] == ' ')
			continue;
		else if (isdigit(post[i - 1]) && isdigit(post[i]))
			continue;
		else if (isdigit(post[i]) && (post[i - 1] == ' '))
		{

			CalPush(&stack, (int)strtol(&post[i], NULL, 10));
			//printf("want to push :%d\n", (int)strtol(&post[i], NULL, 10));
			//printf("ind %d word : %c,STACK: %d\n" ,i,post[i],CalPeek(&stack));
		}
			
		else
		{
			int op2 = CalPop(&stack);
			int op1 = CalPop(&stack);
			switch(post[i])
			{
			case '+': CalPush(&stack, op1+op2); break;
			case '-': CalPush(&stack, op1 - op2); break;
			case '*': CalPush(&stack, op1 * op2); break;
			
			}
		}

	}
	return CalPeek(&stack);


}
int main(void)
{
	char A[101];
	int P, M;
	scanf("%s", A);
	scanf("%d %d",&P,&M);
	char post[202];
	strcpy(post,In2Post(A));
	
	//printf("%s\n", post);
	int i=9;
	int min = 10;
	int result;
	for (i; i >= 1; i--)
	{
		char x2intpost[300];
		//printf("HERE\n");
		strcpy(x2intpost, X2int(post, i+48));
		//printf("COPY COM\n");
		//printf("%s\n", x2intpost);
		
		result=CalPost(x2intpost);
		if (result % M == P)
			min = i;
			
		

	}
	printf("%d", min);
	return 0;
}