#include "utils.h"

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

typedef int (*Func) (int*, int, int);

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

int main(){
  int* data = (int*)malloc(sizeof(int)*10);
  for(int i = 0;i < 10;i++)
    data[i] = Random_int(0, 100);
  LOG("The initial array:");
  print(data, 10);
  quick_sort(data, 0, 9);
  LOG("After quick sort:");
  print(data, 10);
  free(data);
}

