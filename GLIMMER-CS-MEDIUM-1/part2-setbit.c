#include <stdio.h>

// 将x第n位设置为t（t=0或1）
int setBit(int x, int n, int t)
{
    if(t == 1)
    {
        return x | (1 << n);  // 必定是1，故或是1
    }
    else
    {
        return x & ~(1 << n); // 很巧妙，先做一个掩码，掩码为0的位按位与后必定为0，达到了修改的效果，同时又不改变x的其他位
    }                         //eg,如果x某位为0，0&1=1，若某位为1，1&1=1，不影响原来的
}

int main()
{
    int x, n, t;
    printf("输入x n t:");
    scanf("%d %d %d", &x, &n, &t);
    int ans = setBit(x, n, t);
    printf("修改后整数：%d\n", ans);
    return 0;
}