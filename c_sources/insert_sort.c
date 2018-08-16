#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*插入排序的过程实现*/

void insert_sort(int* data, int length){
    int index, query;//查询的位置　　正在插入的数据的序号
    int value;
    for(query=1; query<length; query++){//从第二个数字进行排序
        value = data[query];
        index = query - 1;
        //将大于当前值的数字向后移,并找到当前值的位置
        while(index>=0 && data[index]>value){
            data[index+1] = data[index];
            index--;
        }
        data[index+1] = value;
    }
}

void print_time(){
    struct tm *local, *global;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
//    global = gmtime(&t);
//
    //注意计时的时间从1900年开始 tm_year　的值是当前时间减去1900
    printf("Local time:%d-%d-%d No:%d %d:%d:%d ISDST:%d\n",
            local->tm_year+1900, local->tm_mon, local->tm_mday,
             local->tm_wday, local->tm_hour, local->tm_min,
             local->tm_sec, local->tm_isdst);
//
//    printf("Global time:%d-%d-%d No:%d %d:%d:%d ISDST:%d\n",
//            global->tm_year+1900, global->tm_mon, global->tm_mday,
//             global->tm_wday, global->tm_hour, global->tm_min,
//             global->tm_sec, global->tm_isdst);
    printf("%s", ctime(&t));
}

int main(){
    print_time();
    int num;
    printf("The length of array:\n");
    scanf("%d", &num);

    int *data;
    data = (int *)malloc(num*sizeof(int));
    printf("Numbers:\n");
    for(int i =0; i<num; i++)
        scanf("%d", &data[i]);

    clock_t start, finish;
    double total_time;
    start = clock();
    insert_sort(data, num);
    finish = clock();
    total_time = (double)(finish - start)/CLOCKS_PER_SEC;

    for(int i=0;i<num;i++)
        printf("%d ", data[i]);
    printf("\nTotal time:%fs", total_time);
}

