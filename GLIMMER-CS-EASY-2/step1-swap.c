#include <stdio.h>

void swap(int *a, int *b){

    int tmp = *a;  
    *a = *b;      
    *b = tmp;      
}

int main(void)
{
    int m = 10, n = 20;
    printf("交换前:m=%d, n=%d\n", m, n);

    swap(&m, &n);  // 传入变量的地址

    printf("交换后:m=%d, n=%d\n", m, n);
    return 0;
}
