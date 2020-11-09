/*
类型名称：线性表（利用数组的连续存储空间顺序存放线性表的各元素）

数据对象集：线性表是 n 个元素构成的有序序列(a1, a2, a3, ..., an)

操作集：
    List MakeEmpty(): 初始化一个空线性表 L
    ElementType FindKth(int K, List L): 根据位序k，返回相应元素
    int Find(ElementType X, List L): 在线性表 L 中查找 X 出现的第一个位置
    void Insert(ElementType X, int i, List L): 在位序 i 前插入一个新元素 X
    void Delete(int i, List L): 删除指定位序 i 的元素
    int Length(List L): 返回线性表 L 的长度 n
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElementType;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    int Last;
};

// 操作集声明
List MakeEmpty();
ElementType FindKth(int K, List L);
int Find(ElementType X, List L);
void Insert(ElementType X, int i, List L);
void Delete(int i, List L);
int Length(List L);

// 操作集
List MakeEmpty()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL->Last = -1;
    return PtrL;
}

ElementType FindKth(int K, List L)
{
    return L->Data[K];
}

int Find(ElementType X, List L)
{
    int i;
    for (i = 0; i < L->Last; i++)
    {
        if (L->Data[i] == X)
            return i;
    }

    return -1;
}

void Insert(ElementType X, int i, List L)
{
    int j;

    if ((L->Last + 1) > MAXSIZE)
    {
        printf("没有可插入空间");
        return;
    }

    if (i < 0 || i > L->Last + 1)
    {
        printf("不合法的索引值");
        return;
    }

    // 正式插入
    for (j = L->Last; j >= i; j--)
    {
        L->Data[j + 1] = L->Data[j];
    }

    L->Data[i] = X;
    L->Last++;

    return;
}

void Delete(int i, List L)
{
    int j;

    if (i < 0 || i > L->Last)
    {
        printf("不合法的索引值");
        return;
    }

    // 正式删除
    for (j = i; j <= L->Last; j++)
    {
        L->Data[j] = L->Data[j + 1];
    }

    L->Last--;

    return;
}

int Length(List L)
{
    return L->Last + 1;
}

// 主函数
int main()
{
    int i;
    List L;
    L = MakeEmpty();

    Insert(11, 0, L);
    printf("在线性表 L-Data[0]插入 11\n");

    Insert(25, 0, L);
    printf("在线性表 L-Data[0]插入 25\n");

    Insert(33, 0, L);
    printf("在线性表 L-Data[0]插入 33\n");

    Insert(77, 0, L);
    printf("在线性表 L-Data[0]插入 77\n");

    printf("此时的线性表为：");
    for (i = 0; i < Length(L); i++)
        printf("%d ", L->Data[i]);
    printf("\n");

    printf("查找值为 12 的下标是：%d\n", Find(12, L));
    printf("下标为 3 的线性表的值是：%d\n", FindKth(3, L));

    Delete(2, L);
    printf("删除线性表中下标为 2 的元素\n");
    Delete(2, L);
    printf("删除线性表中下标为 2 的元素\n");
    printf("此时的线性表为：");
    for (i = 0; i < Length(L); i++)
        printf("%d ", L->Data[i]);
    printf("\n");

    return 0;
}