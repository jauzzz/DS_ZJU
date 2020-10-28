// 最大子列和问题：https://blog.csdn.net/liyuanyue2017/article/details/82990246

/* 
    算法一: 求出所有子列和的值，找到最大的    
    算法二：逐个元素处理，直接求出当前情况下最大的子列和值（由于最大子列和必定由正的子列和相加而成）
    算法三：分治法，将求子列和最大值分为：求左半子列和最大值、右半子列和最大值、跨界限子列和最大值
*/

#include <stdio.h>

int sum1(int l[], int N);
int sum2(int l[], int N);
int sum3(int l[], int N);
int Max3(int a, int b, int c);
int MiddleSum(int list[], int middle, int left, int right);

int sum1(int list[], int N)
{
    int sum, max = 0;
    int i, j;

    for (i = 0; i < N; i++)
    {
        sum = 0;
        for (j = i; j < N; j++)
        {
            sum = sum + list[j];
            if (sum > max)
            {
                max = sum;
            }
        }
    }

    return max;
}

int sum2(int list[], int N)
{
    int sum, max = 0;
    int i;

    for (i = 0, sum = 0; i < N; i++)
    {
        sum += list[i];
        if (sum > max)
        {
            max = sum;
        }
        else if (sum < 0)
        {
            sum = 0;
        }
    }

    return max;
}

int Max3(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int MiddleSum(int list[], int middle, int left, int right)
{
    int i, middlesum;
    int leftsum, rightsum, leftmax, rightmax, max;

    leftmax = rightmax = 0;

    // 往左加
    for (i = middle, leftsum = 0, leftmax = 0; i > left; i--)
    {
        leftsum += list[i];
        if (leftsum > leftmax)
        {
            leftmax = leftsum;
        }
    }

    // 往右加
    for (i = middle + 1, rightsum = 0, rightmax = 0; i < right; i++)
    {
        rightsum += list[i];
        if (rightsum > rightmax)
        {
            rightmax = rightsum;
        }
    }

    max = leftmax + rightmax;
    return max;
}

int DivideAndConquer(int list[], int left, int right)
{
    int max;
    int middle;
    int leftsum, rightsum, middlesum;

    // 只有一个时终止
    if (left == right)
        return (list[left] > 0) ? list[left] : 0;

    // 继续分
    middle = (left + right) / 2;
    leftsum = DivideAndConquer(list, left, middle);
    rightsum = DivideAndConquer(list, middle + 1, right);
    middlesum = MiddleSum(list, middle, left, right);

    max = Max3(leftsum, rightsum, middlesum);
    return max;
}

int sum3(int list[], int N)
{
    return DivideAndConquer(list, 0, N - 1);
}

int main()
{
    int max;
    int List[6] = {-2, 11, -4, 13, -5, -2};

    max = sum1(List, 6);
    printf("[直接求和] max sum of sub sequence is: %d\n", max);

    max = sum2(List, 6);
    printf("[在线处理] max sum of sub sequence is: %d\n", max);

    max = sum3(List, 6);
    printf("[分治法] max sum of sub sequence is: %d\n", max);

    return 0;
}