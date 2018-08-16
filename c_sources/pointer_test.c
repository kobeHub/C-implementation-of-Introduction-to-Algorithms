#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*关于内存动态分配的函数使用：
 * malloc(size_t): 分配相应字节数的内存空间
 * calloc(nmemeb, size_t): 分配一定长度的数组，每个成员长度size_t
 * 均需要显示调用free()函数释放空间
 * alloca(size_t): 分配一定字节的栈空间，空间在函数作用域结束后自动释放，可能造成栈空间溢出*/


/*malloc函数向堆申请空间，可以是不连续的空间，不进行初始化
 * calloc函数分配连续的空间，初始化为０
 * realloc:重新分配内存空间大小，一般用于扩大原来的空间，不进行初始化
 * alloca: 不进行初始化
 * new:
 * 是动态分配内存的运算符，自动计算需要分配的空间，在分配类类型的内存空间时，i
 * 同时调用类的构造函数，对内存空间进行初始化，即完成类的初始化工作。
 * 动态分配内置类型是否自动初始化取决于变量定义的位置，
 * 在函数体外定义的变量都初始化为0，
  * 在函数体内定义的内置类型变量都不进行初始化*/

//函数指针用于指向某些具有特定函数签名的函数首地址，通过定义该类函数可以灵活调用
//具有相同类型的函数
//指针函数是指返回值为指针的函数，通常可用于具有多个返回值的解决策略之一
int max(int, int);
int min(int, int);
int (*fun)(int, int);

int main(){
    int *array = (int*)alloca(sizeof(int)*20);
    for(int* p = array; p != array+20; p++)
       (*p) = 1;
   // printf("%d ", *(array+19) == array[19]);
    int *ptr = array;
    for(int i =0; i<20;i++)
    {
        (*ptr) ++;
        printf("%d ", *ptr);
        ptr++;
    }
    //free(array);
    printf("\nint:%ld\nint*:%ld\n", sizeof(int), sizeof(int*));
    printf("char:%ld\nchar*:%ld\n", sizeof(char), sizeof(char*));
    printf("long:%ld\nfloat:%ld\n", sizeof(long), sizeof(float));
    printf("double:%ld\nlonglong:%ld\n", sizeof(double), sizeof(long long));
    printf("float*:%ld\ndouble*:%ld\nlong*:%ld\n\n\n", sizeof(float*),
            sizeof(double*),sizeof(long*));

    /*在64bit机器中，所有指针均为８字节，int 4 char 1 float double long 8*/
    //指针类型可以进行转化，char指针转化为int指针后，每次+1都会加上
    //sizeof(int)
    char str[50] = "abcdefghijklmnopqrstuvwxyz";
    int *int_str = (int*) str;
    int_str += 2;  // 加上了2*sizeof(int) 即８字节，现在指向str[8] = g,即第９个元素
    printf("%s  ", str);
    printf("%c", *int_str);

    //不规则示范
    char *p = str;
    char **ptrl = &p;  //将指针p的地址赋值给ptr
    printf("\n%s\n", *ptrl);
    printf("\n**ptrl = %c\n", **ptrl);
    (*ptrl)++;//*ptrl->p, 现在指向第sizeof(char)+1 第二个元素
    //ptrl += 1;//这里是一个非法操作，ptrl+1表示&p+1这是一个随机的位置
    printf("**ptrl = %c\n", **ptrl);

    //注意c++中的string类型是不可变类型，所以要将字符串定义为const
    const char *arrays[3] = { "Be patient", "It\'s a great test", "You should do it"};
    char *show = (char*)malloc(200*sizeof(char));
    strcat(show, *arrays);
    strcat(show, *(arrays+1));
    strcat(show, *(arrays+2));
    printf("After process:\n%s", show);
    free(show);

    //指针和结构体
    struct Person{
        const char* name;
        int age;
        char sex;
    };

    struct Person p1 = {"Kobe", 39, 'M'};
    struct Person *p_r = &p1;
    int *po = (int*)&p1;//可以把将指针类型进行强制转化
    printf("\nThe person's message:%s, %d, %c", p_r->name, p_r->age, p_r->sex);
    //printf("\nBy another pointer:%s, %d, %c\n", po->name, po->age, po->sex);printf("\nBy array's way:%s, %d, %c\n", *p_r, *++p_r, *++p_r);
   // printf("\nBy another pointer:%s, %d, %c\n", *po, *(po+1), *po+2);
    //进行了指针的类型转化就不可以再访问原结构体数据

    fun = max;//将mxa首地址赋给指针fun
    printf("\n1 and 2:%d\n", (*fun)(1, 2));
    fun = min;
    printf("1 and 2:%d\n", (*fun)(1, 2));

    struct Person *us = (struct Person *)alloca(sizeof(struct Person)*3);
    *us = {"James", 36, 'M'};
    *(us+1) = {"Jodan", 66, 'm'};
    *(us+2) = {"Hadan", 30, 'm'};
    printf("\nus:0 %s %d %c", us[0].name, us[0].age, us[0].sex);
    //指针数组不可以简单进行长度计算
    int leng = sizeof(us)/sizeof(*us);
    printf("\nThe length of us:%ld %ld %d\n", sizeof(us), sizeof((us)[0]), leng);

    typedef struct Position{
        int top;
        int right;
        int bottom;
        int left;
    }pos;
    pos pw = {1, 2, 3, 4};
    pos *pwp = &pw;
    printf("\nThe position is : %d %d %d %d\n", pwp->top, pwp->right, pwp->bottom, pwp->left);
}

int max(int a, int b){return (a>b?a:b);}
int min(int a, int b){return (a<b?a:b);}

