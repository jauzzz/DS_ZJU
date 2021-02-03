#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ERROR NULL
#define INFINITY -1000
#define MAXSIZE 65

typedef struct HTNode *HuffmanTree;
typedef struct HeapNode *MinHeap;
typedef HuffmanTree ElementType;

struct HeapNode
{
    ElementType *Elements;
    int Size;     // 堆的当前元素个数
    int Capacity; // 堆的最大容量
};

struct HTNode
{
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

HuffmanTree mini;

// 操作集声明
MinHeap CreateMinHeap(int maxsize);
bool IsFull(MinHeap H);
bool IsEmpty(MinHeap H);
void InsertMinHeap(ElementType item, MinHeap H);
ElementType DeleteMin(MinHeap H);
void adjust(int i, MinHeap H);
void PrintHeap(MinHeap H);

HuffmanTree CreateHuffmanTree();
HuffmanTree Huffman(MinHeap H);
int WPL(HuffmanTree HT, int depth);

bool Check(int N, int f[], int wpl);
int Min(int a, int b);
bool IsPrefix(char code[][MAXSIZE], int N);

// 操作集实现
MinHeap CreateMinHeap(int maxsize)
{
    MinHeap H;
    H = (MinHeap)malloc(sizeof(struct HTNode));
    H->Elements = malloc((maxsize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = maxsize;
    // 定义一个哨兵，赋值给第一个元素
    H->Elements[0] = mini;

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

void InsertMinHeap(ElementType item, MinHeap H)
{
    if (IsFull(H))
    {
        printf("堆已满");
        return;
    }

    int i;
    i = ++H->Size;
    for (; H->Elements[i / 2]->Weight > item->Weight; i /= 2)
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
    ElementType min;

    min = H->Elements[1]; // 最大值

    adjust(1, H);
    return min;
}

void adjust(int i, MinHeap H)
{
    ElementType temp;
    int parent, child;

    temp = H->Elements[H->Size--];
    for (parent = i; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        // 看跟左子树比还是跟右子树比，那就需要确认，左节点大还是右节点大
        if ((child != H->Size) && (H->Elements[child]->Weight > H->Elements[child + 1]->Weight))
            child++;

        if (H->Elements[child]->Weight > temp->Weight)
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
        printf("%d ", H->Elements[i + 1]->Weight);
}

HuffmanTree CreateHuffmanTree()
{
    HuffmanTree T;

    T = (HuffmanTree)malloc(sizeof(struct HTNode));
    T->Left = NULL;
    T->Right = NULL;

    return T;
}

HuffmanTree Huffman(MinHeap H)
{
    int i, N;
    HuffmanTree T;

    N = H->Size;
    for (i = 1; i < N; i++)
    {
        T = (HuffmanTree)malloc(sizeof(struct HTNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = (T->Left->Weight) + (T->Right->Weight);
        InsertMinHeap(T, H);
    }

    T = DeleteMin(H);
    return T;
}

int WPL(HuffmanTree HT, int depth)
{
    int wpl;

    if (!HT->Left && !HT->Right)
        return (depth * HT->Weight);
    else
        return WPL(HT->Left, depth + 1) + WPL(HT->Right, depth + 1);

    return wpl;
}

bool Check(int N, int f[], int wpl)
{
    int i, len;
    char c[MAXSIZE], code[MAXSIZE][MAXSIZE];
    for (i = 1; i <= N; i++)
    {
        getchar(); // 读掉空格和回车
        scanf("%c %s", &c[i], code[i]);
        len += strlen(code[i]) * f[i];
    }

    if (len > wpl)
        return false;
    else
        // 长度没问题就判断二义性
        return !IsPrefix(code, N);
}

int Min(int a, int b)
{
    return a < b ? a : b;
}

bool IsPrefix(char code[][MAXSIZE], int N)
{
    int length;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            length = Min(strlen(code[i]), strlen(code[j]));
            if (strncmp(code[i], code[j], length) == 0)
                return true;
        }
    }
    return false;
}

// 主函数
int main()
{
    int i, N, M, wpl;
    HuffmanTree T;
    MinHeap H;

    char c;
    int f[MAXSIZE];

    mini = CreateHuffmanTree();
    mini->Weight = INFINITY;

    // i 个数
    scanf("%d", &N);
    printf("N: %d\n", N);

    // 这里要先初始化一个最小堆
    H = CreateMinHeap(N);
    for (i = 0; i < N; i++)
    {
        getchar();
        scanf("%c %d", &c, &f[i]);

        T = (HuffmanTree)malloc(sizeof(struct HTNode));
        T->Left = NULL;
        T->Right = NULL;
        T->Weight = f[i];
        InsertMinHeap(T, H);
    }

    // 调试一下
    PrintHeap(H);

    // 读最小堆，构造哈夫曼树
    // 构造成功后，求出最小的 wpl
    T = Huffman(H);
    // PrintHuffman(T);

    wpl = WPL(T, 0);
    // 调试一下
    printf("\nWPL: %d", wpl);

    // j 个人
    scanf("%d", &M);

    // 对每个人的答案进行检查
    for (int j = 0; j < M; j++)
        if (Check(N, f, wpl))
            printf("YES\n");
        else
            printf("NO\n");

    return 0;
}