#include <stdio.h>

int findFirstOne(int x)
{
    return x & -x;//又是一个相当巧妙的，x与自己的补码做按位与，剩下的必然是最右侧的一个1，eg -x=0110,x=1010,ret=0010->2
}

int main()
{
    int x;
    printf("输入x:");
    scanf("%d", &x);
    int ans = findFirstOne(x);
    printf("最右侧第一个1对应数值:%d\n", ans);
    return 0;
}