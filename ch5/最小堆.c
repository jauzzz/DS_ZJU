#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MinData -10000
#define MaxSize 12
#define ERROR -1

typedef int ElementType;
typedef struct HNode *MinHeap;

struct HNode
{
    ElementType *Elements;
    int Size;     // 堆的当前元素个数
    int Capacity; // 堆的最大容量
};

// 操作集声明
MinHeap Create(int maxsize);
bool IsFull(MinHeap H);
bool IsEmpty(MinHeap H);
void Insert(ElementType item, MinHeap H);
ElementType DeleteMin(MinHeap H);

void PrintHeap(MinHeap);
void adjust(int i, MinHeap H);
MinHeap BuildMinHeap(int *array); // 从序列建立堆

// 操作集实现
MinHeap Create(int maxsize)
{
    MinHeap H;
    H = (MinHeap)malloc(sizeof(struct HNode));
    H->Elements = malloc((maxsize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = maxsize;
    // 定义一个哨兵，赋值给第一个元素
    H->Elements[0] = MinData;

    return H;
}

bool IsFull(MinHeap H)
{
    return H->Size == H->Capacity;
}

bool IsEmpty(MinHeap H)
{
    return H->Size == 0;
}

void Insert(ElementType item, MinHeap H)
{
    if (IsFull(H))
    {
        printf("堆已满");
        return;
    }

    int i;
    i = ++H->Size;
    for (; H->Elements[i / 2] > item; i /= 2)
        H->Elements[i] = H->Elements[i / 2];

    H->Elements[i] = item;
}

ElementType DeleteMin(MinHeap H)
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
void adjust(int i, MinHeap H)
{
    ElementType temp;
    int parent, child;

    temp = H->Elements[i];
    for (parent = i; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        // 看跟左子树比还是跟右子树比，那就需要确认，左节点大还是右节点大
        if ((child != H->Size) && (H->Elements[child] > H->Elements[child + 1]))
            child++;

        if (H->Elements[child] > temp)
            // 已经满足堆特性了，就停止
            break;
        else
            // 比子树小，那交换值，继续比较当前值和剩下的左右子树
            H->Elements[parent] = H->Elements[child];
    }

    H->Elements[parent] = temp;
}

void PrintHeap(MinHeap H)
{
    for (int i = 0; i < H->Size; i++)
        printf("%d ", H->Elements[i + 1]);
}

MinHeap BuildMinHeap(int array[])
{
    MinHeap H;
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

    MinHeap H;
    H = BuildMinHeap(array);
    PrintHeap(H);
}