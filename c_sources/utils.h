#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// define the Log macro
#ifndef LOG
#define LOG(format, args...) fprintf(stdout, "[File:%s, line:%d]"format"\n", __FILE__ , __LINE__, ##args)
#endif

// define the error macro with a return value of int
#ifndef ERROR
#define ERROR(format, args...) do{ \
  fprintf(stderr, "Error:(%s:%d)"format"\n", __FILE__, __LINE__, ##args); \
  return -1; \
}while(0);
#endif


/*
 * 需要注意定义宏时尽可能定义通用宏，使用位运算
 * 进行swap定义时可能会出错*/
#ifndef SWAP
#define SWAP(x,y) do { \
  unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
  memcpy(swap_temp, &y, sizeof(x)); \
  memcpy(&y, &x, sizeof(x)); \
  memcpy(&x, swap_temp, sizeof(x)); \
}while(0);
#endif

int Random_int(int start, int end);
