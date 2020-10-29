/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */

#include <stdio.h>

int binsearch(int list[], int start, int end, int n)
{
    int mid, midVal;

    if (start == end)
        return start;

    mid = (start + end) / 2;
    midVal = list[mid];

    if (midVal < n)
    {
        return binsearch(list, mid + 1, end, n);
    }
    else
    {
        return binsearch(list, start, mid, n);
    }

    // 表示没找到
    return -1;
}

int main()
{
    int i, val, ret;
    int a[8] = {-32, 12, 16, 24, 36, 45, 59, 98};

    for (i = 0; i < 8; i++)
        printf("%d\t", a[i]);

    printf("\n请输人所要查找的元素：");
    scanf("%d", &val);

    ret = binsearch(a, 0, 8, val);
    if (-1 == ret)
        printf("查找失败 \n");
    else
        printf("查找成功, 索引值为%d\n", ret);
    return 0;
}