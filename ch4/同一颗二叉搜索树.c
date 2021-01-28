/*
    题目：
        给定一个插入序列就可以唯一确定一颗二叉搜索树；
        然而，一颗二叉搜索树可以由多种不同的插入序列得到。
        那么，对于输入的各种序列，你需要判断它们是否能生成一样的二叉搜索树？
    
    输入示例：
        4 2
        3 1 4 2
        3 4 1 2
        3 2 4 1
        2 1
        2 1
        1 2
        0

    输出示例：
        Yes
        No
        No

    解题思路：
        1. 建两棵树，比较树是否一致
        2. 不建树，按二叉搜索树的规则排列序列，比较两个序列是否一致
        3. 建一棵树，看另一序列是否一致
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ELementType;
typedef struct TreeNode *Tree;
typedef struct TreeNode *Position;

struct TreeNode
{
    ELementType Data;
    Tree Left;
    Tree Right;
    int flag;
};

// 操作集声明
Tree CreatBstTree(ELementType val);
Position Find(ELementType X, Tree BST);
Position FindMin(Tree BST);
Position FindMax(Tree BST);
Position Insert(ELementType X, Tree BST);
Position Delete(ELementType X, Tree BST);

// 操作实现
Tree CreatBstTree(ELementType val)
{
    Tree T;

    T = (Tree)malloc(sizeof(struct TreeNode));
    T->Data = val;
    T->Left = NULL;
    T->Right = NULL;
    T->flag = 0;

    return T;
}

Position Find(ELementType X, Tree BST)
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

Position FindMin(Tree BST)
{
    if (!BST)
        return NULL;

    if (!BST->Left)
        return BST;
    else
    {
        return FindMin(BST->Left);
    }
}

Position FindMax(Tree BST)
{
    if (!BST)
        return NULL;

    if (!BST->Right)
        return BST;
    else
    {
        return FindMax(BST->Right);
    }
}

Position Insert(ELementType X, Tree BST)
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

Position Delete(ELementType X, Tree BST)
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

void PreOrderTraversal(Tree BT)
{
    // 根左右
    if (BT)
    {
        printf("%5d", BT->Data);      // 打印根
        PreOrderTraversal(BT->Left);  // 进入左子树
        PreOrderTraversal(BT->Right); // 进入右子树
    }
}

void InOrderTraversal(Tree BT)
{
    // 左根右
    if (BT)
    {
        InOrderTraversal(BT->Left);  // 进入左子树
        printf("%5d", BT->Data);     // 打印根
        InOrderTraversal(BT->Right); // 进入右子树
    }
}

void PostOrderTraversal(Tree BT)
{
    // 左右根
    if (BT)
    {
        PostOrderTraversal(BT->Left);  // 进入左子树
        PostOrderTraversal(BT->Right); // 进入右子树
        printf("%5d", BT->Data);       // 打印根
    }
}

// 以上是二叉搜索树的相关操作集
Tree MakeTree(int N)
{
    int val;
    Tree T;

    // 先拿根，然后建树
    scanf("%d", &val);
    T = CreatBstTree(val);
    T->flag = 0;

    // 将其他的值插入
    for (int i = 0; i < N - 1; i++)
    {
        scanf("%d", &val);
        T = Insert(val, T);
    }

    // 把树遍历一下，看看树的样子
    // printf("\n先序遍历:\n");
    // PreOrderTraversal(T);

    // printf("\n中序遍历:\n");
    // InOrderTraversal(T);
    // printf("\n");

    return T;
}

void FreeTree(Tree T)
{
    if (T)
    {
        FreeTree(T->Left);
        FreeTree(T->Right);
        free(T);
    }
}

void ResetTree(Tree T)
{
    if (T)
    {
        ResetTree(T->Left);
        ResetTree(T->Right);
        T->flag = 0;
    }
}

int check(Tree T, int val)
{
    if (T->flag)
    { //flag 不等于 0 的情况
        if (val < T->Data)
            return check(T->Left, val);
        else if (val > T->Data)
            return check(T->Right, val);
        else
            return 0;
    }
    else
    { // T->flag = 0 的情况
        if (val == T->Data)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}

int judge(Tree T, int N)
{
    int val, flag;
    flag = 1;
    scanf("%d", &val);

    // 先判断根节点是否一致
    if (val != T->Data)
        flag = 0;
    else
        T->flag = 1;

    // 进入下一步判断
    for (int i = 0; i < N - 1; i++)
    {
        scanf("%d", &val);
        if (flag && check(T, val))
            flag = 1;
        else
            flag = 0;
    }

    return flag;
}

int main()
{
    // 对每组数据：
    //  1. 读入 N 和 L
    //  2. 根据第一行序列建树 T
    //  3. 依据树 T 判断后面的 L 个序列与 T 是否是同一个二叉搜索树

    int N, L;
    Tree T;

    // N: 序列的长度，L 要判断的序列个数
    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        // 建树
        T = MakeTree(N);
        // 判断 L 个序列是否相同
        for (int i = 0; i < L; i++)
        {
            if (judge(T, N))
                printf("YES\n");
            else
                printf("NO\n");

            ResetTree(T);
        }

        // 销毁树
        FreeTree(T);
        // 进入下一组树的判别
        scanf("%d", &N);
    }

    return 0;
}