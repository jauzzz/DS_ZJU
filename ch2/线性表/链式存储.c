/*
类型名称：线性表（不要求逻辑上相邻的两个元素物理上也相邻；通过“链”建立起数据元素之间的逻辑关系。）

数据对象集：线性表是 n 个元素构成的有序序列(a1, a2, a3, ..., an)

操作集：
    List MakeEmpty(): 初始化一个空线性表 L
    List FindKth(int K, List L): 根据位序k，返回相应元素
    int Find(ElementType X, List L): 在线性表 L 中查找 X 出现的第一个位置
    List Insert(ElementType X, int i, List L): 在位序 i 前插入一个新元素 X，返回表头
    List Delete(int i, List L): 删除指定位序 i 的元素，返回表头
    int Length(List L): 返回线性表 L 的长度 n
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *List;
typedef int ElementType;

struct LNode
{
    ElementType Data;
    List Next;
};

// 操作集函数声明
List MakeEmpty();
int Length(List L);
int Find(ElementType X, List L);
List FindKth(int K, List L);
List Insert(ElementType X, int i, List L);
List Delete(int i, List L);
void Print(List L);

// 操作集函数实现
List MakeEmpty()
{
    List PtrL;

    PtrL = (List)malloc(sizeof(struct LNode));
    // 初始化为空指针
    // PtrL = NULL;
    PtrL->Data = 0;
    PtrL->Next = NULL;
    return PtrL;
}

int Length(List L)
{
    int i = 0;
    List p = L;

    while (p)
    {
        p = p->Next;
        i++;
    }

    return i;
}

int Find(ElementType X, List L)
{
    int i = 1;
    List p = L;

    while (p && p->Data != X)
    {
        p = p->Next;
        i++;
    }

    // 确定是遍历完了还是找到了
    // 遍历完了 p=NULL，找到了 p 就是那个元素
    if (p == NULL)
        return -1;
    else
        return i;
}

List FindKth(int K, List L)
{
    int i = 1;
    List p = L;

    while (i < K && p)
    {
        p = p->Next;
        i++;
    }

    // 确定是遍历完了还是找到了
    // 遍历完了 p=NULL，找到了 p 就是那个元素
    return p;
}

List Insert(ElementType X, int i, List L)
{
    // 需要区分：表头插入，其他位置插入
    List p, s;

    // 表头插入
    if (i == 1)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = L;
        return s;
    }

    // 其他位置
    p = FindKth(i - 1, L);
    if (p == NULL)
    {
        printf("超出链表范围");
        return NULL;
    }
    else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return L;
    }
}

List Delete(int i, List L)
{
    // 需要区分：表头删除，其他位置删除
    List p, s;

    // 表头删除
    if (i == 1)
    {
        if (L)
        {
            s = L;
            p = L->Next;
            free(s);
        }
        else
        {
            return NULL;
        }

        return p;
    }

    // 其他位置
    p = FindKth(i - 1, L);
    if (p == NULL || p->Next == NULL)
    {
        printf("超出链表范围");
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return L;
    }
}

void Print(List L)
{
    List p = L;

    printf("当前链表为:");
    while (p)
    {
        if (p->Data)
            printf("%d ", p->Data);
        else
            printf("NULL ");

        p = p->Next;
    }

    printf("\n");
}

// 主函数
int main()
{
    List L;
    L = MakeEmpty();
    Print(L);

    L = Insert(11, 1, L);
    Print(L);

    L = Insert(25, 1, L);
    Print(L);

    L = Insert(33, 2, L);
    Print(L);

    L = Insert(77, 3, L);
    Print(L);

    printf("当前链表长度为：%d\n", Length(L));

    printf("此时链表中第二个结点的值是：%d\n", FindKth(2, L)->Data);

    printf("查找 22 是否在该链表中：");
    if (Find(22, L) != -1)
        printf("是！\n");
    else
        printf("否！\n");

    printf("查找 33 是否在该链表中：");
    if (Find(33, L) != -1)
        printf("是！\n");
    else
        printf("否！\n");

    L = Delete(1, L);
    L = Delete(3, L);
    printf("----------删除后-----\n");
    Print(L);

    return 0;
}