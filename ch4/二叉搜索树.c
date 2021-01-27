#include <stdio.h>

typedef int ELementType;
typedef struct TreeNode *BinTree;
typedef BinTree Position;

struct TreeNode
{
    ELementType Data;
    BinTree Left;
    BinTree Right;
};

// 操作集声明
BinTree CreatBstTree(ELementType val);
Position Find(ELementType X, BinTree BST);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
Position Insert(ELementType X, BinTree BST);
Position Delete(ELementType X, BinTree BST);

// 操作实现
BinTree CreatBstTree(ELementType val)
{
    BinTree T;

    T = (BinTree)malloc(sizeof(struct TreeNode));
    T->Data = val;
    T->Left = NULL;
    T->Right = NULL;

    return T;
}

Position Find(ELementType X, BinTree BST)
{
    if (!BST)
        return NULL;

    if (X > BST->Data)
        return Find(X, BST->Right);
    else if (X < BST->Data)
        return Find(X, BST->Left);
    else
        return BST;
}

Position FindMin(BinTree BST)
{
    if (!BST)
        return NULL;

    if (!BST->Left)
        return BST->Data;
    else
    {
        FindMin(BST->Left);
    }
}

Position FindMax(BinTree BST)
{
    if (!BST)
        return NULL;

    if (!BST->Right)
        return BST->Data;
    else
    {
        FindMax(BST->Right);
    }
}

Position Insert(ELementType X, BinTree BST)
{
    if (!BST)
    {
        BST = CreatBstTree(X);
    }

    if (X > BST->Data)
        BST->Right = Insert(X, BST->Right);
    else if (X < BST->Data)
        BST->Left = Insert(X, BST->Left);

    return BST;
}

Position Delete(ELementType X, BinTree BST)
{
    Position p;

    if (!BST)
        printf("未找到要删除的节点.");

    if (X > BST->Data)
        BST->Right = Delete(X, BST->Right);
    else if (X < BST->Data)
        BST->Left = Delete(X, BST->Left);
    else
    {
        if (BST->Left && BST->Right)
        {
            // 找左子树最大或右子树最小
            p = FindMin(BST->Right);
            BST->Data = p->Data;
            BST->Right = Delete(BST->Data, BST->Right);
        }
        else
        {
            p = BST;
            // 只有左子树
            if (!BST->Right)
                BST = BST->Left;
            // 只有右子树
            else if (!BST->Left)
                BST = BST->Right;

            free(p);
        }
    }

    return BST;
}
