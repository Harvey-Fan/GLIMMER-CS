#include <stdio.h>

// 递归函数：位运算N皇后
// col：列掩码，bit=1表示该列已经放了皇后
// pie：主对角线（撇，左上→右下）掩码
// na：副对角线（捺，右上→左下）掩码
int dfs(int col, int pie, int na, int fullMask)
{
    // 递归终止：所有列全部填满，找到1组解
    if(col == fullMask){  //每一列都是1就爆满了
        return 1;  //递归出口
    }
    int count = 0;
    // 所有可以放皇后的位置：三个掩码取或得到被禁止位置，取反得到可选位置
    int available = (~(col | pie | na)) & fullMask;
    //这一行是关键！！！，(col | pie | na)是将列中所有遭到ban的地方置1，而按位取反之后1变成可取位置，其他ban位为0，而问题是，int是32个字节，这样会让根本填不了的高位变成无意义的1（实则不可取），故按位与fullmask的意义在于-》消除高位的无意义1，保留低位真正可填的位置1
    while(available != 0)//直到每一列已经被塞满了
    {
        // 取出最右边的可用bit（最右侧可以放皇后的位置）
        int pos = available & -available;  //这个在上个题中提到过，就是取最右边的相同1
        available = available - pos; // 把这个位置从可用集合去掉，避免下一次取pos又取一样的

        // col | pos：标记这一列被占用
        // (pie | pos) <<1：下一行，主对角线整体向左下移1位
        // (na | pos) >>1：下一行，副对角线整体向右下移1位
        count += dfs( col|pos , (pie|pos)<<1 , (na|pos)>>1 , fullMask );//在操作中，我们只关心具体某一行所标记的可用情况，列与对角线只起筛选作用，此时，标记了下一行由于上一行的pos填写而遭到ban的ban位，回到14行，递归
    }
    return count;//回溯，把最终结果交给dfs,再交给ans
}

// 计算N皇后总方案数
int nQueenBit(int n)
{
    // fullMask：低n位全部置1，高位全部0。例如n=4 →0b10000 0b1111(ps 0b代表二进制) 怎么理解？类比十进制1000-1=999，后面的数字将保持该进制下的最高数字
    int fullMask = (1 << n) - 1;  //作用！：用 0 和 1 构成的 “遮罩”，用来筛选保留 / 清除某些 bit
    return dfs(0,0,0,fullMask);  //00001111
}

int main()
{
    int N;
    printf("请输入反应堆规模N(1<=N<=15):");
    scanf("%d",&N);
    int ans = nQueenBit(N);
    printf("控制棒摆放方案总数 = %d\n", ans);
    return 0;
}