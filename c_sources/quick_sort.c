#include "utils.h"
#include <stack>


/***************************************************************
 *Copyright (c) 2018 http://www.innohub.top/ All rights reserved
 *Author: Inno Jia
 * Date: 2018-10-20
 *Decription: 实现快速排序的演示程序，包含利用递归方式，以及
 ×            非递归方式实现的快速排序算法，并且进行性能比较
 *
 **************************************************************/
void print(int* data, int len){
  if(len){
    for(int i = 0; i < len; i++)
      printf("%d ", data[i]);
    printf("\n");
  }
  else
    printf("None array\n");
}

typedef void (*Func) (int*, int, int);

/**************************************************************
 * Function: Partion
 * Description: divide the array and sort it by the original
 *              address.
 *              将数组划分为4个部分，以最后一个元素作为主元x，
 *              对于任意一个元素只有以下情况：
 *              1. 位于p~i 小于x
 *              2. 位于i+1~j-1 大于x
 *              3. 位于j~r-1 暂未比较
 *              4. 位于r 等于x
 ************************************************************/
int partion(int* data, int low, int high){
  int x = data[high];
  int j, i = low - 1;
  for(j = low; j < high; j++){
    if(data[j] <= x){
      i++;
      SWAP(data[i], data[j]);
    }
  }
  SWAP(data[i+1], data[high]);
  return i+1;
}


/***********************************************************
 * Recursive solution of quick sort
 * *********************************************************/
void quick_sort(int* data, int low, int high){
  if(low < high){
    int q = partion(data, low, high);
    quick_sort(data, low, q-1);
    quick_sort(data, q+1, high);
  }
}

/**********************************************************
 * None recursive solution of quick sort
 * *********************************************************/
void quick_sort_non(int* data, int low, int high){
  if(low >= high)
    printf("Array overflow\n");

  // init the buffer
  std::stack<int> buffer;
  buffer.push(low);
  buffer.push(high);

  int left, right, mid;
  while(!buffer.empty()){
    right = buffer.top();
    buffer.pop();
    left = buffer.top();
    buffer.pop();

    mid = partion(data, left, right);
    if(mid-1 > left){
      // Push the left part array args into buffer
      buffer.push(left);
      buffer.push(mid-1);
    }

    if(mid+1 < right){
      buffer.push(mid+1);
      buffer.push(right);
    }
  }
}

void run(Func myFun, int* data, int low, int high){
  double start, end;
  start = clock();
  myFun(data, low, high);
  end = clock();
  printf("Run time:%fs\n", (end-start)/CLOCKS_PER_SEC);
}

inline void init_data(int* data, int len){
  for(int i = 0;i < 10;i++)
    data[i] = Random_int(0, 100);
}

int main(){
  int* data = (int*)malloc(sizeof(int)*10);
  LOG("The initial array:");
  init_data(data, 10);
  print(data, 10);
  LOG("Using recursive quick sort:");
  run(quick_sort, data, 0, 9);
  print(data, 10);
  init_data(data, 10);
  LOG("Using none recursive:");
  print(data, 10);
  run(quick_sort_non, data, 0, 9);
  print(data, 10);
  free(data);
}

