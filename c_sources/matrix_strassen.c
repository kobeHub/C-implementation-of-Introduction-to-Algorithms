#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*MyFunc)(int**, int**, int**, int);
void run(MyFunc func, int **a, int **b, int**c, int rows){
    double start, end;
    start = clock();
    func(a, b, c, rows);
    end = clock();
    printf("Run time:%fs\n", (end-start)/CLOCKS_PER_SEC);
}


//TODO:实现以下标计算的strassen 以及简单分治算法

/*进行矩阵乘法的模拟运算,分别采用了普通的分治算法时间复杂度为   Θ(n**3)
 　 * 以及strassen算法时间复杂度为 Θ(lg7) */


/*普通的矩阵分解算法,将n*n方阵分解为 n/2*n/2方阵,再进行运算
 * 不需要进行矩阵的复制,使用下标进行运算*/

//描述矩阵的坐标值
struct Matrix{
    int row_low;
    int row_high;
    int col_low;
    int col_high;
};

//int **a=NULL, **b=NULL, **c=NULL;//用于矩阵计算的全局变量
/*
//void Square_add(struct Matrix *ma, struct Matrix *mb, struct Matrix *mc){
//    int ar, br, cr, ac, bc, cc;
//    for( ar = ma->row_low-1,  br = mb->row_low-1,  cr = mc->row_low-1; ar<ma->row_high, br<mb->row_high, cr<mc->row_high; ar++,br++,cr++)
//        for( ac = ma->col_low-1,  ac =mb->col_low-1,  cc=mc->col_low-1; ac < ma->col_high, bc < mb->col_high, cc<mc->col_high; ac++, bc++, cc++ )
//            c[cr][cc] = a[ar][ac] + b[br][bc];
//
//}

void Square_add(int a_, int b_, struct Matrix mc){
//    int size = sizeof(a_)/sizeof(a_[0]);
//    printf("size:%d\n", size);
//    for(int i=0;i<size;i++)
//        for(int j =0;j<size;j++)
    c[mc.row_low-1][mc.col_low-1] = a_+b_;
    //free(a_);
    //free(b_);
}

int Square_multiply_recusive(struct Matrix cur_a, struct Matrix cur_b){
    int rows = cur_a.row_high-cur_a.row_low+1;
    if(rows == 1){
        int tem;// = (int **)malloc(sizeof(int*)*1);
        //tem[0] = (int*)malloc(sizeof(int)*1);
        tem = a[cur_a.row_low-1][cur_a.col_low-1] * b[cur_b.row_low-1][cur_b.col_low-1];
        return tem;
    }
    else{
        int half = rows/2;
        struct Matrix a11 ={1, half, 1, half};
        struct Matrix a12 ={1, half, half+1, rows};
        struct Matrix a21 ={half+1, rows, 1, half};
        struct Matrix a22 ={half+1, rows, half+1, rows};
        struct Matrix b11 ={1, half, 1, half};
        struct Matrix b12 ={1, half, half+1, rows};
        struct Matrix b21 ={half+1, rows, 1, half};
        struct Matrix b22 ={half+1, rows, half+1, rows};
        struct Matrix c11 ={1, half, 1, half};
        struct Matrix c12 ={1, half, half+1, rows};
        struct Matrix c21 ={half+1, rows, 1, half};
        struct Matrix c22 ={half+1, rows, half+1, rows};

        Square_add(Square_multiply_recusive(a11, b11), Square_multiply_recusive(a12, b21), c11);
        Square_add(Square_multiply_recusive(a11, b12), Square_multiply_recusive(a12, b22), c12);
        Square_add(Square_multiply_recusive(a21, b11), Square_multiply_recusive(a22, b21), c21);
        Square_add(Square_multiply_recusive(a21, b12), Square_multiply_recusive(a22, b22), c22);

    }
}
*/


int Random(int beg, int end){
    static unsigned int seed = 0;
    seed++;
    srand((int) time(NULL)+seed*seed);
    int res = end - beg;
    return rand()%res+beg;
}

