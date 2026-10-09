//实现前序，中序，后序三个功能加深度统计。
#include <stdio.h>
#include <stdlib.h>

// 二叉树节点定义
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建单个节点，即多个根节点
TreeNode* create_node(int value)
{
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 递归建树，#代表空节点
TreeNode* create_tree()
{
    char ch;
    scanf(" %c", &ch);
    if (ch == '#')
    {
        return NULL;//#号的作用是返回上一层，注意函数类型是指针，所以要返回空
    }
    ungetc(ch, stdin);
    /*ungetc(ch, stdin)：把刚刚从键盘读到的 1 个字符，塞回输入缓冲区
### 例子：读到 1

1.  scanf(" %c", &ch) 拿走字符1
2. 判断不是`#`，但是字符1已经被消耗掉了
3.  ungetc把'1'塞回缓冲区
4. scanf("%d", &val)` 读取，拿到数字 1
 如果没有 ungetc：1已经被 % c 读走消耗，%d就拿不到这个数字，程序直接错。

*/
    int val;
    scanf("%d", &val);  //接受到缓冲区的值
    TreeNode *root = create_node(val);  //创造节点
    root->left = create_tree();
    root->right = create_tree();
    return root;  //第二种情况返回，当某个节点左右孩子都有了，就返回上一层
}

// 前序遍历：根 左 右
void pre_order(TreeNode *root)
{
    if(root == NULL) return;
    printf("%d ", root->data);
    pre_order(root->left);
    pre_order(root->right);
}

// 中序遍历：左 根 右
void in_order(TreeNode *root)
{
    if(root == NULL) return;
    in_order(root->left);
    printf("%d ", root->data);
    in_order(root->right);
}

// 后序遍历：左 右 根，三种遍历方式很相似，只是顺序不同而已，很好理解，不过多在注释中解释
void post_order(TreeNode *root)
{
    if(root == NULL) return;
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->data);
}

// 题目要求：统计树深度的递归函数
// 返回以root为根的二叉树的深度（高度）
int getDepth(TreeNode *root)
{
    if (root == NULL)
    {
        return 0; // 空树，深度为0
    }
    int left_depth = getDepth(root->left);   // 左子树深度
    int right_depth = getDepth(root->right); // 右子树深度
    // 当前树深度 = 左右子树较大值 + 1（加上自己这一层）
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}    //逻辑，找到最下面的那个空节点，作为基准0，然后往上加1


int main()
{
    printf("请输入二叉树序列，# 代表空节点\n");
    // 这棵树:
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
    // 输入: 1 2 4 # # 5 # # 3 6 # # 7 # #  ps 回到1这最开始这一层时，左指针这一行已经操作完成了，只剩下单右指针直接给3，没问题
    //eg 4 后#，ret 空，告诉2左指针指向空，第二个#告诉2右指针为空，然后ret root,回到上一个节点2继续进程
    TreeNode *root = create_tree(); //调用前面的

    printf("前序遍历结果：");
    pre_order(root);
    printf("\n");

    printf("中序遍历结果：");
    in_order(root);
    printf("\n");

    printf("后序遍历结果：");
    post_order(root);
    printf("\n");

    // 调用depth函数，初始current_depth=0，max_depth=0
    int tree_depth = getDepth(root);
    printf("\n二叉树的最大深度 = %d\n", tree_depth);

    return 0;
}
