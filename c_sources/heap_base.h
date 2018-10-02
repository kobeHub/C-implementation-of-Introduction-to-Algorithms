#ifndef __HEAP_BASE_H_
#define __HEAP_BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEFT(i) i<<1
#define RIGHT(i) (i<<1)+1
#define PARENT(i) i>>1

#define SWAP(a, b) do{ \
    a = a^b; b = a^b; a = a^b; \
}while(0);

#define DEBUG_LOG(module) fprintf(stderr, "[+]Debug: "#module"\n")
#define ERROR_LOG(module) fprintf(stderr, "[+]Error: "#module"\n")

void heapfy(int *data, int index, int heap_size);
void MaxHeap(int *data, int length);
void heap_sort(int *data, int length);
int Random(int start, int end);



#endif
