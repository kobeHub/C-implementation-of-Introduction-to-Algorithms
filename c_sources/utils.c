#include "utils.h"

int Random_int(int start, int end){
  static int seed = 1;
  srand((int) time(NULL)*seed*seed);
  int res = end - start;
  seed += rand();
  return rand()%res;
}
