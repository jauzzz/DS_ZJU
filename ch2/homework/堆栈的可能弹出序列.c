// 相邻数的差不能大于栈最大值
// 后进先出

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

typedef int ElementType;
typedef struct SNode *Stack;

struct SNode
{
    ElementType Data[MAXSIZE];
    int TOP;
};

// 操作集声明
Stack CreateStack();
int IsFull(Stack S, int maxsize);
int IsEmpty(Stack S);
void Push(Stack S, ElementType I);
ElementType Pop(Stack S);

// 操作集
Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->TOP = -1;
    return S;
}

int IsFull(Stack S, int maxsize)
{
    return S->TOP == maxsize - 1;
}

int IsEmpty(Stack S)
{
    return S->TOP == -1;
}

void Push(Stack S, ElementType I)
{
    // 检查栈是否已满
    if (IsFull(S, MAXSIZE))
    {
        printf("栈已满\n");
        return;
    }

    S->TOP++;
    S->Data[S->TOP] = I;
    return;
}

ElementType Pop(Stack S)
{
    // 检查栈是否到底
    if (IsEmpty(S))
    {
        printf("栈已空\n");
        return -1;
    }

    return S->Data[S->TOP--];
}

// 主函数
int check(int l[])
{
    Stack S = CreateStack();

    int temp;
    int j = 1;

    for (int i = 0; i <= 6; i++)
    {
        while (j < l[i])
            // printf("push %d\n", j++);
            Push(S, j++);

        if (j > l[i])
        {
            // printf("pop %d\n", l[i]);
            temp = Pop(S);
            if (temp != l[i])
            {
                printf("ERROR!\n");
                return -1;
            }
        }
        if (j == l[i])
        {
            // printf("push %d\n", j);
            // printf("pop %d\n", j);
            Push(S, j);
            temp = Pop(S);
            if (temp != l[i])
            {
                printf("ERROR!\n");
                return -1;
            }

            j++;
        }
    }

    printf("SUCCESS!\n");
    return 0;
}

int main()
{
    int l1[7] = {1, 2, 3, 4, 5, 6, 7};
    int l2[7] = {3, 2, 1, 7, 5, 6, 4};

    int l3[7] = {7, 6, 5, 4, 3, 2, 1};
    int l4[7] = {5, 6, 4, 3, 7, 2, 1};
    int l5[7] = {1, 7, 6, 5, 4, 3, 2};

    printf("check l1:\n");
    check(l1);
    printf("\n");

    printf("check l2:\n");
    check(l2);
    printf("\n");

    printf("check l3:\n");
    check(l3);
    printf("\n");

    printf("check l4:\n");
    check(l4);
    printf("\n");

    printf("check l5:\n");
    check(l5);
    printf("\n");
}