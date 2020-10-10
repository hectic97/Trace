#include<stdio.h>
#define ARR_LEN 1000

int visit[12][12];
int maze[12][12];

typedef struct _node {
    int x;
    int y;
}Node;

typedef struct _queue
{
    Node node[ARR_LEN];
    int tail;
    int head;
}Queue;

void InitQueue(Queue* q)
{
    q->tail = 0;
    q->head = 0;
}


int x_move[4] = { 0,0,1,-1 };
int y_move[4] = { 1, -1, 0, 0 };


Node Deque(Queue* q) 
{
    Node delNode = q->node[q->head];
    (q->head)++;
    return delNode;
}

int Empty(Queue *q) 
{
    if (q->head == q->tail) 
        return 0;
    else
        return 1;
}

void Enque(Queue *q,int y, int x)
{
    Node newNode = { x,y };
    q->node[q->tail] = newNode;
    (q->tail)++;
}

void BFS(Queue*q,int n,int m)
{
    int to_x, to_y;
    while (Empty(q))
    {
        Node f = Deque(q);
        for (int i = 0; i < 4; i++) 
        {
            to_x = f.x + x_move[i];
            to_y = f.y + y_move[i];
            if (to_x >= 1 && to_x <= m && to_y >= 1 && to_y <= n)  
                if (maze[to_y][to_x] == 0)
                    if (visit[to_y][to_x] == 0)
                    {
                        visit[to_y][to_x] = visit[f.y][f.x] + 1;
                        Enque(q,to_y, to_x);
                    }
                
            
        }
    }
}



int main(void)
{
    int i, j, m, n;
    scanf("%d %d", &n, &m);
    int min = m * n + 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%1d", &maze[i][j]);
    Queue queue;
    InitQueue(&queue);
    if (m == 1 && n == 1)
    {
        printf("%d", 1);
        return 0;
    }
    visit[1][1] = 1;
    Enque(&queue, 1, 1);
    BFS(&queue, n, m);
    if (visit[n][m] <= min && visit[n][m]!=0)
        min = visit[n][m];


    if (maze[1][1] != 1) // wall at the start point,spend a chance to break the wall   
    {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
            {
                for (int k = 1; k <= n; k++)
                    for (int l = 1; l <= m; l++)
                        visit[k][l] = 0;
                Queue queue;
                InitQueue(&queue);
                int change = 0;
                if (maze[i][j] == 1)
                {
                    maze[i][j] = 0;
                    change = 1;
                }
                visit[1][1] = 1;
                Enque(&queue, 1, 1);
                BFS(&queue, n, m);
              
                if (visit[n][m] <= min && visit[n][m]!=0)
                    min = visit[n][m];

                if (change==1)
                    maze[i][j] = 1;
            }
    }
    
    if (min == n * m + 1)
    {
        printf("%d", -1);
        return 0;
    }
    printf("%d", min);
    return 0;
    
}
//