/*
类型名称：队列(Queue)

数据对象集：一个有0个或多个元素的有穷线性表

操作集：长度为 MaxSize 的队列 Q ∈ Queue，队列元素 item ∈ ElementType
    1、Queue CreateQueue( int MaxSize )：生成长度为 MaxSize 的空队列；
    2、int IsFullQ( Queue Q, int MaxSize )：判断队列 Q 是否已满；
    3、void AddQ( Queue Q, ElementType item )：将数据元素 item 插入队列 Q 中；
    4、int IsEmptyQ( Queue Q )：判断队列 Q 是否为空；
    5、ElementType DeleteQ( Queue Q )：将队头数据元素从队列中删除并返回。
*/

/*
    循环队列的一个问题：如何判断是空还是满？
        1. 可以使用额外标记: size / tag
        2. 仅适用 n-1 个数组空间
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElementType;
typedef struct QNode *Queue;

struct QNode
{
    ElementType Data[MAXSIZE];
    int front;
    int rear;
};

// 操作集声明
Queue CreateQueue(int MaxSize);
int IsFullQ(Queue Q, int MaxSize);
void AddQ(Queue Q, ElementType item);
int IsEmptyQ(Queue Q);
ElementType DeleteQ(Queue Q);

// 操作集
Queue CreateQueue(int Maxsize)
{
    Queue q;
    q = (Queue)malloc(sizeof(struct QNode));
    q->front = 0;
    q->rear = 0;
    return q;
}

int IsFullQ(Queue Q, int MaxSize)
{
    return ((Q->rear + 1) % MAXSIZE == Q->front);
}

int IsEmptyQ(Queue Q)
{
    return (Q->front == Q->rear);
}

void AddQ(Queue Q, ElementType item)
{
    if (IsFullQ(Q, MAXSIZE))
    {
        printf("队列已满");
        return;
    }

    Q->rear = (Q->rear + 1) % MAXSIZE;
    Q->Data[Q->rear] = item;
}

ElementType DeleteQ(Queue Q)
{
    if (IsEmptyQ(Q))
    {
        printf("队列已空");
        return -1;
    }

    Q->front = (Q->front + 1) % MAXSIZE;
    return Q->Data[Q->front];
}

// 主函数
int main()
{
    Queue Q;
    Q = CreateQueue(MAXSIZE);

    AddQ(Q, 3);
    printf("3 入队\n");

    AddQ(Q, 5);
    printf("5 入队\n");

    AddQ(Q, 11);
    printf("11 入队\n");

    printf("%d 出队\n", DeleteQ(Q));
    printf("%d 出队\n", DeleteQ(Q));
    return 0;
}
