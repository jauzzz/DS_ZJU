#include <stdio.h>
#include <stdlib.h>

// 链表结构体定义
typedef int ElementType;
typedef struct LNode *List;

struct LNode
{
    ElementType Data;
    List Next;
};

// 操作集声明
void PrintL(List L);
List MakeEmpty();
List Append(ElementType K, List L);
List Reversed(ElementType K, List L);

// 操作集
void PrintL(List L)
{
    while (L)
    {
        printf("%d ", L->Data);
        L = L->Next;
    }

    printf("NULL");
}

List MakeEmpty()
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L = NULL;
    return L;
}

List Append(ElementType K, List L)
{
    List node, L1;
    L1 = L;

    // 表头
    node = (List)malloc(sizeof(struct LNode));
    node->Data = K;
    node->Next = NULL;

    if (L1 == NULL)
    {
        return node;
    }
    else
    {
        // 找到最尾元素
        while (L1->Next)
        {
            L1 = L1->Next;
        }

        L1->Next = node;
        return L;
    }
}

int CanReverse(ElementType K, List *tail)
{
    // L: 某个链表节点指针，确定后面是否还有 K 个元素
    ElementType i;
    i = 0;

    List *temp;
    temp = tail;

    while (*temp && i < K)
    {
        *temp = (*temp)->Next;
        i++;
    }

    // tail 的值要往后推进 K
    tail = temp;

    return (i >= K);
}

List Reverse(ElementType K, List *head, List *tail)
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L = NULL;

    while (*head && *head != *tail)
    {
        // 反转过程
        List node = (List)malloc(sizeof(struct LNode));
        if (L == NULL)
        {
            node->Data = (*head)->Data;
            node->Next = NULL;
        }
        else
        {
            node->Data = (*head)->Data;
            node->Next = L;
        }

        L = node;
        *head = (*head)->Next;
    }

    // head 也要往后推移到 tail 的位置
    head = tail;

    // L 是表头
    return L;
}

void Attach(List *R, List L)
{
    List temp;
    temp = *R;

    if (temp == NULL)
        *R = L;
    else
    {
        while (temp->Next)
        {
            temp = temp->Next;
        }

        temp->Next = L;
    }
}

List Reversed(ElementType K, List L)
{
    // 每 K 反转，不足 K 保留原样
    //  1. 确定是否反转
    //  2. 反转/保留

    List head = L;
    List tail = L;

    List S, R, cur;
    cur = R = (List)malloc(sizeof(struct LNode));
    R = NULL;

    while (CanReverse(K, &tail))
    {
        printf("\n可以遍历\n");
        S = Reverse(K, &head, &tail);
        Attach(&R, S);
    }

    Attach(&R, head);

    return R;
}

// 主函数
int main()
{
    List L, R;

    L = MakeEmpty();
    L = Append(4, L);
    L = Append(1, L);
    L = Append(6, L);
    L = Append(3, L);
    L = Append(5, L);
    L = Append(2, L);
    PrintL(L);

    int K = 5;
    R = Reversed(K, L);
    PrintL(R);

    return 0;
}