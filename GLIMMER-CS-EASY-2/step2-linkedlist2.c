//这里是头插法加反转函数，已完整按照题意完成
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode  // 同
{
    int data;           
    struct LNode *next; 
} LNode;

void TraverseList(LNode *L)  // 同
{
    if(L == NULL)
    {
        printf("链表为空\n");
        return;
    }

    LNode *p = L->next;  
    if(p == NULL)
    {
        printf("链表为空\n");
        return;
    }

    while(p != NULL)
    {
        printf("%d ", p->data);  
        p = p->next;              
    }
    printf("\n");
}

LNode *CreateHeadList(int n)  // 头插法创建链表，头插法会让新结点放在前面，这是和上个程序不同的
{
    LNode *L = (LNode *)malloc(sizeof(LNode)); 
    if(L == NULL)
    {
        printf("内存分配失败\n");
        exit(1);             //提前终止程序
    }                //ps 这是ai说还要考虑的，规范，
    L->next = NULL;  // 虚拟头结点不存数据，只作为链表入口

    if(n <= 0)
    {
        return L;  // 节点数为0或负数时，返回空链表
    }

    for(int i = 0; i < n; i++)
    {
        int value;
        printf("请输入第 %d 个数据：", i + 1);  // 输入每个结点的数据
        if(scanf("%d", &value) != 1)
        {
            printf("输入格式错误，程序退出\n");   //输入格式也要考虑，666
            free(L);  //已经用了堆空间了要free掉
            exit(1);
        }

        LNode *s = (LNode *)malloc(sizeof(LNode));  // 新建结点
        if(s == NULL)
        {
            printf("结点分配失败\n");
            exit(1);
        }

        s->data = value;      // 写入数据
        s->next = L->next;    // 新结点接到头结点后面
        L->next = s;          // 头结点指向新结点，完成头插
    }

    return L;
}

void ReverseList(LNode *L)  // 反转链表：每次把当前结点插入到头结点之后，形成新头
{
    if(L == NULL || L->next == NULL || L->next->next == NULL)  // 空表或只有一个结点不需要反转
    {
        return;
    }

    LNode *beg = L->next;  // beg 指向原链表的第一个结点

    while(beg != NULL && beg->next != NULL)  // 只要还没到链表尾，就继续处理
    {
        LNode *end = beg->next;          // end 指向当前结点的下一个结点
        beg->next = end->next;           // 连：把当前结点从原链中断开
        end->next = L->next;             // 掉：让 end 指向原头结点之后
        L->next = end;                   // 接：把 end 插到虚拟头结点后面
    }
}

void FreeList(LNode *L)  // 释放链表中的所有结点，避免内存泄漏
{
    if(L == NULL)
    {
        return;
    }

    LNode *p = L->next;  // 从首元结点开始释放
    while(p != NULL)
    {
        LNode *q = p;    // 保存当前结点
        p = p->next;     // 指向下一个结点
        free(q);         // 释放当前结点
    }
    free(L);  // 最后释放虚拟头结点
}



//main函数藏在这
int main(void)
{
    int n;
    printf("请输入链表节点个数：");
    if(scanf("%d", &n) != 1)
    {
        printf("输入错误，程序退出\n");
        return 1;
    }

    if(n < 0)  // 边界情况：节点个数不能为负数
    {
        printf("节点个数不能为负数\n");
        return 1;
    }

    LNode *L = CreateHeadList(n);       // 建立链表

    printf("原链表：");
    TraverseList(L); 
    ReverseList(L);  // 调用反转函数
    printf("反转后链表：");
    TraverseList(L);  
    FreeList(L);  // 释放内存
    return 0;
}
