//刚才那个是原地反转，下面这种方式是反复头插实现的反转
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

//尾插创建链表
LNode* createList(int n)
{
    LNode *L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *tail = L;
    for(int i = 0; i < n; i++)
    {
        int val;
        printf("请输入第%d个数据:",i+1);
        scanf("%d",&val);
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = val;
        s->next = NULL;
        tail->next = s;
        tail = s;
    }
    return L;
}

//遍历打印链表
void TraverseList(LNode *L)
{
    LNode *p = L->next;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

//利用头插思想反转链表
int reverseList(LNode *L)
{
    if(L->next == NULL)
        return 0;

    LNode *p = L->next;
    L->next = NULL; //把原链表拆下来，虚拟头置空
    LNode *q;
    while(p != NULL)   //p会去遍历，所有节点处理完会是null
    {
        q = p->next;            //保存后面节点，p,q同步平移
        p->next = L->next;  //意思是每一个节点右端链接首元节点，
        L->next = p;         //虚拟头指向p左端，已经利用头插法把他夹住了
        p = q;              //p移动到下一个，马上下一个循环q同步平移进行下一轮头插
    }
    return 1;
}

int main()
{
    int n;
    printf("请输入节点个数n:");
    scanf("%d",&n);
    LNode *L = createList(n);
    printf("原链表：");
    TraverseList(L);

    reverseList(L);
    printf("反转链表：");
    TraverseList(L);
    return 0;
}