void show(int **target, int len){
    for(int i =0;i<len;i++){
         for(int j =0;j<len;j++)
            printf("%d ", target[i][j]);
         printf("\n");
    }
    printf("\n");
}

void init(int **a, int **b, int **c, int size){
    for(int i=0; i<size;i++)
        for(int j = 0;j<size;j++){
            a[i][j] = Random(1, 3);
            b[i][j] = Random(1, 3);
            c[i][j] = 0;
        }
    show(a, size);
    show(b, size);
}

//把a的指定项复制到b
void matrix_cpy_pre(int **am, int **bm, int row_low, int row_high, int col_low, int col_high){
    int size = row_high - row_low + 1;
    for(int i = 0; i<size;i++)
        for(int j =0;j<size;j++)
            bm[i][j] = am[row_low-1+i][col_low-1+j];
}

//把b复制到a的指定项
void matrix_cpy_back(int **am, int**bm, int row_low, int row_high, int col_low, int col_high){
    int size= row_high - row_low + 1;
    for(int i = 0; i<size;i++)
        for(int j =0;j<size;j++)
            am[row_low-1+i][col_low-1+j] = bm[i][j];

}

void matrix_add(int **m, int **n, int **result, int size){
    for(int i =0;i<size;i++)
        for(int j = 0; j<size; j++)
            result[i][j] = m[i][j] + n[i][j];
}

void matrix_sub(int **m, int **n, int **result, int size){
    for(int i = 0; i<size; i++)\
        for(int j = 0; j<size; j++)
            result[i][j] = m[i][j] - n[i][j];
}

//进行矩阵的划分
int ***divide_matrix(int **data, int half){
    int ***result = (int***)malloc(4*sizeof(int**));
    for(int i =0;i<4;i++){
        result[i] = (int**)malloc(half*sizeof(int*));
        for(int j =0;j<half;j++)
            result[i][j] = (int*)malloc(half*sizeof(int));
    }
    matrix_cpy_pre(data, result[0], 1, half, 1, half);
    matrix_cpy_pre(data, result[1], 1, half, half+1, half*2);
    matrix_cpy_pre(data, result[2], half+1, half*2, 1, half);
    matrix_cpy_pre(data, result[3], half+1, half*2, half+1, half*2);
    return result;

}

//初始化m*n*n三维数组
int ***init_data(int m, int n){
    int ***res = (int***)malloc(m*sizeof(int**));
    for(int i =0;i<m;i++){
        res[i] = (int**)malloc(n*sizeof(int*));
        for(int j =0;j<n;j++)
            res[i][j] = (int*)malloc(n*sizeof(int));
    }
    return res;
}

void free_(int ***data, int m, int n){
    for(int i = 0; i<m; i++){
        for(int  j =0;j<n;j++)
            free(data[i][j]);
        free(data[i]);
    }
    free(data);
}

/*strassen 方法:
 * 1.将矩阵分解为n/2大小的子矩阵
 * 2.创建10个临时矩阵均为n/2大小,每个保存的是步骤一中的子矩阵的或者差
 * 3.递归计算7个矩阵的积
 * 4.利用步骤3中的矩阵计算c的四个矩阵的数值
 *
 * 10个矩阵:
 * s1 = b12-b22
 * s2 = a11+a12
 * s3 = a21+a22
 * s4 = b21-b11
 * s5 = a11+a22
 * s6 = b11+b22
 * s7 = a12-a22
 * s8 = b21+b22
 * s9 = a11-a21
 * s10 = b11+b12
 *
 * 7个矩阵的积:
 * p1 = a11*s1
 * p2 = s2*b22
 * p3 = s3*b11
 * p4 = a22*s4
 * p5 = s5*s6
 * p6 = s7*s8
 * p7 = s9*s10
 *
 * 得到的四个n/2矩阵:
 * c11 = p5+p4-p2+p6
 * c12 = p1+p2
 * c21 = p3+p4
 * c22 = p5+p1-p3-p7*/
