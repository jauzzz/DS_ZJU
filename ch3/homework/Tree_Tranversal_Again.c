// https://pintia.cn/problem-sets/1302953266564911104/problems/1310235296110600194
// 栈的输入是前序遍历的，栈的输出是中序遍历的，给出该树的后序遍历
//
// 遍历方式：
//  前序：根左右
//  中序：左根右
//  后序：左右根

/*
方式：重排

举例:
 前序：1     234     56
 中序: 324   1       65
 后序: 342   65      1

 前序：[1 2 3 4 5 6]
 中序：[3 2 4 1 6 5]

重排：
 步骤：
     1. 根据前序根是 1
     2. 那么对中序进行拆分：[3 2 4] [1] [6 5]
     3. 得知，左的长度3，右的长度2，对应回前序进行拆分：[1] [2 3 4] [5 6]
     4. 对左和右继续拆分，重复步骤123，这里需要确定结束条件
     5. 结束条件：拆到只有一个元素，即叶子节点/根
 结果：
     [3 2 4] [1] [6 5]   -->     Reverse([3 2 4]) + Reverse([6 5]) + Reverse([1])，Reverse([1]) == Post[1]
     Reverse([3 2 4])    -->     Reverse([3]) Reverse([4]) Reverse([2]) --> Post[3, 4, 2]
         中序：[3 2 4]
         前序：[2 3 4]
         根为 2
         对中序进行拆分: [3] [2] [4]
         符合结束条件，结束
     Reverse([6 5])      -->     Reverse([6]) Reverse([5]) --> Post[6, 5]
         中序：[6 5]
         前序: [5 6]
         根为 5
         对中序进行拆分： [6] [5]
         符合结束条件，结束
     最终结果：Post[3, 4, 2] + Post[6, 5] + Post[1]
*/

#define Maxsize 10
#define DEBUG 0

#include <stdio.h>
#include <string.h>

int pre[Maxsize], in[Maxsize], post[Maxsize], temp[Maxsize];
int pindex = 0;

void reversal(int root, int start, int end);

void reversal(int root, int start, int end)
{
    // root: 前序中，当前序列的根的位置
    // start: 中序队列，起始位置
    // end: 中序队列，结束位置
    if (DEBUG)
        printf("打印当前参数：%d %d %d\n", root, start, end);

    int i = start;

    // 需要先构造出 pre 和 in 的队列
    // 这个在 main 函数里面完成

    // 结束条件
    if (start > end)
        return;

    // 前序的根 pre[root]
    // 进行拆分，要找到中序排列中，根的位置
    while (i < end && pre[root] != in[i])
        i++;

    // 找到之后，进行拆分，按照左右根的顺序
    reversal(root + 1, start, i - 1);
    reversal(root + 1 + i - start, i + 1, end);

    if (DEBUG)
        printf("\n添加到队列 [%d %d %d] %d %d\n", root, start, end, pindex, pre[root]);

    post[pindex++] = pre[root];
}

int main()
{
    int N, num;
    scanf("%d", &N);

    int pindex = 0;
    int tindex = 0;
    int index = 0;

    if (N)
    {
        char s[5];
        printf("%d", N);

        for (int i = 0; i <= 2 * N; i++)
        {
            scanf("%s", s);
            if (strlen(s) == 4)
            {
                scanf(" %d", &num);
                pre[pindex++] = num;
                temp[tindex++] = num;
            }
            else
            {
                in[index++] = temp[--tindex];
            }
        }
    }

    // 构造出 pre 和 in 的队列
    // DEBUG: 调试一下，看看 pre 和 in 的队列是否正确
    if (DEBUG)
    {
        printf("\n前序序列：\n");
        for (int loop = 0; loop < Maxsize; loop++)
            printf("%d ", pre[loop]);

        printf("\n中序序列：\n");
        for (int loop = 0; loop < Maxsize; loop++)
            printf("%d ", in[loop]);
    }

    reversal(0, 0, N - 1);

    printf("\n后序序列：\n");
    for (int loop = 0; loop < Maxsize; loop++)
        printf("%d ", post[loop]);

    return 0;
}