#include <stdio.h>
#include <stdbool.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];

// 函数声明
Tree BuildTree(struct TreeNode T[]);
bool Isomorphic(Tree R1, Tree R2);

// 函数实现
Tree BuildTree(struct TreeNode T[])
{
    // N 是输入的二叉树数据的行数
    int N, root;

    scanf("%d", &N);

    int check[N];
    // 初始化 check
    for (int i = 0; i < N; i++)
        check[i] = 0;

    if (N)
    {
        char cl, cr;

        for (int i = 0; i < N; i++)
        {
            scanf("%c %c %c", &T[i].Element, &cl, &cr);
            // printf("[%d] %c %c %c\n", i, T[i].Element, cl, cr);

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

bool Isomorphic(Tree R1, Tree R2)
{
    // 同构的概念是什么？
    // 如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的

    // 首先肯定是递归的，然后分析基本情况有哪些:
    //  1. 空
    //  2. 根
    //  3. 是否需要左右互换？根据根的值来判断

    if (R1 == Null && R2 == Null)
        return 1;
    if (R1 == Null || R2 == Null)
        return 0;

    if (T1[R1].Element != T2[R2].Element)
        return 0;

    if ((T1[R1].Left != Null) && (T2[R2].Left != Null) && T1[T1[R1].Left].Element != T2[T2[R2].Left].Element)
        return Isomorphic(T1[R1].Right, T2[R2].Left) && Isomorphic(T1[R1].Left, T2[R2].Right);
    else
        return Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right);
}

// 主函数
// 返回根结点
int main()
{
    Tree R1, R2;

    // 获取输入，根据输入重建树 R1、R2
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);

    // 判断重构
    if (Isomorphic(R1, R2))
        printf("\n同构!\n");
    else
        printf("\n不同构!\n");
}

/*
示例输入数据

8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -

8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
*/