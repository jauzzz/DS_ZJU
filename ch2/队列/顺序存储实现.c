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

// 这个结构的队列，有一个问题，因为最大尺寸是确定的;
// 然后出队列的时候，仅仅修改队列头部的坐标，而不移动队列，所以会出现队列满而实际空间未满的情况
// 为了避免这种情况，可以使用循环队列

// 操作集
Queue CreateQueue(int MaxSize)
{
    Queue q;
    q = (Queue)malloc(sizeof(struct QNode));
    q->front = -1;
    q->rear = MAXSIZE;
    return q;
}

int IsFullQ(Queue Q, int MaxSize)
{
    return (Q->rear == MAXSIZE);
}

int IsEmptyQ(Queue Q)
{
    return (Q->front == -1);
}

void AddQ(Queue Q, ElementType item)
{
    // 判断是否还能加
    if (IsFullQ(Q, MAXSIZE))
        printf("队列已满");

    Q->rear++;
    Q->Data[Q->rear] = item;
}

ElementType DeleteQ(Queue Q)
{
    ElementType ele;

    if (IsEmptyQ(Q))
        printf("队列已空");

    ele = Q->Data[Q->rear];
    Q->rear--;
}