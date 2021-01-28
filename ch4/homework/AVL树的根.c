// https://pintia.cn/problem-sets/1302953266564911104/problems/1313023111009525761
// 给定一个序列，返回该序列组成的 AVL 树的根
// 主要就是 AVL 要做平衡操作会影响根的值

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef struct AVLNode *Position;

struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

// 操作集声明
AVLTree CreatAVLTree(ElementType val);
Position Find(ElementType X, AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
AVLTree Insert(ElementType val, AVLTree T);

int Max(int a, int b);
int GetHeight(AVLTree T);
AVLTree LLRotation(AVLTree T);
AVLTree LRRotation(AVLTree T);
AVLTree RRRotation(AVLTree T);
AVLTree RLRotation(AVLTree T);

// 操作集实现
AVLTree CreatAVLTree(ElementType val)
{
    AVLTree T;
    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->Data = val;
    T->Left = NULL;
    T->Right = NULL;
    T->Height = 1;

    return T;
}

Position Find(ElementType X, AVLTree T)
{
    if (!T)
        return NULL;

    if (X > T->Data)
        return Find(X, T->Right);
    else if (X < T->Data)
        return Find(X, T->Left);
    else
        return T;
}

Position FindMin(AVLTree T)
{
    if (!T)
        return NULL;

    if (!T->Left)
        return T;
    else
    {
        return FindMin(T->Left);
    }
}

Position FindMax(AVLTree T)
{
    if (!T)
        return NULL;

    if (!T->Right)
        return T;
    else
    {
        return FindMax(T->Right);
    }
}

AVLTree Insert(ElementType val, AVLTree T)
{
    // 插入的步骤:
    //  1. 确认插入的结点位置（小于往左插，大于往右插）
    //  2. 插入

    if (!T)
        T = CreatAVLTree(val);
    else if (val < T->Data)
    {
        T->Left = Insert(val, T->Left);                      // 插入左子树
        if ((GetHeight(T->Left) - GetHeight(T->Right)) == 2) //需要做 LL 旋转或 LR
        {
            if (val < T->Left->Data) // 新结点插入在 A(Root)的左孩子的左子树中
                T = LLRotation(T);
            else // 新结点插在 A 的左子树的右子树中
                T = LRRotation(T);
        }
    }

    else if (val > T->Data)
    {
        T->Right = Insert(val, T->Right);                    // 插入左子树
        if ((GetHeight(T->Right) - GetHeight(T->Left)) == 2) //需要做 RR 旋转或者 RL
        {
            if (val > T->Right->Data)
                T = RRRotation(T); // 新结点插入在 A(Root)的右孩子 B 的右子树中
            else                   // 新结点插入在 A(Root)的右孩子 B 的左子树中
                T = RLRotation(T);
        }
    }

    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1; // 更新树的高度,左右高度的最大值+1

    return T;
}

// 树的平衡化操作
int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree T)
{
    if (!T)
        return 0;
    else
    {
        T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
        return T->Height;
    }
}

AVLTree LLRotation(AVLTree T)
{
    AVLTree B;
    B = T->Left;
    T->Left = B->Right;
    B->Right = T;
    // 更新高度
    T->Height = GetHeight(T);
    B->Height = Max(GetHeight(B->Left), T->Height) + 1;

    return B;
}

AVLTree LRRotation(AVLTree T)
{
    T->Left = RRRotation(T->Left);
    return LLRotation(T);
}

AVLTree RRRotation(AVLTree T)
{
    AVLTree B;
    B = T->Right;
    T->Right = B->Left;
    B->Left = T;
    // 更新高度
    T->Height = GetHeight(T);
    B->Height = Max(T->Height, GetHeight(B->Right)) + 1;

    return B;
}

AVLTree RLRotation(AVLTree T)
{
    T->Right = LLRotation(T->Right);
    return RRRotation(T);
}

// 主函数
int main()
{
    int N, val;
    AVLTree T;

    // N: 序列的长度，L 要判断的序列个数
    scanf("%d", &N);
    if (N)
    {
        scanf("%d", &val);
        // 建树
        T = CreatAVLTree(val);
        // 判断 L 个序列是否相同
        for (int i = 0; i < N - 1; i++)
        {
            scanf("%d", &val);
            T = Insert(val, T);
        }

        printf("%d\n", T->Data);
    }
    else
        printf("0\n");

    return 0;
}