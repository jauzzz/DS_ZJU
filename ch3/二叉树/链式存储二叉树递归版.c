#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef int ElementType;
typedef struct TreeNode *BinTree;
typedef struct QNode *Queue;

struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

struct Node
{
    BinTree Data;
    struct Node *Next;
};

struct QNode
{
    struct Node *rear;  // 指向队尾结点
    struct Node *front; // 指向队头结点
};

// 操作集声明
BinTree CreatBinTree(ElementType val);
void Insert(BinTree T, ElementType val, int type);

Queue CreateQueue();
void AddQ(Queue Q, BinTree item);
int IsEmptyQ(Queue Q);
BinTree DeleteQ(Queue Q);

// 遍历
void PreOrderTraversal(BinTree BT);   //前序遍历
void InOrderTraversal(BinTree BT);    //中序遍历
void PostOrderTraversal(BinTree BT);  //后序遍历
void LevelOrderTraversal(BinTree BT); //层次遍历

// 操作集实现
BinTree CreatBinTree(ElementType val)
{
    BinTree T;

    T = (BinTree)malloc(sizeof(struct TreeNode));
    T->Data = val;
    T->Left = NULL;
    T->Right = NULL;

    return T;
}

BinTree CreateTestTree()
{
    BinTree T;

    T = CreatBinTree(1);
    T->Left = CreatBinTree(2);
    T->Right = CreatBinTree(3);
    T->Left->Left = CreatBinTree(4);
    T->Left->Right = CreatBinTree(6);
    T->Left->Right->Left = CreatBinTree(5);
    T->Right->Left = CreatBinTree(7);
    T->Right->Right = CreatBinTree(9);
    T->Right->Left->Right = CreatBinTree(8);
    return T;
}

void PreOrderTraversal(BinTree BT)
{
    // 根左右
    if (BT)
    {
        printf("%5d", BT->Data);       // 打印根
        PreOrderTraversal(BT->Left);  // 进入左子树
        PreOrderTraversal(BT->Right); // 进入右子树
    }
}

void InOrderTraversal(BinTree BT)
{
    // 左根右
    if (BT)
    {
        InOrderTraversal(BT->Left);  // 进入左子树
        printf("%5d", BT->Data);       // 打印根
        InOrderTraversal(BT->Right); // 进入右子树
    }
}

void PostOrderTraversal(BinTree BT)
{
    // 左右根
    if (BT)
    {
        PostOrderTraversal(BT->Left);  // 进入左子树
        PostOrderTraversal(BT->Right); // 进入右子树
        printf("%5d", BT->Data);       // 打印根
    }
}

// 层次遍历，需要借助队列来实现
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

void AddQ(Queue Q, BinTree item)
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

BinTree DeleteQ(Queue Q)
{
    BinTree e;
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

void LevelOrderTraversal(BinTree BT)
{
    Queue Q;
    Q = CreateQueue();
    BinTree item;

    AddQ(Q, BT);

    while (!IsEmptyQ(Q))
    {
        item = DeleteQ(Q);
        printf("%5d", item->Data);

        if (item->Left)
            AddQ(Q, item->Left);
        if (item->Right)
            AddQ(Q, item->Right);
    }
}

// 主函数
int main()
{
    BinTree T;

    T = CreateTestTree();

    printf("先序遍历\n");
    PreOrderTraversal(T);
    printf("\n");

    printf("中序遍历\n");
    InOrderTraversal(T);
    printf("\n");

    printf("后序遍历\n");
    PostOrderTraversal(T);
    printf("\n");

    printf("层次遍历\n");
    LevelOrderTraversal(T);
    printf("\n");

    return 0;
}