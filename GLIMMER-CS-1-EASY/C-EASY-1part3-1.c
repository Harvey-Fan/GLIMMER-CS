#include <stdio.h>
double f(double x, int n){
    double r=1;
    for(int i=0;i<n;i++) r*=x;
    return r;
}
double Score(double s1,double s2,double s3){
    double avg=(s1+s2+s3)/3.0;
    double var=(f(s1-avg,2)+f(s2-avg,2)+f(s3-avg,2))/3.0;  //ps,avg是平均数，var是方差，用f求平方
    return 3*avg - var/3.0;
}
void sort3(double *a,double *b,double *c){
    double t;
    if(*a<*b){t=*a;*a=*b;*b=t;}
    if(*a<*c){t=*a;*a=*c;*c=t;}
    if(*b<*c){t=*b;*b=*c;*c=t;}
}
int main(){
    double a1,a2,a3,b1,b2,b3,c1,c2,c3;
    printf("输入小明三项成绩：");
    scanf("%lf %lf %lf",&a1,&a2,&a3);
    printf("输入小强三项成绩：");
    scanf("%lf %lf %lf",&b1,&b2,&b3);
    printf("输入小林三项成绩：");
    scanf("%lf %lf %lf",&c1,&c2,&c3);

    double ming=Score(a1,a2,a3);
    double qiang=Score(b1,b2,b3);
    double lin=Score(c1,c2,c3);

    sort3(&ming,&qiang,&lin);
    printf("综合成绩降序：%.2f %.2f %.2f\n",ming,qiang,lin);
    return 0;
}
