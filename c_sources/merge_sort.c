#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/*归并排序过程的实现以及测试*/

/*对于已经排序完成的子数组进行合并
 * 数组的两部分data[begin...middle], data[middle+1...end]
 * middle取值(n+1)/2
 * 该算法设置一个“哨兵”　在两个临时数组最后设置一个最大整值*/
void Merge_guard(int *data, int begin, int middle, int end){
    int *left, *right;
    int left_len = middle - begin + 1;
    int right_len = end - middle;
    left = (int*)malloc((left_len+1)*sizeof(int));
    right = (int*)malloc((right_len+1)*sizeof(int));

    //将元数据放入两个数组中,最后一个数据放入最大整值
    for(int i = 0; i < left_len; i++)
        left[i] = data[begin-1+i];
    for(int i =0;i<right_len;i++)
        right[i] = data[middle+i];
    left[left_len] = INT_MAX;
    right[right_len] = INT_MAX;

    int index_l=0, index_r = 0;
    for(int k=begin-1;k<end;k++){
        if(left[index_l]<=right[index_r]){
            data[k] = left[index_l];
            index_l++;
        }
        else{
            data[k] = right[index_r];
            index_r++;
        }
    }

    free(left);
    free(right);
}

//该算法不设置哨兵，当一个部分数组全部pop，不再执行比较，直接将另一个数组全部复制到原数组
void Merge_no_guard(int *data, int begin, int middle, int end){
    int *left, *right;
    int left_len = middle - begin + 1;
    int right_len = end - middle;
    left = (int*)malloc(left_len*sizeof(int));
    right = (int*)malloc(right_len*sizeof(int));

    //将元数据放入两个数组中,最后一个数据放入最大整值
    for(int i = 0; i < left_len; i++)
        left[i] = data[begin-1+i];
    for(int i =0;i<right_len;i++)
        right[i] = data[middle+i];

    int index_l=0, index_r=0;
    for(int k = begin-1; k<end; k++){
        if(index_l == left_len){
            for(int i= k;i<end;i++){
                data[i] = right[index_r];
                index_r++;
            }
            return;
        }
        if(index_r == right_len){
            for(int i= k;i<end;i++){
                data[i] = left[index_l];
                index_l++;
            }
            return;
        }
        if(left[index_l]<=right[index_r]){
            data[k] = left[index_l];
            index_l++;
        }else{
            data[k] = right[index_r];
            index_r++;
        }
    }

    free(left);
    free(right);
}

void Merge_sort(int* data, int begin, int end){
    if(begin<end){
        int middle = (begin+end)/2;
        Merge_sort(data, begin, middle);
        Merge_sort(data, middle+1, end);
        Merge_no_guard(data, begin, middle, end);
    }
    else
        return;
}

int main(){
    int *data;
    int leng;
    printf("The length:\n");
    scanf("%d", &leng);

    data = (int*)malloc(leng*sizeof(int));
    Merge_sort(data, 1, leng);

    printf("The number:\n");
    for(int i=0; i<leng; i++)
        scanf("%d", &data[i]);
    Merge_sort(data, 1, leng);
    for(int i=0;i<leng;i++)
        printf("%d ", data[i]);
    printf("\n");

    free(data);
}