void strassen(int** a, int **b, int **c, int rows){
    //printf("Use %s function:\n", __FUNCTION__);
    if(rows == 1){
        c[0][0] = a[0][0] * b[0][0];
        return ;
    }

    int half = rows/2;
    //获得的是四个n/2矩阵
    int ***a_part = divide_matrix(a, half);
    int ***b_part = divide_matrix(b, half);
    int ***c_part = divide_matrix(c, half);

    int ***s_part = init_data(10, half);
    matrix_sub(b_part[1], b_part[3], s_part[0], half);
    matrix_add(a_part[0], a_part[1], s_part[1], half);
    matrix_add(a_part[2], a_part[3], s_part[2], half);
    matrix_sub(b_part[2], b_part[0], s_part[3], half);
    matrix_add(a_part[0], a_part[3], s_part[4], half);
    matrix_add(b_part[0], b_part[3], s_part[5], half);
    matrix_sub(a_part[1], a_part[3], s_part[6], half);
    matrix_add(b_part[2], b_part[3], s_part[7], half);
    matrix_sub(a_part[0], a_part[2], s_part[8], half);
    matrix_add(b_part[0], b_part[1], s_part[9], half);

    int ***p_part = init_data(7, half);
    strassen(a_part[0], s_part[0], p_part[0], half);
    strassen(s_part[1], b_part[3], p_part[1], half);
    strassen(s_part[2], b_part[0], p_part[2], half);
    strassen(a_part[3], s_part[3], p_part[3], half);
    strassen(s_part[4], s_part[5], p_part[4], half);
    strassen(s_part[6], s_part[7], p_part[5], half);
    strassen(s_part[8], s_part[9], p_part[6], half);

    matrix_add(p_part[3], p_part[4], c_part[0], half);
    matrix_sub(c_part[0], p_part[1], c_part[0], half);
    matrix_add(c_part[0], p_part[5], c_part[0], half);

    matrix_add(p_part[0], p_part[1], c_part[1], half);

    matrix_add(p_part[2], p_part[3], c_part[2], half);

    matrix_add(p_part[4], p_part[0], c_part[3], half);
    matrix_sub(c_part[3], p_part[2], c_part[3], half);
    matrix_sub(c_part[3], p_part[6], c_part[3], half);

    matrix_cpy_back(c, c_part[0], 1, half, 1, half);
    matrix_cpy_back(c, c_part[1], 1, half, half+1, half*2);
    matrix_cpy_back(c, c_part[2], 1+half, half*2, 1, half);
    matrix_cpy_back(c, c_part[3], 1+half, half*2, 1+half, half*2);

    free_(a_part, 4, half);
    free_(b_part, 4, half);
    free_(c_part, 4, half);
    free_(s_part, 10, half);
    free_(p_part, 7, half);
}

void matmul(int **a, int **b, int **c, int size){
    int i, j ,k;
    printf("Use %s function:\n", __FUNCTION__);
    for(i = 0;i<size;i++)
        for(j =0;j<size;j++)
            c[i][j] = 0;

    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            for(k=0; k<size;k++)
                c[i][j] += a[i][k] * b[k][j];
    show(c, size);
}


int main(int args, char* argv[]){
    if(args <= 1){
        printf("[!]Please enter the square matrix size!\n");
        exit(0);
    }
    int size = atoi(argv[1]);
    int **a = (int **)malloc(sizeof(int*)*size);
    int **b = (int **)malloc(sizeof(int*)*size);
    int **c = (int **)malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
        a[i] = (int *)malloc(sizeof(int)*size);
        b[i] = (int *)malloc(sizeof(int)*size);
        c[i] = (int *)malloc(sizeof(int)*size);
    }
/*
    init();
    struct Matrix a_origin = {1, 4, 1 ,4};
    struct Matrix b_origin = {1 ,4, 1, 4};
    Square_multiply_recusive(a_origin, b_origin);
    show(c, 4);
*/

    init(a, b, c, size);
    printf("Use strassen function:\n");
    run(strassen, a, b, c, size);
    show(c, size);
    run(matmul, a, b, c, size);
    for(int i=0;i<size;i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}
