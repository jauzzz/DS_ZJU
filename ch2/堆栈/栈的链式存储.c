/*
类型名称: 堆栈（Stack）

数据对象集：一个有0个或多个元素的有穷线性表。

操作集：长度为 MaxSize 的堆栈S ∈ Stack，堆栈元素item ∈ ElementType
    1、Stack CreateStack()： 生成空堆栈，其最大长度为 MaxSize；
    2、int IsEmpty ( Stack S )：判断堆栈S是否为空；
    3、void Push( Stack S, ElementType item )：将元素item压入堆栈；
    4、ElementType Pop( Stack S )：删除并返回栈顶元素；
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct SNode *Stack;

struct SNode
{
    ElementType Data;
    Stack Next;
};

// 操作集声明
Stack CreateStack();
int IsEmpty(Stack S);
void Push(Stack S, ElementType item);
ElementType Pop(Stack S);

// 操作集
Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

int IsEmpty(Stack S)
{
    return (S->Next == NULL);
}

void Push(Stack S, ElementType item)
{
    Stack node;
    node = CreateStack();
    node->Data = item;
    node->Next = S->Next;
    S->Next = node;
}

ElementType Pop(Stack S)
{
    Stack ele;
    ElementType item;

    if (IsEmpty(S))
    {
        printf("堆栈空");
    }

    ele = S->Next;
    S->Next = ele->Next;

    // 要释放
    item = ele->Data;
    free(ele);
    return item;
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

    printf("%d 出栈\n", Pop(S));
    printf("%d 出栈\n", Pop(S));
    return 0;
}