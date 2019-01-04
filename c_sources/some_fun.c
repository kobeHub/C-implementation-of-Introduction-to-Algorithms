#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


typedef float (*Myfun)(float);

float q_rsqrt_normal(float num){
    //printf("The function is:%s\n", __FUNCTION__);
    return (float)1.0/sqrtf(num);
}

//求平方根倒数的一种方式,精确度0.001
float q_rsqrt_unique(float num){
    //printf("The function is:%s\n", __FUNCTION__);
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = num * 0.5F;
    y = num;
    i = *(long*) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y = y*(threehalfs - (x2 * y *y));

    return y;
}

float run(Myfun func, int num){
    double start, end;
    float res;
    start = clock();
    for(int i = 0; i<100; i++)
        res = func(num);
    end = clock();
    printf("Use time:%fs\n", (end-start)/CLOCKS_PER_SEC);
    return res;
}


// Binary search to compute sqrt
int sqrt_b(int value) {
  long long i = 0;
  long long j = value / 2 + 1;
  while (i <= j) {
    long long mid = (i + j) / 2;
    long long cul = mid * mid;
    if (cul == value)
      return mid;
    else if (cul < value)
      i = mid + 1;
    else
      j = mid -1;
  }
  return j;
}

int main(){
    float a = run(q_rsqrt_unique, 16.0);
    float b = run(q_rsqrt_normal, 16.0);
    printf("reciprocal of the sqrt(%f): %f %f\n", 16.0, a, b);

    printf("Use binary search to compute sqrt:\n");
    printf("Test for int: 25, %d\n", sqrt_b(25));
}
