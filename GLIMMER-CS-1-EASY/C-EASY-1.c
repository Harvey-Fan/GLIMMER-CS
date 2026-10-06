#include <stdio.h>
int main(void)
{
    char name[20];
    int age;
    char choice;
    int count = 0;

    do
    {
        printf("请输入姓名：");
        scanf("%s", name);
        printf("请输入年龄：");
        scanf("%d", &age);
        count++;
        printf("姓名：%s,年龄：%d\n", name, age);
        printf("是否继续输入? a继续 / b退出:");
        scanf(" %c", &choice);
    } while (choice == 'a');

    printf("本次一共录入 %d 组数据\n", count);
    return 0;
}//ps 在运行时发现中文在终端显示的是乱码，通过修改settings.json,改为了UTF-8编码，每次运行会Active code page: 65001