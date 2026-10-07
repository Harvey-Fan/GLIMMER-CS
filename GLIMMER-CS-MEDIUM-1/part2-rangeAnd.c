#include <stdio.h>
//a 到 b 所有数连续按位与，结果等于 a 和 b 从高位开始，最长公共前缀，后面所有 bit 全部置 0。
//原理：只要区间内存在两个数，某一位一个是 0 一个是 1，这一位的最终 & 结果一定是 0。只要 a≠b，中间一定会发生进位，进位位置会翻 0。
unsigned int rangeAnd(unsigned int a, unsigned int b)
{
    int shift = 0;
    while(a != b)//直到相等
    {
        a >>= 1;
        b >>= 1;   //同步右移，就是为了找到最长公共前缀
        shift++;
    }
    return a << shift;  //最长公共前缀低位补零，完成
}

int main()
{
    unsigned int a,b;
    printf("输入a,b(a<b):");
    scanf("%u %u", &a, &b);
    unsigned int ans = rangeAnd(a,b);
    printf("[%u,%u]区间按位与结果：%u\n", a,b,ans);  //%u是无符号int
    return 0;
}