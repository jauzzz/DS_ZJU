/* 
    静态链表：用数组来表示链表的一种方式

    任意一个数据结构，都有两种物理存储方式：
    - 顺序存储
    - 链式存储

    静态链表，就是用链表数据结构的顺序存储方式，来描述单链表，又称游标实现法。

    对于静态链表，我们对数组的第一个和最后一个这两个元素，看作是特殊的元素对待：
    - 第一个元素，没有 Data 域，Pointer 指向下一个可用的数组元素
    - 最后一个元素，没有 Data 域，Pointer 指向第一个有值的元素，相当于链表的头结点的作用

    静态链表操作集（跟单链表没啥区别）：
    - InitList
    - Add
    - Append
    - Insert
    - Remove
    - Delete
    - Find
    - FindKth
    - PrintL
*/

#include <stdio.h>

#define MAXSIZE 10
#define OK 1
#define ERROR 0
#define NOCUR -1

typedef int Status;
typedef int ElementType;
typedef int Cursor;
typedef struct SNode *Component;

struct SNode
{
    ElementType data;
    Cursor cur;
};
typedef struct SNode StaticLinkList[MAXSIZE];

// 操作集声明
Status initList(StaticLinkList list);
Cursor Malloc(StaticLinkList list);
Cursor Free(Cursor i, StaticLinkList list);
Status Insert(Cursor i, ElementType data, StaticLinkList list);
Status Delete(Cursor i, StaticLinkList list);
void PrintL(StaticLinkList list);

// 操作集实现
Status initList(StaticLinkList list)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        list[i].cur = i + 1;

    list[MAXSIZE - 1].cur = 0;

    return OK;
}

Cursor Malloc(StaticLinkList list)
{
    Cursor cur;
    cur = list[0].cur; // 默认是 1

    // 这里要判断下是否超过链表长度
    if (cur < 1 || cur >= MAXSIZE)
        return NOCUR;

    list[0].cur = list[cur].cur; // 指向要使用的元素的下一个cur
    return cur;
}

Cursor Free(Cursor i, StaticLinkList list)
{
    // 如何释放一个节点：
    //  1. 让当前节点指向下一个可用节点
    //  2. 更改 list[0] 的可用节点为当前节点
    list[i].cur = list[0].cur;
    list[0].cur = i;
    return OK;
}

Status Insert(Cursor i, ElementType data, StaticLinkList list)
{
    Cursor cur;
    cur = Malloc(list);

    if (cur != NOCUR)
    {
        // data 赋值
        list[cur].data = data;
        // cur 赋值：如果没有后面的元素就是 0，否则就是指向第 i 个元素（list[i-1].cur）
        Cursor j;
        j = MAXSIZE - 1;

        int k;
        for (k = 1; k < i; k++)
            j = list[j].cur;

        // 所以第 i-1 个元素就是 list[j]
        list[cur].cur = list[j].cur;
        list[j].cur = cur;

        return OK;
    }

    return ERROR;
}

Status Delete(Cursor i, StaticLinkList list)
{
    // 删除一个节点有什么操作？
    //  1. 前置节点 指向 后驱节点
    //  2. free(当前节点)
    Cursor pre;
    pre = MAXSIZE - 1;

    int k;
    for (k = 1; pre != 0 && k < i; k++)
        pre = list[pre].cur;

    // pre=0，表明是空链表或者找不到
    if (pre == 0)
    {
        printf("删除失败");
        return ERROR;
    }

    // 到这里，说明 pre 节点存在并找到了
    Cursor j;
    j = list[pre].cur;
    // 让前置结点 指向 后驱节点
    list[pre].cur = list[j].cur;

    // 第二步：free 当前节点
    Free(j, list);

    return ERROR;
}

void PrintL(StaticLinkList list)
{
    Cursor cur;
    cur = list[MAXSIZE - 1].cur;

    // 当 cur=0 时，表明没有下一个元素
    while (cur)
    {
        printf("%2d ", list[cur].data);
        // 指向下一个元素
        cur = list[cur].cur;
    }

    printf("\n");
}

// 测试函数
void MallocTest()
{
    printf("\n    --- MallocTest --- \n");

    StaticLinkList list;
    initList(list);

    Cursor cur;
    printf("备用链表起始下标为: %d\n", list[0].cur);
    cur = Malloc(list);
    printf("分配的元素下标为: %d，新的备用链表起始下标为: %d\n\n", cur, list[0].cur);

    printf("备用链表起始下标为: %d\n", list[0].cur);
    cur = Malloc(list);
    printf("分配的元素下标为: %d，新的备用链表起始下标为: %d\n\n", cur, list[0].cur);

    printf("备用链表起始下标为: %d\n", list[0].cur);
    cur = Malloc(list);
    printf("分配的元素下标为: %d，新的备用链表起始下标为: %d\n\n", cur, list[0].cur);

    printf("    --- MallocTest --- \n");
}

void InsertTest()
{
    printf("\n    --- InsertTest --- \n");

    StaticLinkList list;
    initList(list);

    Insert(1, 11, list);
    Insert(2, 12, list);
    Insert(2, 13, list);
    PrintL(list);

    printf("    --- InsertTest --- \n");
}

void DeleteTest()
{
    printf("\n    --- DeleteTest --- \n");

    StaticLinkList list;
    initList(list);

    Insert(1, 11, list);
    Insert(2, 12, list);
    Insert(2, 13, list);
    PrintL(list);

    Delete(2, list);
    PrintL(list);

    Insert(2, 14, list);
    Insert(2, 15, list);
    PrintL(list);

    Delete(3, list);
    PrintL(list);

    printf("    --- DeleteTest --- \n");
}

// 主函数
int main()
{
    StaticLinkList list;

    printf("初始化静态链表\n");
    initList(list);

    printf("\n打印空的静态链表");
    PrintL(list);
    printf("打印完成\n");

    // 测试流程
    MallocTest();
    InsertTest();
    DeleteTest();
}