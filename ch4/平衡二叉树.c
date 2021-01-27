#include <stdio.h>

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef AVLTree Position;

struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

// 操作集声明
AVLTree CreatATree(ElementType val);
AVLTree Find(ElementType X, AVLTree A);
AVLTree FindMin(AVLTree A);

int Max(int a, int b);
int GetHeight(AVLTree A);
AVLTree LLRotation(AVLTree A); // 左单旋
AVLTree RRRotation(AVLTree A); // 右单旋
AVLTree LRRotation(AVLTree A); // 左右单旋
AVLTree RLRotation(AVLTree A); // 右左单旋

int GetTreeBalanceFactor(AVLTree A);          // 树的平衡因子
AVLTree BalanceTree(AVLTree A);               // 平衡化树
AVLTree Insert(ElementType value, AVLTree A); // 插入节点，并保持平衡
AVLTree Delete(ElementType value, AVLTree A); // 删除节点，并保持平衡

// 操作集实现
AVLTree CreatAVLTree(ElementType val)
{
    AVLTree T;

    T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->Data = val;
    T->Left = NULL;
    T->Right = NULL;

    return T;
}

AVLTree Find(ElementType X, AVLTree A)
{
    if (!A)
        return NULL;

    if (X > A->Data)
        return Find(X, A->Right);
    else if (X < A->Data)
        return Find(X, A->Left);
    else
        return A;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
    int HL, HR;
    if (A)
    {
        HL = GetHeight(A->Left);
        HR = GetHeight(A->Right);
        A->Height = Max(HL, HR) + 1;
    }
    else
        return 0;

    return A->Height;
}

AVLTree LLRotation(AVLTree A)
{
    AVLTree B = A;
    A->Left = B->Right;
    B->Right = A;
    A->Height = GetHeight(A);
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

AVLTree RRRotation(AVLTree A)
{
    AVLTree B = A;
    A->Right = B->Left;
    B->Left = A;
    A->Height = GetHeight(A);
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;

    return B;
}

AVLTree LRRotation(AVLTree A)
{
    A->Left = RRRotation(A->Left);
    return LLRotation(A);
}

AVLTree RLRotation(AVLTree A)
{
    A->Right = LLRotation(A->Right);
    return RRRotation(A);
}

int GetTreeBalanceFactor(AVLTree A)
{
    if (!A)
        return 0;
    else
        return (A->Left->Height - A->Right->Height);
}

AVLTree BalanceTree(AVLTree A)
{
    // 先判断是否平衡
    int factor = GetTreeBalanceFactor(A);

    // 然后看是做什么平衡操作
    if (factor > 1 && GetTreeBalanceFactor(A->Left) > 0)
        return LLRotation(A);
    else if (factor > 1 && GetTreeBalanceFactor(A->Left) < 0)
        return LRRotation(A);
    else if (factor < -1 && GetTreeBalanceFactor(A->Right) > 0)
        return RRRotation(A);
    else if (factor < -1 && GetTreeBalanceFactor(A->Right) < 0)
        return RLRotation(A);
    else
        return A;
}

AVLTree Insert(ElementType value, AVLTree A)
{
    if (!A)
        A = CreatAVLTree(value);

    if (value > A->Data)
    {
        A->Right = Insert(value, A->Right);
        A = BalanceTree(A);
    }
    else if (value < A->Data)
    {
        A->Left = Insert(value, A->Left);
        A = BalanceTree(A);
    }

    return A;
}

AVLTree Delete(ElementType value, AVLTree A)
{
    Position p;

    if (!A)
        printf("未找到要删除的节点.");

    if (value > A->Data)
        A->Right = Delete(value, A->Right);
    else if (value < A->Data)
        A->Left = Delete(value, A->Left);
    else
    {
        if (A->Left && A->Right)
        {
            // 找左子树最大或右子树最小
            p = FindMin(A->Right);
            A->Data = p->Data;
            A->Right = Delete(A->Data, A->Right);
        }
        else
        {
            p = A;
            // 只有左子树
            if (!A->Right)
                A = A->Left;
            // 只有右子树
            else if (!A->Left)
                A = A->Right;

            free(p);
        }
    }

    A = BalanceTree(A);
    return A;
}