#include <stdio.h>

// 获取x的第n位的函数
int getBit(int x, int n)
{
    return (x >> n) & 1;  //ps: 最低位规定为第0位，所以实际上要右移n位后，最低位才为所需的
}

int main()
{
    int x, n;
    printf("请输入x和n：");
    scanf("%d %d", &x, &n);
    int ans = getBit(x, n);
    printf("第%d位的值：%d\n", n, ans);
    return 0;
}