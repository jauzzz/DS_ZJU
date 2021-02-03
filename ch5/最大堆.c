/*
    堆：优先队列（并不是队列），取出数据的顺序是依照元素的优先级大小，而不是进入队列先后顺序

    对于优先队列来说，操作有两个：
    - 入队（没有特殊要求）
    - 出队，出队时要保证出的是最高优先级的元素

    那么，如何组织优先队列？
    - 一般的数组、链表？
    - 有序的数组或链表？
    - 二叉搜索树？AVL树？

    对于数组来说：
        插入（入队）-- 元素总是插入尾部，加上数组随机读写的特性，复杂度为 O(1)
        删除（出队）-- 首先需要找到最大值/最小值，复杂度为 O(N)                     
                     删除后需要移动元素，复杂度为 O(N)

    对于链表来说：
        插入（入队）-- 元素总是插在头部，复杂度为 O(1)
        删除（出队）-- 首先需要找到最大值/最小值，复杂度为 O(N)
                     删除节点，复杂度为 O(1)

    对于有序数组来说：
        插入（入队）-- 插入要找到它对应的位置，用二分查找，复杂度为 O(logN)
                     同样因为有序，插之前，要先移动元素，复杂度为 O(N)
        删除（出队）-- 删除最后一个元素，复杂度为 O(1)

    对于有序链表来说：
        插入（入队）-- 插入要找到它对应的位置，不能用二分查找，只能遍历，复杂度为 O(N)
                     插入元素复杂度为 O(1)
        删除（出队）-- 删除第一个元素，复杂度为 O(1)

    对于二叉搜索树来说：
        插入（入队）-- 插入要找到它对应的位置，复杂度为 O(logN)
                     插入元素复杂度为 O(1)
        删除（出队）-- 删除也要找到它对应的位置，复杂度为 O(logN)
                     但搜索树容易存在一个问题：由于是优先队列，总是先出比较大/小的，容易造成一侧的子树空，导致左右子树的不平衡，而不平衡就会影响查找效率

    对于 AVL树 来说：
        插入（入队）-- 插入要找到它对应的位置，复杂度为 O(logN)
                     插入元素复杂度为 O(1)
                     可能为了平衡，要做旋转操作
        删除（出队）-- 删除也要找到它对应的位置，复杂度为 O(logN)
                     可能为了平衡，要做旋转操作

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxData 10000
#define MaxSize 12
#define ERROR -1

typedef int ElementType;
typedef struct HNode *MaxHeap;

struct HNode
{
    ElementType *Elements;
    int Size;     // 堆的当前元素个数
    int Capacity; // 堆的最大容量
};

// 操作集声明
MaxHeap Create(int maxsize);
bool IsFull(MaxHeap H);
bool IsEmpty(MaxHeap H);
void Insert(ElementType item, MaxHeap H);
ElementType DeleteMax(MaxHeap H);

void PrintHeap(MaxHeap);
void adjust(int i, MaxHeap H);
MaxHeap BuildMaxHeap(int *array); // 从序列建立堆

// 操作集实现
MaxHeap Create(int maxsize)
{
    MaxHeap H;
    H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Elements = malloc((maxsize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = maxsize;
    // 定义一个哨兵，赋值给第一个元素
    H->Elements[0] = MaxData;

    return H;
}

bool IsFull(MaxHeap H)
{
    return H->Size == H->Capacity;
}

bool IsEmpty(MaxHeap H)
{
    return H->Size == 0;
}

void Insert(ElementType item, MaxHeap H)
{
    if (IsFull(H))
    {
        printf("堆已满");
        return;
    }

    int i;
    i = ++H->Size;
    for (; H->Elements[i / 2] < item; i /= 2)
        H->Elements[i] = H->Elements[i / 2];

    H->Elements[i] = item;
}

ElementType DeleteMax(MaxHeap H)
{
    if (IsEmpty(H))
    {
        printf("堆已空");
        return ERROR;
    }

    int parent, child;
    ElementType max, temp;

    max = H->Elements[1];          // 最大值
    temp = H->Elements[H->Size--]; // 完全二叉树最后一个值

    adjust(1, H);
    return max;
}

// 从序列建堆，有两种方式：
//  1. 建立一个空堆，对序列的每一个值执行插入操作，时间复杂度为 O(NlogN)
//  2. 顺序存入，先满足完全二叉树特征，然后进行结点位置的调整
void adjust(int i, MaxHeap H)
{
    ElementType temp;
    int parent, child;

    temp = H->Elements[i];
    for (parent = i; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        // 看跟左子树比还是跟右子树比，那就需要确认，左节点大还是右节点大
        if ((child != H->Size) && (H->Elements[child] < H->Elements[child + 1]))
            child++;

        if (H->Elements[child] < temp)
            // 已经满足堆特性了，就停止
            break;
        else
            // 比右子树小，那交换值，继续比较当前值和剩下的左右子树
            H->Elements[parent] = H->Elements[child];
    }

    H->Elements[parent] = temp;
}

void PrintHeap(MaxHeap H)
{
    for (int i = 0; i < H->Size; i++)
        printf("%d ", H->Elements[i + 1]);
}

MaxHeap BuildMaxHeap(int array[])
{
    MaxHeap H;
    H = Create(MaxSize);

    // 先存入，满足完全二叉树
    int i, j;
    for (i = 0; i < MaxSize; i++)
        H->Elements[++H->Size] = array[i];

    // 进行调整
    for (j = H->Size / 2; j > 0; j--)
        adjust(j, H);

    return H;
}

int main()
{

    int array[MaxSize] = {79, 66, 43, 83, 72, 87, 38, 55, 91, 30, 49, 9};

    MaxHeap H;
    H = BuildMaxHeap(array);
    PrintHeap(H);
}