/*
用一个数组实现双堆栈，并保证数组有空位时必定能够入栈：
    1、DStack CreateStack()： 生成空堆栈，其最大长度为 MaxSize；
    2、int IsEmpty (DStack S, int Tag)：判断堆栈S是否为空；
    3、void Push(DStack S, ElementType item, int Tag)：将元素item压入堆栈；
    4、ElementType Pop(DStack S, int Tag)：删除并返回栈顶元素；
*/

#define MAXSIZE 100

typedef int ElementType;
typedef struct DSNode *DStack;

struct DSNode
{
    ElementType Data[MAXSIZE];
    int LEFT;
    int RIGHT;
};

// 操作集声明
DStack CreateStack();
int IsEmpty(DStack S, int Tag);
int IsFull(DStack S);
void Push(DStack S, ElementType item, int Tag);
ElementType Pop(DStack S, int Tag);

// 操作集
DStack CreateStack()
{
    DStack S;
    S = (DStack)malloc(sizeof(struct DSNode));
    S->LEFT = -1;
    S->RIGHT = MAXSIZE;
    return S;
}

int IsEmpty(DStack S, int Tag)
{
    if (Tag == 0)
        return (S->LEFT == -1);
    else if (Tag == 1)
        return (S->RIGHT == MAXSIZE);
    else
    {
        printf("未知的Tag类型");
        return -1;
    }
}

int IsFull(DStack S)
{
    return (S->LEFT == S->RIGHT);
}

void Push(DStack S, ElementType item, int Tag)
{
    if (IsFull(S))
        printf("栈已满");

    // 看看往左边推还是右边推
    if (Tag == 0)
        S->Data[++(S->LEFT)] = item;
    else if (Tag == 1)
        S->Data[--(S->RIGHT)] = item;
    else
        printf("未知的Tag类型");
}

ElementType Pop(DStack S, int Tag)
{
    ElementType item;

    if (IsEmpty(S, Tag))
        printf("栈已空");

    // 出栈
    if (Tag == 0)
        return S->Data[(S->LEFT)--];
    else if (Tag == 1)
        return S->Data[(S->RIGHT)++];
    else
        printf("未知的Tag类型");
}