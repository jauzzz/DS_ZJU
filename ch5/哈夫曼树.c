/*
    哈夫曼树：
        每个叶子节点带有权重 W，从根节点到叶子节点之间的长度为 L；
        所有叶子节点的带权路径和 WPL = ∑ (W * L)

        WPL 最小的树称为哈夫曼树（最优二叉树）
*/

#include <stdbool.h>

#define MinData -10000

typedef struct HNode *MinHeap;
typedef struct HuffmanNode *HuffmanTree;
typedef HuffmanTree ElementType;

struct HuffmanNode
{
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

struct HNode
{
    ElementType *Elements;
    int Size;     // 堆的当前元素个数
    int Capacity; // 堆的最大容量
};

// 操作集声明
HuffmanTree Huffman(MinHeap H); // 将一个权值序列构造成哈夫曼树

// 操作集实现
HuffmanTree Huffman(MinHeap H)
{
    int i;
    HuffmanTree T;

    for (i = 1; i < H->Size; i++)
    {
        T = (HuffmanTree)malloc(sizeof(struct HNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = (T->Left->Weight) + (T->Right->Weight);
        Insert(H, T);
    }

    T = DeleteMin(H);
    return T;
}