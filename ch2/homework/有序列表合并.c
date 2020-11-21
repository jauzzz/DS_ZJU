/*
    本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
*/

#include <stdio.h>
#include <stdlib.h>

// 结构定义
typedef int ElementType;
typedef struct Node *PtrToNode;

struct Node
{
    ElementType Data; /* 存储结点数据 */
    PtrToNode Next;   /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

// 操作集声明
List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出 NULL */

List Merge(List L1, List L2);

// 操作集实现
List Merge(List L1, List L2)
{
    List L, head, tmp1, tmp2;
    L = (List)malloc(sizeof(struct Node));
    head = L;

    tmp1 = L1->Next;
    tmp2 = L2->Next;

    while (tmp1 && tmp2)
    {
        if (tmp1->Data < tmp2->Data)
        {
            L->Next = tmp1;
            tmp1 = tmp1->Next;
        }
        else
        {
            L->Next = tmp2;
            tmp2 = tmp2->Next;
        }
        L = L->Next;
    }

    // 考虑 L1 或 L2 为空
    if (tmp1)
        L->Next = tmp1;
    if (tmp2)
        L->Next = tmp2;

    // 让 L1、L2 为空列表
    L1->Next = NULL;
    L2->Next = NULL;

    // 最后返回 head
    return head;
}

// 主程序
int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);

    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}
