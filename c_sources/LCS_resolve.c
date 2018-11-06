#include "utils.h"
#include <stack>

/****************************************************************
 *Copyright (c) 2018 http://www.innohub.top All rights reserved
 *Auther: Inno Jia
 *Date: 2018-11-01
 *Description: 实现LCS问题的求解策略,使用动态规划的方式进行问题
 *             子串:两个序列删除一定的元素得到的序列如果完全相同
 *             则该序列为两个序列的公共子串
 *             该问题具有可以重复利用的计算部分,假定序列a,b长度分
 *             别为m,n 最长子序列的长度为c{m, n}
 *             Longest Common subsequence:
 *             (1) a[m-1] = b[n-1]; c{m, n} = c{m-1, n-1} + 1
 *             (2) a[m-1] != b[n-1]; c{m, n} = max(c{m-1, n}, c{m, n-1})
 *             (3) m = 0 | n = 0 ; c{m, n} = 0
 ****************************************************************/


//---------------------------------------------------------------
// The global vars to record the path and length
//---------------------------------------------------------------
typedef enum{left, up, add}direction;
int** record;
direction** path;


//---------------------------------------------------------------
// Initialize the basic array and fill the matrix record, path
// according to the rule above. Return the LCS length
//---------------------------------------------------------------
int lcs_resolve(char* data_a, char* data_b, int len_a, int len_b) {
  record = (int**)malloc(sizeof(int*)*(len_a+1));
  for(int i = 0; i <= len_a; i++)
    record[i] = (int*)malloc(sizeof(int)*(len_b+1));
  for(int i = 0; i <= len_a; i++) {
    record[i][0] = 0;
  }
  for(int i = 0; i <= len_b; i++) {
    record[0][i] = 0;
  }
  path = (direction**) malloc(sizeof(direction*)*len_a);
  for(int i = 0; i < len_a; i++)
    path[i] = (direction*)malloc(sizeof(direction)*len_b);

  for(int i = 1; i <= len_a; i++) {
    for(int j = 1; j <= len_b; j++) {
      if(data_a[i-1] == data_b[j-1]) {
        record[i][j] = record[i-1][j-1] + 1;
        path[i-1][j-1] = add;
      }else if(record[i-1][j] >= record[i][j-1]) {
        record[i][j] = record[i-1][j];
        path[i-1][j-1] = up;
      }else{
        record[i][j] = record[i][j-1];
        path[i-1][j-1] = left;
      }
    }
  }

  return record[len_a][len_b];
}


void destory(int len_a) {
  for(int p = 0; p <= len_a; p++) {
    free(record[p]);
    free(path[p]);
  }
  free(record);
  free(path);
}

std::stack<char> output;
void construLCS(char* data, int len_a, int len_b) {
  if(len_a == 0 || len_b == 0) {
    printf("\n");
    return ;
  }
  if(path[len_a-1][len_b-1] == add) {
    output.push(data[len_a-1]);
    construLCS(data, len_a-1, len_b-1);
  }else if(path[len_a-1][len_b-1] == up) {
    construLCS(data, len_a-1, len_b);
  } else {
    construLCS(data, len_a, len_b-1);
  }
}

void printLCS(char* data, int len_a, int len_b) {
  construLCS(data, len_a, len_b);
  while(!output.empty()) {
    printf("%c", output.top());
    output.pop();
  }
  printf("\n");
}

//----------------------------------------------------------
// eval one time
//----------------------------------------------------------
void show_one(char* str1, char* str2) {
  int len_a = strlen(str1);
  int len_b = strlen(str2);
  int len = lcs_resolve(str1, str2, len_a, len_b);
  printf("[+]String to be compared: %s   %s", str1, str2);
  printf("\n[+]Common subsequence:");
  printLCS(str1, len_a, len_b);
  printf("[+]The LCS: %d\n\n", len);
}

int main() {
  char human[20] = "human";
  char monkey[20] = "monkey";
  char num1[100] = "0100100111010110100110011101011";
  char num2[100] = "101011100111001100101110011100";
  char str1[100] = "AMANAPLANACATAHAMAYA";
  char str2[100] = "KAYAMAHATACANALPANAMA";

  show_one(human, monkey);
  show_one(num1, num2);
  show_one(str1, str2);
  destory(strlen(str1));
}
