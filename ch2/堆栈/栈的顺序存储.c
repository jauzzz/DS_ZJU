/*
类型名称: 堆栈（Stack）

数据对象集：一个有0个或多个元素的有穷线性表。

操作集：长度为 MaxSize 的堆栈S ∈ Stack，堆栈元素item ∈ ElementType
    1、Stack CreateStack()： 生成空堆栈，其最大长度为MaxSize；
    2、int IsFull( Stack S, int MaxSize )：判断堆栈S是否已满；
    3、void Push( Stack S, ElementType item )：将元素item压入堆栈；
    4、int IsEmpty ( Stack S )：判断堆栈S是否为空；
    5、ElementType Pop( Stack S )：删除并返回栈顶元素；
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

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
        printf("栈已满");
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
        printf("栈已空");
        return -1;
    }

    return S->Data[S->TOP--];
}

// 主函数
int main()
{
    Stack S;
    S = CreateStack();

    printf("5 入栈\n");
    Push(S, 5);

    printf("7 入栈\n");
    Push(S, 7);

    printf("66 入栈\n");
    Push(S, 66);

    printf("%d出栈\n", Pop(S));
    printf("%d出栈\n", Pop(S));
    return 0;
}