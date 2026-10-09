#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100

/*
 * 顺序存储二叉树结点
 * - data: 结点数据
 * - used: 当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;


/*
 * 顺序存储二叉树
 * - nodes: 结点数组
 * - size: 数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;


 //ps:根结点放在 nodes[1]，nodes[0] 不使用。
 //结点 i 的左孩子是 2i，右孩子是 2i+1，双亲是 i/2。
   //有效下标范围是 [1, size-1]，

// 判断下标 i 是否落在有效范围内 
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
void init_tree(SeqBiTree *tree)
{
    if (tree == NULL) {
        return;
    }
    tree->size = MAX_TREE_SIZE;
    for (int i = 0; i < tree->size; i++) {
        tree->nodes[i].data = 0;
        tree->nodes[i].used = false;
    }
}

/* ---------- 2. 创建根结点 ---------- */
/*
 * 根固定放在下标 1。
 * 失败返回 false：指针为空，或根已经存在（避免悄悄覆盖旧数据）。
 */
bool set_root(SeqBiTree *tree, int value)
{
    if (!is_valid_index(tree, 1)) {
        return false;
    }
    if (tree->nodes[1].used) {
        return false;
    }
    tree->nodes[1].data = value;
    tree->nodes[1].used = true;
    return true;

}


/*
 * 左右孩子的逻辑只差一个“+1”，抽成内部函数避免重复代码。
 * 失败的情形：
 *   1) parent_node 越界；
 *   2) 双亲位置是空的（不能给不存在的结点挂孩子）；
 *   3) 孩子下标超出数组容量；
 *   4) 孩子位置已被占用。
 */
static bool set_child(SeqBiTree *tree, int parent_node, int value, bool is_left)
{
    if (!is_valid_index(tree, parent_node)) {
        return false;
    }
    if (!tree->nodes[parent_node].used) {
        return false;
    }

    /* parent_node 最大为 size-1，乘 2 不会溢出 int，可放心计算 */
    int child = is_left ? parent_node * 2 : parent_node * 2 + 1;

    if (!is_valid_index(tree, child)) {
        return false;
    }
    if (tree->nodes[child].used) {
        return false;
    }
    tree->nodes[child].data = value;
    tree->nodes[child].used = true;
    return true;
}

/* ---------- 3. 创建左孩子 ---------- */
bool set_left_child(SeqBiTree *tree, int parent_node, int value)
{
    return set_child(tree, parent_node, value, true);
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
    }

    int last = 0; /* 最后一个非空结点的下标，0 表示树是空的 */
    for (int i = tree->size - 1; i >= 1; i--) {
        if (tree->nodes[i].used) {
            last = i;
            break;
        }
    }
    if (last == 0) {
        printf("(empty tree)\n");
        return;
    }

    for (int start = 1; start <= last; start *= 2) {
        int end = start * 2 - 1; /* 当前层的最后一个下标 */
        for (int i = start; i <= end && i < tree->size; i++) {
            if (i > start) {
                printf(" ");
            }
            if (tree->nodes[i].used) {
                printf("%d", tree->nodes[i].data);
            } else {
                printf("-1");
            }
        }
        printf("\n");
    }
}

/* ---------- 6. 测试 ---------- */
int main(void)
{
    SeqBiTree tree;
    init_tree(&tree);

    /*
     * 构造一棵三层的二叉树（故意让 3 的左孩子留空，用来观察 -1）：
     *
     *           1            <- 下标 1
     *         /   \
     *        2     3         <- 下标 2, 3
     *       / \     \
     *      4   5     7       <- 下标 4, 5, (6 空), 7
     */
    set_root(&tree, 1);
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
