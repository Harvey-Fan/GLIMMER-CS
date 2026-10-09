#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;           // 节点存储的数据
    struct TreeNode *left;  // 左子树指针
    struct TreeNode *right; // 右子树指针
} TreeNode;  //一个节点由三部分构成

// 创建新节点：值为value，左右指针置NULL
TreeNode* create_node(int value)
{
    // 分配内存
    TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;  
}

// 先序遍历打印二叉树（用来验证树是否创建成功）
void pre_order(TreeNode *root)  //拿根来
{
    if(root == NULL) return;
    printf("%d ", root->data);
    pre_order(root->left);
    pre_order(root->right);//先序遍历，根左右
    /* 到达一个节点：
 1.先打印当前这个根节点
 2. 然后**递归把左边一整棵子树全部打印完**，遇到`NULL`就 return 原路返回上一级函数
 3. 左边全部搞定返回之后，**再递归把右边一整棵子树全部打印完** */
}

int main()
{
    /*
        构造这棵树：
             1
           /   \
          2     3
         / \   / \
        4  5  6  7
    */
    TreeNode *n1 = create_node(1);
    TreeNode *n2 = create_node(2);
    TreeNode *n3 = create_node(3);
    TreeNode *n4 = create_node(4);
    TreeNode *n5 = create_node(5);
    TreeNode *n6 = create_node(6);
    TreeNode *n7 = create_node(7);

    // 连接父子关系
    n1->left = n2;
    n1->right = n3;

    n2->left = n4;
    n2->right = n5;

    n3->left = n6;
    n3->right = n7;

    printf("先序遍历结果：");
    pre_order(n1);
    return 0;
}
