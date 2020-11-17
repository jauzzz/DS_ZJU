/*
类型名称：队列(Queue)

数据对象集：一个有0个或多个元素的有穷线性表

操作集：长度为 MaxSize 的队列 Q ∈ Queue，队列元素 item ∈ ElementType
    1、Queue CreateQueue( int MaxSize )：生成长度为 MaxSize 的空队列；
    3、void AddQ( Queue Q, ElementType item )：将数据元素 item 插入队列 Q 中；
    4、int IsEmptyQ( Queue Q )：判断队列 Q 是否为空；
    5、ElementType DeleteQ( Queue Q )：将队头数据元素从队列中删除并返回。
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct QNode *Queue;

struct Node
{
    ElementType Data;
    struct Node *Next;
};

struct QNode
{
    struct Node *rear;  // 指向队尾结点
    struct Node *front; // 指向队头结点
};

// 操作集声明
Queue CreateQueue();
void AddQ(Queue Q, ElementType item);
int IsEmptyQ(Queue Q);
ElementType DeleteQ(Queue Q);

// 操作集
Queue CreateQueue()
{
    Queue q;
    q = (Queue)malloc(sizeof(struct QNode));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int IsEmptyQ(Queue Q)
{
    return (Q->front == NULL);
}

void AddQ(Queue Q, ElementType item)
{
    struct Node *node;
    node = (struct Node *)malloc(sizeof(struct Node));
    node->Data = item;
    node->Next = NULL;

    // 判断队列是否为空
    if (IsEmptyQ(Q))
    {
        Q->front = node;
        Q->rear = node;
    }
    else
    {
        Q->rear->Next = node;
        Q->rear = node;
    }
}

ElementType DeleteQ(Queue Q)
{
    ElementType e;
    struct Node *node;

    // 判断队列是否为空
    if (IsEmptyQ(Q))
    {
        printf("队列空");
        return -1;
    }
    else
    {
        node = Q->front;
        e = node->Data;

        // 然后修改 front 和 rear
        if (Q->front == Q->rear)
            Q->front = Q->rear = NULL;
        else
            Q->front = Q->front->Next;

        free(node);
        return e;
    }
}

// 主函数
int main()
{
    Queue Q;
    Q = CreateQueue();

    printf("入队 5\n");
    AddQ(Q, 5);

    printf("入队 4\n");
    AddQ(Q, 4);

    printf("入队 3\n");
    AddQ(Q, 3);

    printf("出队 %d\n", DeleteQ(Q));
    printf("出队 %d\n", DeleteQ(Q));
    printf("出队 %d\n", DeleteQ(Q));
    printf("%d\n", DeleteQ(Q));
    return 0;
}