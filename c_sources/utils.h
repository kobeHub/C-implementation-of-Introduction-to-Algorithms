#include <stdio.h>
#include <stdlib.h>

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
