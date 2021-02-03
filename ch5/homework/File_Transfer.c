// 集合的简化表示，用数组的下标指示它的值，下标的元素指示父亲的值

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXSIZE];

// 操作集声明
void Initial(SetType S, int N);
SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName R1, SetName R2);

void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int N);

// 操作集实现
void Initial(SetType S, int N)
{
    // 全部初始化为 -1
    for (int i = 0; i < N; i++)
        S[i] = -1;
}

void Input_connection(SetType S)
{
    // 作并集
    ElementType i, j;
    scanf("%d %d", &i, &j);

    SetName S1, S2;
    S1 = Find(S, i - 1);
    S2 = Find(S, j - 1);
    if (S1 != S2)
        Union(S, S1, S2);
}

void Check_connection(SetType S)
{
    ElementType i, j;
    scanf("%d %d", &i, &j);

    SetName S1, S2;
    S1 = Find(S, i - 1);
    S2 = Find(S, j - 1);

    if (S1 != S2)
        printf("NO\n");
    else
        printf("YES\n");
}

void Check_network(SetType S, int n)
{
    int i, counter = 0;
    for (i = 0; i < n; i++)
    {
        if (S[i] < 0)
            counter++;
    }
    if (counter == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", counter);
}

SetName Find(SetType S, ElementType X)
{
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName R1, SetName R2)
{
    if (S[R1] > S[R2])
    { // 集合 R2 比较大,因为是负数
        S[R2] += S[R1];
        S[R1] = R2;
    }
    else
    {
        S[R1] += S[R2];
        S[R2] = R1;
    }
}

// 主函数
int main()
{
    int N;
    scanf("%d", &N);

    SetType S;
    Initial(S, N);

    char in;
    do
    {
        getchar(); // 接收每次多出来的回车
        scanf("%c", &in);
        switch (in)
        {
        case 'I':
            Input_connection(S);
            break;
        case 'C':
            Check_connection(S);
            break;
        case 'S':
            Check_network(S, N);
            break;
        }
    } while (in != 'S');

    return 0;
}