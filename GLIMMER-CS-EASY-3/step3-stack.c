//栈放和取的动态过程有点难理解
#include <stdio.h>
#include <stdlib.h>

// 二叉树节点定义
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


//==================== 栈结构（题目给的栈代码）====================
//定义栈结构体，存放二叉树节点指针
typedef struct Stack {
    TreeNode **arr; //二级指针，arr 指向一块数组空间，数组里面每一项都是TreeNode*（二叉树节点的地址）简单说：数组用来存放节点指针。
    int top;//栈顶下标，top=-1是栈空
    int capacity;
} Stack;

//传入容量，返回一个栈的指针
Stack *createStack(int capacity) {  
    Stack *stack = malloc(sizeof(Stack));
    stack->arr = malloc(sizeof(TreeNode *) * capacity);  //结构体里面的 arr 成员，单独开一块堆内存。空间大小 = 单个 TreeNode 指针的大小 × 容量。这就是存放节点指针的数组。
    stack->top = -1;//初始化栈为空                       //空间大小 = 单个 TreeNode 指针的大小 × 容量。这就是存放节点指针的数组。
    stack->capacity = capacity;
    return stack;
}
//判断栈是否为空函数，
int isEmpty(Stack *stack) {
    return stack->top == -1;//空则返回1，有则返回0
}

//入栈函数，把node压进去
void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {  //数组下标从0开始，容量为capacity，故下标到capacity-1就是最后一个
        return;     //栈满，直接退出，不存入
    }
    stack->arr[++stack->top] = node;   //// ++top：top先加1，再把node放到arr[top]位置
}                                      //eg top=-1 → ++top 变成 0，arr[0]=node，第一个元素存入,故初始top为1


//出栈，pop出栈顶元素
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {  //若栈空
        return NULL;
    }
    return stack->arr[stack->top--];// 
}                                   //例子：top=0，取 arr [0] 返回，然后 top 变成 - 1，注意和push顺序不太一样


// 迭代前序遍历，栈是后进先出，为了实现根左右，必须先压右孩子，再压左孩子
void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;      //空树直接回
    Stack *st = createStack(100);//创建栈，最多放100个节点指针，st是栈的指针，注意此时！栈初始状态：top=-1，数组空。
    push(st, root);/*调用 push，把根节点 1 的地址压进栈。
执行 push 内部：top=-1 → ++top 变成 0，arr[0]=节点1
栈现在：[1]，top=0*/


    while (!isEmpty(st))   //如果栈不为空，也就是只要栈里面还有元素，循环就不停
    {
        TreeNode *cur = pop(st);//弹出栈顶节点，cur拿到这个节点地址，这里是关键的弹出操作
        printf("%d ", cur->data);//打印，这里是一个个根节点，因为每次pop会让top-1，故每次

        // 栈后进先出：先压右，再压左，保证左先弹出
        if (cur->right != NULL)
        {
            push(st, cur->right);
        }
        if (cur->left != NULL)
        {
            push(st, cur->left);
        }
    }
}
//这里有点难理解，举个例子，
/*      1
      /   \
     2     3
    / \   / \
   4   5 6   7
   对这样的树，目标输出：1 2 4 5 3 6 7
   初始：把根1压栈，栈：[1]

第 1 次循环

栈不为空，pop拿出1
打印 1
节点 1 的右孩子是3，先压右 → 栈[3]
节点 1 的左孩子是2，再压左 → 栈[3, 2]


 栈里面现在：3 先放，2 后放。下一次 pop 拿的是 2！
 这样才能实现根左右。

 第 2 次循环

pop 拿出2
打印 1 2
节点 2 右孩子是5，压 5 →栈[3,5]
节点 2 左孩子是4，压 4 →栈[3,5,4]


栈：3,5,4。最后放的是 4，下一次拿 4

 第 3 次循环

pop 拿出4
打印 1 2 4
4 没有左右孩子，不压任何东西。栈：[3,5]

 第 4 次循环

pop 拿出5
打印 1 2 4 5
5 没有左右孩子。栈：[3]

第 5 次循环

pop 拿出3
打印 1 2 4 5 3
节点 3 右孩子 7，压 7 →栈[7]
节点 3 左孩子 6，压 6 →栈[7,6]


 栈：7，6，下一次拿 6

 第 6 次循环

pop 拿出6
打印 1 2 4 5 3 6
6 无孩子，栈：[7]

第 7 次循环

pop 拿出7
打印 1 2 4 5 3 6 7
7 无孩子，栈空。

栈空，循环结束。




conclusion：我的理解是：pop和push是一个动态过程，故要改动top以实现放和拿的动态过程
*/
//递归前序（原来的，对照一下），显然结果是一样的
void pre_order(TreeNode *root)
{
    if (root == NULL) return;
    printf("%d ", root->data);
    pre_order(root->left);
    pre_order(root->right);
}

//建树函数
// 输入样例：1 2 4 # # 5 # # 3 6 # # 7 # #
//建树是一样的
TreeNode* create_tree()
{
    int val;
    char ch;
    if(scanf("%d", &val) == 1)
    {
        TreeNode* node = malloc(sizeof(TreeNode));
        node->data = val;
        node->left = create_tree();
        node->right = create_tree();
        return node;
    }
    else
    {
        scanf("%c", &ch); // 读取 #
        return NULL;
    }
}

int main()
{
    printf("请输入二叉树序列，# 代表空节点\n");
    TreeNode *root = create_tree();

    printf("递归前序遍历结果：");
    pre_order(root);
    printf("\n");

    printf("迭代栈实现前序遍历结果：");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
