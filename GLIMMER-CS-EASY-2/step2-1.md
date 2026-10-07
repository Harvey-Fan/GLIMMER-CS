# Step2. 链操作
## 参考资料
1. B站代码随想录 链表专题
2. 浙大MOOC《数据结构》
## 1. 请对比链表和数组的存储，讲讲链表和数组的区别
## PS:使用了AI工具查询
1. **内存存储**
数组：占用**连续**的一块内存空间。
单向链表：节点在内存中**分散存放**，依靠节点内部指针域保存下一个节点的地址，串联所有节点。
2. **访问方式**
数组：支持随机访问，直接通过下标访问元素，访问速度快。
链表：**不支持随机访问**，访问第n个元素必须从头节点开始依次遍历。
3. **插入、删除**
数组：在中间位置插入或删除元素，需要移动后面大量元素，开销大。
链表：插入、删除只需要修改相关指针，不需要移动大量数据，开销小。
4. **长度特性**
数组：定义后长度固定，不能动态增减。
链表：可以动态malloc申请、free释放节点，长度灵活。

## 2. 简述单向链表节点的结构特点。定义一个只存储一个整数的单向链表节点。

单向链表节点包含两部分：

**数据域**：存放数据，本题存放int整数。
**指针域**：保存**下一个节点的地址**。单向链表只能顺着指针向后遍历，无法直接回到上一个节点。

```
typedef struct Node {
    int data;               // 数据域，存储整数
    struct Node *next;      // 指针域，保存下一个节点地址
} Node;
```

## 3. 添加元素（头插法）

需求：新节点A指向原来头节点，头指针指向A。

```
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 头插，head传入头指针的地址
void addHead(Node **head, int n)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = n;
    newNode->next = *head;
    *head = newNode;
}
```

## 4. 查找元素：查找第n位的元素

```
Node* findNth(Node *head, int n)
{
    Node *p = head;
    int cnt = 0;
    while(p != NULL)
    {
        if(cnt == n)
        {
            return p;
        }
        p = p->next;
        cnt++;
    }
    return NULL;
}
```

## 5. 删除和更改

### 修改第n个节点的数据

```
int modifyNth(Node *head, int n, int newData)
{
    Node *p = findNth(head, n);
    if(p == NULL) return 0;
    p->data = newData;
    return 1;
}
```

### 删除第n个节点

```
int deleteNth(Node **head, int n)
{
    if(*head == NULL) return 0;
    // 删除头节点
    if(n == 0)
    {
        Node *del = *head;
        *head = del->next;
        free(del);
        return 1;
    }
    // 寻找前驱节点 n-1
    Node *pre = findNth(*head, n - 1);
    if(pre == NULL || pre->next == NULL) return 0;
    Node *del = pre->next;
    pre->next = del->next;
    free(del);
    return 1;
}
```

## 6. 反转函数

```
Node* reverseList(Node *head)
{
    Node *pre = NULL;
    Node *cur = head;
    Node *next;
    while(cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}
```

## 完整测试main函数

```
// 打印链表辅助函数
void printList(Node *head)
{
    Node *p = head;
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(void)
{
    Node *head = NULL;
    addHead(&head,10);
    addHead(&head,20);
    addHead(&head,30);
    printf("原始链表：");
    printList(head);

    modifyNth(head,1,99);
    printf("修改后：");
    printList(head);

    deleteNth(&head,0);
    printf("删除后：");
    printList(head);

    head = reverseList(head);
    printf("反转链表：");
    printList(head);
    return 0;
}
```


