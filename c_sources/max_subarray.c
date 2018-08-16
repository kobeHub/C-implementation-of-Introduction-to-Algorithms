#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <time.h>

typedef int* (*MyFunc)(int*, int, int);//定义函数指针，用于选择待执行的算法
/*求解最大子数组的过程化demo
 * 使用分治法，将原数组分为左数组以及右数组，最大子数组一定位于
 * 左数组，右数组或者跨越左右数组
 * 记最大子数组的上下索引为i, j*/


/*找出跨越左右数组的最大子数组，该数组由两部分组成：
 * A[i...middle]  A[middle...j]
 * 需要 Θ (N)的时间复杂度*/
 int* find_max_subarray_cross_middle(int* data, int low, int middle, int high){
    int left_sum = -INT_MAX;
    int right_sum = -INT_MAX;
    int *index_and_sum = (int*)malloc(3*sizeof(int));//存放最大子数组的index以及和

    int i, max_left, max_right;
    int sum = 0;
    for(i=middle;i>=low;i--){
        sum += data[i];
        if(left_sum<sum){
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;
    for(i = middle+1; i<=high; i++){
        sum += data[i];
        if(right_sum<sum){
            right_sum = sum;
            max_right = i;
        }
    }

    index_and_sum[0] = max_left;
    index_and_sum[1] = max_right;
    index_and_sum[2] = left_sum + right_sum;
    return index_and_sum;
}

int* max_subarray(int* data, int low, int high){
    int *result = (int*)malloc(sizeof(int)*3);//存放返回值
    int middle = (low+high)/2;

    if(low == high){
        result[0] = low;
        result[1] = high;
        result[2] = data[low];
        return result;
    }

    int *left, *cross, *right;
    left = max_subarray(data, low, middle);
    right = max_subarray(data, middle+1, high);
    cross = find_max_subarray_cross_middle(data, low, middle, high);

    if(left[2] > right[2] && left[2] > cross[2])
        return left;
    else if(right[2] > left[2] && right[2] > cross[2])
        return right;
    else if(cross[2] > left[2] && cross[2] > right[2])
        return cross;
}

//一个不需要递归分治的最大子数组算法
//通过找到A[1..j]的最大子数组，增加一个元素后，最大子数组只有两种可能
//A[1..j]的最大子数组，或者A[i..j+1]的最大子组
//假设A[1..j]的最大子组为[k,l] 那么新的最大子组如果与原来不同
//上界一定包含j+1,若A[j+1]<0,那么下界一定不会小于k
int* max_subarray_normal(int *data, int low, int high){
    int *result = (int*)malloc(sizeof(int)*3);
    //初始化最大子组为第一个元素
    int max_sum = data[low];
    int left_index = low, right_index = low;
    int left_index_pre;//至关重要的一步，记录每次内循环前的左标，防止在有多个正数相邻，对左标的破坏

    int sum;
    for(int i=low+1;i<=high;i++){
        sum = 0;
        left_index_pre = left_index;
        for(int j = i;j>=left_index_pre;j--){
            sum += data[j];
            if(sum > max_sum){
                max_sum = sum;
                left_index = j;
                right_index = i;
                //printf("%d %d\n", i, j);
            }
        }
    }

    result[0] = left_index;
    result[1] = right_index;
    result[2] = max_sum;
    return result;
}

int* run(MyFunc func, int* data, int low, int high){
    double start, end;
    start = clock();
    int *p = func(data, low, high);
    end = clock();
    printf("Run time:%fs\n", (end-start)/CLOCKS_PER_SEC);
    return p;
}

int main(int argc, char *argv[]){
    int data[] = {1, -2, 3, 4, -6, 7, -2, 5};
    int *result1, *result2;

    result1 = run(max_subarray, data, 0, 7);
    result2 = run(max_subarray_normal, data, 0, 7);
    printf("The array is:\n");
    for(int i=0; i<8;i++)
        printf("%d ", data[i]);
    printf("\nDivide and conquer: A[%d, %d] = %d", result1[0]+1, result1[1]+1, result1[2]);
    printf("\nLinear method: A[%d, %d] = %d", result2[0]+1, result2[1]+1, result2[2]);

    printf("\n\n\nThe number of the args: %d\n", argc);
    for(int i = 0; i<argc; i++)
        printf("%s\n", argv[i]);

}
