#include <stdio.h>

void printN(int N);
void printN1(int N);

void printN(int N)
{
    int i;
    for (i = 0; i <= N; i++)
    {
        printf("%d\n", i);
    }

    return;
}

// 递归版
void printN1(int N)
{
    if (N)
    {
        printN1(N - 1);
        printf("%d\n", N);
    }

    return;
}


// 测试不同版本的 printN，递归版的在数据量大时会堆栈溢出
int main()
{
    int N;
    printf("please enter a number:");
    scanf("%d", &N);
    printf("\n");

    printN1(N);
    return 0;
}