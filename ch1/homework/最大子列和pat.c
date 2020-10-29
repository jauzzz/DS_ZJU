// 最大子列和问题：https://pintia.cn/problem-sets/1302953266564911104/problems/1302953426338533377

/* 
    输入最大子列和的起始索引和结束索引
    如果最大子列和有多个，输出索引最小的子序列起始值和结束值
    如果最大子列和，最大为负数，则将最大子列和定义为0，并输出第一个数字和最后一个数字的值
*/

#include <stdio.h>

int *sum(int l[], int N);

int *sum(int list[], int N)
{
    int i, sum, start = 0;

    static int ans[3];

    for (i = 0, sum = 0; i < N; i++)
    {
        sum += list[i];
        if (sum > ans[0])
        {
            ans[2] = i;
            ans[1] = start;
            ans[0] = sum;
        }
        else if (sum < 0)
        {
            start = i + 1;
            sum = 0;
        }
    }

    return ans;
}

int main()
{
    int *ans;
    int N = 6;
    int List[] = {-1, 11, -4, -13, -5, -2};

    ans = sum(List, 6);
    if (ans[0] == 0)
    {
        ans[1] = 0;
        ans[2] = N - 1;
    }

    printf("[在线处理] max sum of sub sequence is: %d\n", ans[0]);
    printf("子序列起始值：%d, 子序列结束值： %d\n", List[ans[1]], List[ans[2]]);

    return 0;
}