#include <stdio.h>
#include <stdbool.h>

// 定义简单队列结构用于 BFS
typedef struct {
    int pos;    // 当前节点编号 (0~15)
    int dist;   // 到达当前节点的最短步数
} Node;


int minStepsToCheese(int walls) {
    int start = 0;
    int target = 15;

    // 如果起点或终点本身是墙，直接不可达
    if ((walls & (1 << start)) || (walls & (1 << target))) {//任一堵住都不行
        return -1;
    }

    // BFS 队列与访问位图
    Node queue[16];
    int front = 0, rear = 0;
    int visited = 0;

    // 起点入队并标记已访问（请使用位运算）
    queue[rear++] = (Node){start, 0};//把起点 (0 号，步数 0) 放进队列，rear 变成 1，打包放进数组
    visited |= (1 << start);        //1.visited |= (1 << 0)→ visited = 0b0000000000000001，标记 pos0 已访问

    // 上、下、左、右四个方向的节点偏移量
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    /*dr 是行变化，dc 是列变化：

- dr=-1,dc=0  → 向上一行
- dr=1, dc=0  → 向下一行
- dr=0, dc=-1 → 向左一列
- dr=0, dc=1  → 向右一列*/

    // //TO DO ========================
    while (front < rear) {//BFS 核心循环：队列不为空就继续
//front < rear：队列里面还有元素。front 等于 rear = 队列为空，搜索结束。
        // 取出队首
        Node curr = queue[front++];//取出队列最前面的节点，front++（队头往后移）。//curr指当前节点
        int curPos = curr.pos;//currentposition
        int curDist = curr.dist;//currentdistance

        // 到达终点，返回步数
        if (curPos == target) {//如果当前格子就是 15 号，直接返回当前步数。BFS 特性：第一次碰到终点就是最短路径。
            return curDist;    //只要碰到，立马返回，就能保证最短
        }

        // 把pos转成行列
        int r = curPos / 4;
        int c = curPos % 4;
        /*pos 转行列公式：`r = pos /4`，`c = pos %4`
        例子 curPos=0：r=0/4=0，c=0%4=0 → 第 0 行第 0 列。
        curPos=5：5/4=1，5%4=1 → 第 1 行第 1 列。*/
        // 遍历4个方向
        for (int d = 0; d < 4; d++) {//非常巧妙地遍历四个方向,d=0,1,2,3分别代表上下左右
            int nr = r + dr[d];
            int nc = c + dc[d];
            // 判断行列合法不越界：0<=nr<4，0<=nc<4
            if (nr >=0 && nr <4 && nc >=0 && nc <4) {
                int newPos = nr *4 + nc;//还原new position
                // 判断：不是墙，并且没有访问过
                if ( !(walls & (1 << newPos)) && !(visited & (1 << newPos)) ) {
                    visited |= (1 << newPos);//标记一处访问
                    queue[rear++] = (Node){newPos, curDist + 1};//把新节点压入队列，步数 = 当前步数 +1
                }       //走到当前格子花了 curDist 步，那走到相邻这个新格子，就要再多走 1 步（再多跨一格）
            }
        }
    }
    // //END OF TO DO ========================

    return -1; //队列全部遍历完，始终没碰到终点，说明无路可走，返回 - 1。
}


int main() {
    int walls = (1 << 5) | (1 << 10); // 5号和10号格子是墙，用或达到标记的效果
    int steps = minStepsToCheese(walls);
    printf("Minimum steps: %d\n", steps); // 应输出 6
    return 0;
}
