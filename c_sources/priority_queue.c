#include <limits.h>
#include "heap_base.h"
#include "utils.h"

/****************************************************************
 *Copyright (c) 2018 http://www.innohub.top All rights reserved
 *Auther: Inno Jia
 *Date: 2018-09-13
 *Decription: 最大堆实现的最大优先队列
 *            最大堆是一种用来维护一组元素的集合的数据结构，
 *            其中每个元素都有一个对应的值，即关键字(key)
 *一个最大优先队列支持以下操作:
 *INSERT(S, x): 把元素x插入集合S中去
 *MAXMUM(S): 返回集合中具有最大键的元素
 *EXTRACT-MAX(s): 去掉集合中具有最大键值的元素
 *INCREASE-KEY(S,x,k): 将x的关键字增加到k,假设k的值不小于x
 ****************************************************************/
int maximum(int *data){
    return data[0];
}

int extract_max(int *data, int heap_size){
    if(heap_size < 1)
        ERROR("Heap underflow!");
    int max = data[0];
    SWAP(data[0], data[heap_size-1]);
    heap_size = heap_size - 1;
    heapfy(data, 1, heap_size);
    return max;
}

int increase_key(int *data, int index, int key){
    if(key < data[index-1])
        ERROR("The value is smaller than previous!");
    data[index-1] = key;
    while(index > 1 && data[PARENT(index)-1] < key){
        SWAP(data[PARENT(index)-1], data[index-1]);
        index = PARENT(index);
    }
}

// Insert the value of key into the priority
// by insert a -INT_MIN value and increase it
// to key.
int insert(int *data,int key, int heap_size){
    heap_size += 1;
    data[heap_size-1] = INT_MIN;
    increase_key(data, heap_size, key);
}

int main(){
    int *data = (int*)malloc(sizeof(int)*10);
    for(int i = 0; i < 10; i++)
        data[i] = Random(0, 100);
    print(data, 10);
    MaxHeap(data, 10);
    LOG("The test of max priority queue:");
    LOG("Maximum: %d", maximum(data));
    LOG("Extract maximum:%d", extract_max(data, 10));
    print(data, 9);
    LOG("Increase 7th element to 50:");
    increase_key(data, 7, 50);
    print(data, 9);
    LOG("Insert 20:");
    insert(data, 20, 9);
    print(data, 10);
    free(data);
}
