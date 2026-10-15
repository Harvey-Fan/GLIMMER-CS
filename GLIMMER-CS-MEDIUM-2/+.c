#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 将8位二进制字符串转换为浮点数的各个部分，拆解出符号位，阶码，尾数
void parseFloat(char* str, int* sign, int* exp, int* mant) {
    *sign = str[0] - '0';//ps '0'是48，'1'是49,起识别作用
    *exp = 0;
    *mant = 0;
    // 解析4位阶码 (第1到第4个字符)
    for (int i = 1; i <= 4; i++) {
        *exp = (*exp << 1) | (str[i] - '0');
    }
    // 解析3位尾数 (第5到第7个字符)
    for (int i = 5; i <= 7; i++) {
        *mant = (*mant << 1) | (str[i] - '0');
    }
}

// 将浮点数的各个部分格式化输出为8位二进制字符串
void formatFloat(int sign, int exp, int mant, char* out) {
    out[0] = sign + '0';
    for (int i = 1; i <= 4; i++) {
        out[i] = ((exp >> (4 - i)) & 1) + '0';
    }
    for (int i = 5; i <= 7; i++) {
        out[i] = ((mant >> (7 - i)) & 1) + '0';
    }
    out[8] = '\0';
}

int main() {
    char str1[10], str2[10], result[10];
    
    // 输入两个8位二进制字符串
    if (scanf("%s %s", str1, str2) != 2) {
        return 1;
    }

    int s1, e1, m1;
    int s2, e2, m2;
    
    parseFloat(str1, &s1, &e1, &m1);
    parseFloat(str2, &s2, &e2, &m2);

    // 1. 提取真实阶码和有效尾数
    int E1 = e1 - 7; // 偏置值为7
    int E2 = e2 - 7;
    
    // 加上隐藏的整数位1
    int M1 = m1 | 0x8; // 0x8 是 1000，即隐藏位1加上3位尾数
    int M2 = m2 | 0x8;

    // 2. 对阶 (向大阶看齐)
    int E = (E1 > E2) ? E1 : E2;
    
    // 将较小的阶码对齐到大阶码，右移尾数
    if (E1 < E) {
        M1 >>= (E - E1);
    } else if (E2 < E) {
        M2 >>= (E - E2);
    }

    // 3. 尾数相加
    int M = M1 + M2;

    // 4. 规格化与舍入 (向零舍入)
    // 假设相加后尾数的有效位为 M (可能变成5位，如 1xxxx 或 10xxx)
    // 如果 M >= 16 (即 10000)，说明发生了进位，需要右移，同时阶码加1
    if (M >= 16) {
        M >>= 1;    // 右移一位，直接舍去最低位（向零舍入）
        E += 1;     // 阶码加1
    }
    
    // 本题默认不会出现溢出，因此不需要额外的溢出判断
    int out_exp = E + 7;

    // 将结果转换回8位二进制字符串输出
    formatFloat(0, out_exp, M & 0x7, result); // 符号位默认0，M只保留低3位尾数
    
    printf("%s\n", result);

    return 0;
}