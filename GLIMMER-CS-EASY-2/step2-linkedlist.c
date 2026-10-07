//这个程序是用 尾插法 实现可添加n个元素的链表，查找元素，遍历打印每个数据，删除节点和修改节点，均考虑了特殊情况
//ps 注释是我自己的理解，头插法和反转函数在下一个程序中查看！
#include <stdio.h>
#include <stdlib.h>
//定义
typedef struct LNode{    //数据加指针打包叫做LNode 
    int data;           //数据域
    struct LNode *next; //指针域   //ps：此时改名还没生效
} LNode;


//查找函数
int findNode(LNode *L, int n1)
{
    LNode *p = L->next; // p从首元节点开始遍历，头指针L保持不动
    int cnt = 1;        // 首元节点算作第1个，虚拟头结点不计入
    while(p != NULL)    //前提是不是空
    {
        if(p->data == n1)
        {
            return cnt; // 找到第一个匹配，直接返回序号
        }
        p = p->next;  //这里和遍历输出的思路很像，
        cnt++;
    }
    return 0; // 遍历完没找到，返回0 false
}


// 修改函数
int modifyNode(LNode *L, int n, int new_val)
{
    LNode *p = L->next;  //先指向首元
    int cnt = 1;
    while(p != NULL && cnt < n)
    {
        p = p->next;   //指向第n元时，cnt+1=n,循环结束
        cnt++;
    }
    if(p == NULL)
        return 0;  //res=0,
    p->data = new_val;
    return 1;
}

//删除函数
int deleteNode(LNode *L, int n)
{
    if(n <= 0)
        return 0;  //这个情况要考虑

    LNode *p = L; // 让p指向虚拟头结点，而不是LNode *p = L->next;了
    int cnt = 0;

    while(p->next != NULL && cnt < n - 1)
    {
        p = p->next;//指向下一个
        cnt++;
    }
                               //结束后是指向第n-1个
    if(p->next == NULL)
        return 0;   //上界

    LNode *q = p->next;    //q指向第n个
    p->next = q->next;     //这里关键，直接跳过q指向第n+1个
    free(q);               //再把q节点给释放了
    return 1;
}

//遍历输出链表函数,会被多次调用//
void TraverseList(LNode *L)
{
    LNode *p = L->next;
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//尾插法创建含数据列表
int main(void)
{
    LNode *L = (LNode*)malloc(sizeof(LNode));   //申请堆内存，不会被free，L指向一个虚拟头节点，可视作两部分的方框
    L->next = NULL; // malloc总是和->并存，表示具体改哪部分的地址，ps：虚拟头节点不存数据，只是为了方便
    LNode *tail = L; // 新建指针，同样指向那个头节点
    int n;
    printf("请输入节点数量：");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        // 新建一个结点并读入数据
        LNode *s = (LNode*)malloc(sizeof(LNode));
        printf("请输入第%d个数据:", i + 1);
        scanf("%d", &s->data);
        s->next = NULL; // 这部分完全一样，又建了个结点
        tail->next = s; // 关键：让next指向节点s
        tail = s;       // 再让尾指针指向节点s
    } // 重复操作

    // 遍历输出数据，Ps：跳过虚拟头结点！从后接的首元结点开始！
    printf("\n你输入的数据(从首元节点开始):");
    TraverseList(L);

    // 查找功能
    int target;
    printf("\n请输入想要查找的数字:");
    scanf("%d", &target);
    int result = findNode(L, target);
    if(result != 0)
    {
        printf("找到了 %d,它是链表中第 %d 个节点\n", target, result);
    }
    else
    {
        printf("链表中没有 %d 这个数据\n", target);
    }


    //修改功能
    int n2, new_val;
    int res;
    printf("\n请输入要修改第几个节点:");
    scanf("%d", &n2);
    printf("请输入修改后的值：");
    scanf("%d", &new_val);
    res = modifyNode(L, n2, new_val);

    if(res == 1)
    {
        printf("修改成功！链表现在：");
        TraverseList(L);  //调用下遍历函数
    }
    else
    {
        printf("不能改，节点不存在\n");
    }

    // 删除功能
    int choice;
    printf("\n是否要删除节点?(1: 是  0: 否):");
    scanf("%d", &choice);

    if(choice == 1)
    {
        int delPos;
        printf("删除哪个节点：");
        scanf("%d", &delPos);

        int deleteRes = deleteNode(L, delPos);
        if(deleteRes == 1)
        {
            printf("删除成功！删除后链表是：");
            TraverseList(L);
        }
        else
        {
            printf("无对应节点\n");
        }
    }
    else
    {
        printf("不删除\n");
    }

    return 0;
}
