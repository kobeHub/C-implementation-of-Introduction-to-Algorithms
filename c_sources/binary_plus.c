#include<stdio.h>
#include<stdlib.h>
/*二进制逐位相加测试，两个n位数组，存二进制数字，将结果放到一个n+1位
 * 数组中*/

int *result, *a, *b, *digit;
int len;
void pluse(){
    int j;
    for(j=0; j<len; j++){
        if(a[j] == 1 && b[j] == 1){//注意短路判断
            digit[j] = 1;
            result[j] = 0;
        }else{
            digit[j] = 0;
            result[j] = a[j] + b[j];
        }
    }
    result[len] = 0;
    for(j=0; j<len; j++){
        result[j+1] += digit[j];
    }
}

void print(int *array, int length){
    for(int i=length-1; i>=0; i--)
        printf("%d",array[i]);
    printf("\n");
}

void ops(){
    char str[len+1];
    int i;
    printf("a:\n");
    scanf("%s", str);
    for(i=0;str[i]!='\0';i++) // 下面就是将字符串转化成二进制字符串了
    {
        if(str[i]=='1')
        {
           a[len-1-i] = 1;
        }
        else if(str[i] == '0')
            a[len-1-i] = 0;
        else
        {
            printf("不是二进制数\n");
            return;
       }
    }

    printf("b:\n");
    scanf("%s", str);
    for(i=0;str[i]!='\0';i++) // 下面就是将字符串转化成二进制字符串了
    {
        if(str[i]=='1')
        {
            b[len-1-i] = 1;
        }
        else if(str[i] == '0')
            b[len-1-i] = 0;
        else
        {
            printf("不是二进制数\n");
            return ;
        }
    }

    pluse();
}

int main(){
    printf("The length:\n");
    scanf("%d", &len);
    int i;

    result = (int *)malloc((len+1)*sizeof(int));
    a = (int *)malloc(len*sizeof(int));
    b = (int*)malloc(len*sizeof(int));
    digit = (int*)malloc(len*sizeof(int));

    ops();
    print(result, len+1);

    free(a);
    free(b);
    free(result);
    return 0;
}
