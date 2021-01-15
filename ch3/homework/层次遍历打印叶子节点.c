// https://pintia.cn/problem-sets/1302953266564911104/problems/1310235296110600193
// 通过输入节点数以及每个节点的左儿子和右儿子，从上到下打印出叶节点

/*
    1. 还原树
    2. 层序遍历
    3. 打印叶节点
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1
#define DEBUG false

typedef struct TreeNode *TNode;
typedef struct QNode *Queue;

struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
} T[MaxTree];

struct Node
{
    TNode Data;
    struct Node *Next;
};

struct QNode
{
    struct Node *rear;  // 指向队尾结点
    struct Node *front; // 指向队头结点
};

// 函数声明
Tree BuildTree(struct TreeNode T[]);
void Traverse(TNode BT);

Queue CreateQueue();
int IsEmptyQ(Queue Q);
void AddQ(Queue Q, TNode item);
TNode DeleteQ(Queue Q);

// 函数实现
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

void AddQ(Queue Q, TNode item)
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

TNode DeleteQ(Queue Q)
{
    TNode e;
    struct Node *node;

    // 判断队列是否为空
    if (IsEmptyQ(Q))
    {
        printf("队列空");
        return NULL;
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

Tree BuildTree(struct TreeNode T[])
{
    // N 是输入的二叉树数据的行数
    int N, root;

    scanf("%d", &N);

    // int check[N];
    int *check;
    check = (int *)calloc(N, sizeof(int));

    // 初始化 check
    for (int i = 0; i < N; i++)
        check[i] = 0;

    if (N)
    {
        char cl, cr;

        for (int i = 0; i < N; i++)
        {
            T[i].Element = i;

            // NOTE: scanf %c 的时候会读取换行符，所以要加个 getchar 预读换行符
            // https://blog.csdn.net/sinat_40043477/article/details/77748944
            getchar();
            scanf("%c %c", &cl, &cr);

            // 处理 cl
            if (cl != '-')
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
            {
                T[i].Left = Null;
            }

            // 处理 cr
            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
            {
                T[i].Right = Null;
            }

            // 调试：打印结果
            if (DEBUG == true)
            {
                printf("\n---- %d -----\n", i);
                printf("%d %d %d\n", T[i].Element, T[i].Left, T[i].Right);
                printf("--------------\n\n");
            }
        }
    }

    // 需要返回根节点是哪个
    int j;
    for (j = 0; j < N; j++)
    {
        if (check[j] == 0)
            break;
    }

    root = j;
    return root;
}

void Traverse(TNode BT)
{
    printf("\ntraverse....\n");

    Queue Q;
    Q = CreateQueue();
    TNode item;

    AddQ(Q, BT);

    while (!IsEmptyQ(Q))
    {
        item = DeleteQ(Q);
        if ((item->Left == Null) && (item->Right == Null))
            printf("%5d", item->Element);

        if (item->Left != Null)
            AddQ(Q, &T[item->Left]);
        if (item->Right != Null)
            AddQ(Q, &T[item->Right]);
    }
}

// 主函数
int main()
{
    Tree R;

    // 获取输入，根据输入重建树 R1、R2
    R = BuildTree(T);

    // 层序遍历，打印叶节点
    Traverse(&T[R]);
}