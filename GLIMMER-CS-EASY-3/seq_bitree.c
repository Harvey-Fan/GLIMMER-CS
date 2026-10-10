#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100  //宏定义，数组最大容量100，支持下标0-99

/*
 * 顺序存储二叉树结点
 * - data: 结点数据
 * - used: 当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;//bool类型只有0和1，用于标记这个数组位置有没有真实节点
} SeqTreeNode;


/*
 * 顺序存储二叉树
 * - nodes: 结点数组
 * - size: 数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];  //数组存储
    int size;
} SeqBiTree;


 //ps:根结点放在 nodes[1]，nodes[0] 不使用。
 //结点 i 的左孩子是 2i，右孩子是 2i+1，双亲是 i/2。
   //有效下标范围是 [1, size-1]，

// 判断下标 i 是否落在有效范围内 ，做检查函数
/*辅助函数：检查下标是否合法
条件同时满足：

1. tree 指针不为空（不是野指针）
2. i >=1（不用 0 号下标）
3. i < tree->size 不越界
static：这个函数只能在本文件内部使用，外部不能调用。*/
static bool is_valid_index(const SeqBiTree *tree, int i)
{
    return tree != NULL && i >= 1 && i < tree->size;
}



/* ---------- 1. 初始化 ---------- */
/*
 * 把容量设为 MAX_TREE_SIZE，并把每个位置都置为“空”：
 * used = false，data = 0。
 * 这里用循环逐个清空，而不是依赖未初始化的栈内存里的随机值。
 */
void init_tree(SeqBiTree *tree)  //针对树的操作
{
    if (tree == NULL) {
        return;
    }
    tree->size = MAX_TREE_SIZE;
    for (int i = 0; i < tree->size; i++) {//遍历数组
        tree->nodes[i].data = 0;         //全部置0
        tree->nodes[i].used = false;      //标记为空
    }
}

/* ---------- 2. 创建根结点，同时检查 ---------- */
/*
 * 根固定放在下标 1。
 * 失败返回 false：指针为空，或根已经存在（避免悄悄覆盖旧数据）。
 */
bool set_root(SeqBiTree *tree, int value)//ps,bool类型的意思是只执行，不返回任何值，和void不同的是，他会告诉main成功了没有，
{                                       //如果ret true就完成，如果ret false就直接停止干活，而void不会保留报错信息，不利于检查
    if (!is_valid_index(tree, 1)) {//！作用是调整一下，因为空是0，！0是非0就可以报错了
        return false;  //非1，操作失败
    }
    if (tree->nodes[1].used) {  //ps tree是结构体指针，用->访问内部成员，而nodes是数组，是结构体实体，用.访问成员
        return false;
    }
    tree->nodes[1].data = value;
    tree->nodes[1].used = true;  //检查传进了值，且为已用状态
    return true;

}


/*
 * 左右孩子的逻辑只差一个“+1”，抽成内部函数避免重复代码。
 * 失败的情形：*/
static bool set_child(SeqBiTree *tree, int parent_node, int value, bool is_left)
{
    if (!is_valid_index(tree, parent_node)) { //检查父节点的数组下标
        return false;
    }
    if (!tree->nodes[parent_node].used) {//检查父节点的存在与否 
        return false;
    }

    /* parent_node 最大为 size-1，乘 2 不会溢出 int，可放心计算 */
    int child = is_left ? parent_node * 2 : parent_node * 2 + 1; //关键，通过输入的布尔值判断孩子左右，统一了函数，

    if (!is_valid_index(tree, child)) {
        return false;
    }
    if (tree->nodes[child].used) {
        return false; //同上，检查用的
    }
    tree->nodes[child].data = value;  //赋值
    tree->nodes[child].used = true;  //别忘了标记使用情况
    return true;
}

/* ---------- 3. 创建左孩子 ---------- */
bool set_left_child(SeqBiTree *tree, int parent_node, int value)
{
    return set_child(tree, parent_node, value, true);//都到大函数里执行
}

/* ---------- 4. 创建右孩子 ---------- */
bool set_right_child(SeqBiTree *tree, int parent_node, int value)
{
    return set_child(tree, parent_node, value, false);
}


/* ---------- 5. 层序遍历 ---------- */
/*
 * 数组下标顺序本身就是层序，所以不需要队列。
 * 第 k 层（k 从 1 起）占据下标 [2^(k-1), 2^k - 1]。
 * 为了不把后面一长串无意义的 -1 都打出来，
 * 先找到最后一个有结点的下标，只打印到它所在那一层为止。
 * 空位置打印 -1，每层结束换行。
 */
void level_order(SeqBiTree *tree)
{
    if (tree == NULL) {
        return;
    }  //空则返回

    int last = 0; /* 最后一个非空结点的下标，0 表示树是空的 */
    for (int i = tree->size - 1; i >= 1; i--) {//从最大下标往下遍历，
        if (tree->nodes[i].used) {
            last = i;  //标记 最后一个非空节点下标
            break;
        }
    }

    if (last == 0) {
        printf("(empty tree)\n");
        return;
    }

    for (int start = 1; start <= last; start *= 2) {// start <= last很关键，保证不会多打印后面一堆空的节点，到最后一层就停止了
        int end = start * 2 - 1; //start到 end 指的是每一层的下标起始，
        for (int i = start; i <= end && i < tree->size; i++) {//i去遍历每一层，同时限制不能超过size，避免越界
            if (i > start) {
                printf(" ");
            }
            if (tree->nodes[i].used) {
                printf("%d", tree->nodes[i].data);
            } else {
                printf("-1");
            }
        }
        printf("\n");//一层完换行
    }//直到最后非全空层
}

/* ---------- 6. 测试 ---------- */
int main(void)
{
    SeqBiTree tree;   //建树，含有数组和大小，数组存数据和状态
    init_tree(&tree);//初始化

    /*
     * 构造一棵三层的二叉树（故意让 3 的左孩子留空，用来观察 -1）：
     *
     *           1            <- 下标 1
     *         /   \
     *        2     3         <- 下标 2, 3
     *       / \     \
     *      4   5     7       <- 下标 4, 5, (6 空), 7
     */
    set_root(&tree, 1);   //创建根节点，1是根节点的value
    set_left_child(&tree, 1, 2);
    set_right_child(&tree, 1, 3);
    set_left_child(&tree, 2, 4);
    set_right_child(&tree, 2, 5);
    set_right_child(&tree, 3, 7);

    printf("层序遍历结果(空位置为 -1):\n");
    level_order(&tree);

    // 预期输出：
    //  1
    //  2 3
    // 4 5 -1 7
    return 0;
}
