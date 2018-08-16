#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//生成指定范围的随机数
int Random(int beg, int end){
    static unsigned int seed = 0;
    seed++;
    srand((int)time(NULL)+seed*seed);
    int residual = end - beg;
    return (rand()%residual + beg);
}

double RandomDouble(int beg, int end){
    //srand((int)time(0));
    static unsigned int seed = 0;
    seed++;
    srand((int)time(NULL)+seed*seed);

    int res = end - beg;
    return beg+res*(rand()/(RAND_MAX+1.0));
}

int main(){
    int i;
   // srand((int)time(0));
    for(i = 0; i< 5; i++)
        printf("%d %f\n", Random(1, 5), RandomDouble(1, 5));   // printf("\n%ld %d ", random(), RAND_MAX);
    return 0;
}
