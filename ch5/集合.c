#define MAXSIZE 1000

typedef int ElementType;

typedef struct
{
    ElementType Data;
    int Parent;
} SetType;

// 操作集声明
int Find(SetType S[], ElementType X);                    // 查找某个元素所在的集合(用根结点表示)
void Union(SetType S[], ElementType X1, ElementType X2); // 集合的并运算

// 操作集实现
int Find(SetType S[], ElementType X)
{
    int i;
    for (i = 0; i < MAXSIZE && S[i].Data != X; i++)
        ;

    if (i >= MAXSIZE)
        return -1;

    for (; S[i].Parent >= 0; i = S[i].Parent)
        ;

    return i;
}

void Union(SetType S[], ElementType X1, ElementType X2)
{
    /*
    1. 分别找到X1和X2两个元素所在集合树的根结点
    2. 如果它们不同根，则将其中一个根结点的父结点指针设置成另一个根结点的数组下标
    */
    int r1, r2;

    r1 = Find(X1, S);
    r2 = Find(X2, S);

    if (r1 != r2)
        S[r2].Parent = r1;
}

// 上面的 Union 方法，总是将 S2 并入 S1
// 为了最好的性能，应该将小集合并入大集合
void Union(SetType S[], ElementType X1, ElementType X2)
{
    /*
    1. 分别找到X1和X2两个元素所在集合树的根结点
    2. 如果它们不同根，则将其中一个根结点的父结点指针设置成另一个根结点的数组下标
    */
    int r1, r2;

    r1 = Find(X1, S);
    r2 = Find(X2, S);

    if (r1 == r2)
        return;

    if (S[r1].Parent < S[r2].Parent)
    {
        // 说明 r2 是比较大的集合
        S[r2].Parent += S[r1].Parent;
        S[r1].Parent = r2;
    }
    else
    {
        // 说明 r1 是比较大的集合
        S[r1].Parent += S[r2].Parent;
        S[r2].Parent = r1;
    }
}