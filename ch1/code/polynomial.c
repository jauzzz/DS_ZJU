/* 
    Polynomial: 多项式求值 
*/
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAXN 10
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
        p += (a[i] * pow(x, i));
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
        p = a[i - 1] + x * p;
    }

    return p;
}

// 进行一下速度测试：使用 clock 和 CLK_TCK
int main()
{
    int i;
    double a[MAXN];
    for (i = 0; i < MAXN; i++)
    {
        a[i] = (double)i;
    }

    // 测试主体代码
    // NOTE: 当程序运行过快，在一个时钟 tick 之内就已经完成了，那么是无法捕捉到运行一次需要多少 tick 的？
    //       解决的方法也很简单：重复运行这个程序，直到它超过一个时钟 tick，然后除以次数，计算出单次的时间
    start = clock();

    // 重复 MAXK 次
    for (i = 0; i < MAXK; i++)
    {
        p1(MAXN - 1, a, 1.1);
    }

    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC / MAXK;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration1 = %6.2e\n", duration);

    start = clock();
    for (i = 0; i < MAXK; i++)
    {
        p2(MAXN - 1, a, 1.1);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC / MAXK;
    printf("ticks2 = %f\n", (double)(stop - start));
    printf("duration2 = %6.2e\n", duration);

    return 0;
}

// 观察结果，可以知道，秦九韶算法是比较快的，差了一个数量级