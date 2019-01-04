#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define MIN_FIL  0.000000001
#define loop_time 1000

typedef float (*Myfun)(float);
typedef double (*Dfun)(double);

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

    return 1/y;
}

float sqrt_qr(float num) {
  float half = 0.5f * num;
  int i = *(int*) &num;

  i = 0x5f375a86 - (i >> 1);
  num = *(float*) &i;
  num = num*(1.5f-half*num*num);
  num = num*(1.5f-half*num*num);
  num = num*(1.5f-half*num*num);

  return 1/num;
}

float run(Myfun func, int num){
    double start, end;
    float res;
    start = clock();
    for(int i = 0; i<loop_time; i++)
        res = func(num);
    end = clock();
    printf("Use time:%fs\n", (end-start)/CLOCKS_PER_SEC);
    return res;
}


// Binary search to compute sqrt
double sqrt_bs(double value) {
  double i = 0;
  double j = value / 2 + 1;
  while (j - i >= MIN_FIL) {
    double mid = (i + j) / 2;
    double cul = mid * mid;
    if (cul == value)
      return mid;
    else if (cul < value)
      i = mid + 1;
    else
      j = mid -1;
  }
  return j;
}

// Newton method to compute the sqrt
double sqrt_nt(double num) {
  if (num <= 0)
    return 0;
  double res, last_res;

  res = num;
  do {
    last_res = res;
    res = (res + num / res) / 2;
  } while (fabs(last_res - res) > MIN_FIL);

  return res;
}

double run_double(Dfun func, double num) {
  double start, end, sqrt;
  start = clock();
  for (int i = 0; i < loop_time; i++)
    sqrt = func(num);
  end = clock();
  printf("Sqrt %f: %f\t", num, sqrt);
  printf("Use time:%fs\n", (end-start) / CLOCKS_PER_SEC);
  //return sqrt;
}

// Run magic for float
float run_float(Myfun func, float num) {
  double start, end;

  float sqrt;
  start = clock();
  for (int i = 0; i < loop_time; i++)
    sqrt = func(num);
  end = clock();
  printf("Sqrt %f: %f\t", num, sqrt);
  printf("Use time:%fs\n", (end-start) / CLOCKS_PER_SEC);
  //return sqrt;
}

int main(){
    float a = run(q_rsqrt_unique, 16.0);
    float b = run(q_rsqrt_normal, 16.0);
    printf("reciprocal of the sqrt(%f): %f %f\n", 16.0, a, b);

    printf("Test for the time of compute sqrt:\n");
    printf("System method:\n");
    run_double(sqrt, 65535);
    printf("Binary search method:\n");
    run_double(sqrt_bs, 65535);
    printf("Newton method:\n");
    run_double(sqrt_nt, 65535);
    printf("Magical method:\n");
    run_float(q_rsqrt_unique, 65535);
}
