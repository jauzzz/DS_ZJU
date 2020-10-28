// 题目：https://www.icourse163.org/learn/ZJU-93001?tid=1461682474#/learn/content?type=detail&id=1238255556&cid=1258682845

#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAXN 100
#define MAXK 1e7

clock_t start, stop;
double duration;

double p1(int n, double a[], double x);
double p2(int n, double a[], double x);

// 按照公式直接翻译成代码
double p1(int n, double a[], double x)
{
    int i;
    double p = a[0];

    for (i = 1; i <= n; i++)
    {
        p += (1 / a[i] * pow(x, i));
    }

    return p;
}

// 秦九韶
double p2(int n, double a[], double x)
{
    int i;

    double p = a[n];
    for (i = n; i > 0; i--)
    {
        p = 1 / a[i - 1] + x * p;
    }

    return p;
}

// 进行一下速度测试：使用 clock 和 CLK_TCK
int main()
{
    int i;
    double a[MAXN];

    a[0] = 1;
    for (i = 1; i < MAXN; i++)
    {
        a[i] = (double)i;
    }

    // 测试主体代码
    // NOTE: 当程序运行过快，在一个时钟 tick 之内就已经完成了，那么是无法捕捉到运行一次需要多少 tick 的？
    //       解决的方法也很简单：重复运行这个程序，直到它超过一个时钟 tick，然后除以次数，计算出单次的时间
    start = clock();
    p1(MAXN - 1, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration1 = %6.2e\n", duration);

    start = clock();
    p2(MAXN - 1, a, 1.1);
    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("ticks2 = %f\n", (double)(stop - start));
    printf("duration2 = %6.2e\n", duration);

    return 0;
}

/*
    ticks1 = 14.000000
    duration1 = 1.40e-05
    ticks2 = 1.000000
    duration2 = 1.00e-06

    观察结果，可以知道，秦九韶算法是比较快的，差了一个数量级
*/