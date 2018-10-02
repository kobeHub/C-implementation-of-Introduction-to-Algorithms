#include "heap_base.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define LEFT(i) i<<1
//#define RIGHT(i) (i<<1) + 1
//#define PARENT(i) i>>1
//#define SWAP(a, b) do{ \
//    a = a^b; b = a^b; a = a^b; \
//}while(0);
//#define DEBUG_LOG(module) fprintf(stderr, "[+]Debug: "#module"\n")
//#define ERROR_LOG(module) fprintf(stderr, "[+]Error: "#module"\n")
//#if !defined DEBUG_VERSION \
//    printf("Final version\n")
//#endif

/*堆排序的额演示程序:
 * 采用最大堆的数据结构,使用数组存储,堆的大小为实际存储元素的数目,heap_size
 * 数组表示最大堆,叶节点为(n/2+1, n)
 * 采用heapfy()将子树构建为最大堆,然后从最后一个非叶节点开始,一次向上构建最大堆
 *
 *
 * 最大堆排序:
 * 1.每次将根节点与最后一个叶节点交换
 * 2.heap_size - 1
 * 3.heapfy(1) 重新构建为最大堆
 *
 * 使用宏定义的位操作符获取左右子*/
void print(int*, int);

void heapfy(int *data, int index, int heap_size){
    int left = LEFT(index);
    int right = RIGHT(index);

    int largest;
    if(left <= heap_size && data[left-1] > data[index-1])
        largest = left;
    else
        largest = index;
    if(right <= heap_size && data[right-1] > data[largest-1])
        largest = right;
    if(largest != index){
        SWAP(data[index-1], data[largest-1]);
        heapfy(data, largest, heap_size);
    }
}

//从最后一个非叶节点开始,使之成为一个最大堆子树.合并到第一个节点时即组成最大堆
void MaxHeap(int *data, int length){
    int last_root = length/2;
    for(int i = last_root; i>0; i--)
        heapfy(data, i, length);
    DEBUG_LOG(Max heap initializer:);
    print(data, length);
}

//每次将首尾值互换,然后岁根节点进行最大堆化
void heap_sort(int *data, int length){
    int heap_size = length;
    MaxHeap(data, length);
    while(heap_size != 1){
        SWAP(data[0], data[heap_size-1]);
        heap_size --;
        heapfy(data, 1, heap_size);
    }
}

void print(int *data, int length){
    for(int i =0;i<length; i++)
        printf("%d ", data[i]);
    printf("\n");
}

int Random(int start, int end){
    static int seed = 1;
    srand((int)time(NULL)*seed*seed);
    int res = end - start;
    seed += rand();
    return rand()%res;
}

int main(){
    int *data = (int*)malloc(sizeof(int)*9);
    for(int i =0;i<9;i++)
        data[i] = Random(0, 100);
    print(data, 9);
    heap_sort(data, 9);
    DEBUG_LOG(After heap_sort);
    print(data, 9);
    free(data);
}
