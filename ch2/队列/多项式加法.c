#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;

struct PolyNode
{
    int coef;  // 系数
    int expon; // 指数
    Polynomial link;
};

Polynomial p1, p2;

// 操作集声明
int Compare(int a, int b);
Polynomial PolyAdd(Polynomial p1, Polynomial p2);
void Attach(int c, int e, Polynomial *p);

// 操作集
int Compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    else
        return -1;
}

void Attach(int c, int e, Polynomial *p)
{
    Polynomial node;
    node = (Polynomial)malloc(sizeof(struct PolyNode));
    node->coef = c;
    node->expon = e;
    node->link = NULL;

    // 要对 p 做修改
    (*p)->link = node;
    *p = node;
}

Polynomial PolyAdd(Polynomial p1, Polynomial p2)
{
    int sum;
    Polynomial p3, p4, temp;
    p3 = (Polynomial)malloc(sizeof(struct PolyNode));
    p4 = p3;

    while (p1 && p2)
    {
        switch (Compare(p1->expon, p2->expon))
        {
        case 0:
            sum = p1->coef + p2->coef;
            if (sum)
                // 这里需要假定 attach 会对 p3 做修改
                Attach(sum, p1->expon, &p3);

            // 往下推进
            p1 = p1->link;
            p2 = p2->link;
            break;
        case 1:
            Attach(p1->coef, p1->expon, &p3);
            p1 = p1->link;
            break;
        case -1:
            Attach(p2->coef, p2->expon, &p3);
            p2 = p2->link;
            break;
        default:
            printf("Unknown error.");
            break;
        }
    }

    // 处理手尾，将剩余的多项式复制到 p3 中
    for (; p1; p1 = p1->link)
        Attach(p1->coef, p1->expon, &p3);
    for (; p2; p2 = p2->link)
        Attach(p2->coef, p2->expon, &p3);

    // 然后要拿最后一个，指向为空
    p3->link = NULL;
    // 由于 p3 的首节点为空节点，真正的第一个多项式为 p4->link
    temp = p4;
    p4 = temp->link;
    free(temp);

    // 返回 p3
    return p4;
}