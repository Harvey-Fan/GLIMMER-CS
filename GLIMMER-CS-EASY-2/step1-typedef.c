#include <stdio.h>
typedef struct {
    char name[10];
    char gender;
    int age;
    double height;
} PerInfo;

int main(void)
{
    printf("结构体大小：%zu\n", sizeof(PerInfo));   //printf sizeof 要用%zu
    return 0;
}
