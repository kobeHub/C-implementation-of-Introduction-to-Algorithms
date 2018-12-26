#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX (INT_MAX - 1000)
#define NIL -1000

/*******************************************************************
 * Copyright © 2018 http://www.innohub.top/ All Rights Reserved
 * Author: Inno Jia
 * Date: 2018-12-10
 * Description: Implement 2 basic algorithms to solve the all vertexes
 *              pairs shortest path problem.
 *              One use the Dynamic programming with time complexion
 *              θ(V**4) and can be promoted to θ(V**3 * lgV)
 *
 *              Another is Floyd-Warshall with time complexion of
 *              θ(V**3)
 * Compile:
 * Usage:
 *******************************************************************/

int ** Init(int n){
  int **data = (int**)malloc(sizeof(int*) * n);
  for (int i = 0; i < n; i++) {
    data[i] = (int*) malloc(sizeof(int) * n);
    memset(data[i], MAX, sizeof(int) * n);
  }


  return data;
}

void free_(int **data, int n) {
  for (int i = 0; i < n; i++)
    free(data[i]);
  free(data);
  data = NULL;
}


//-------------------------------------------------------------------------
// extend_shortest_path():
//        Compute the data matrix according to Initialize matrix weights
//        and the data matrix on the process, and record the previous
//        vertexes to the **pre matrix.
//        Time complexion: θ(V**3)
//-------------------------------------------------------------------------
int **extend_shortest_path(int **data_l, int **data_r, int **pre, int n) {
  int **data_l1 = Init(n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      data_l1[i-1][j-1] = MAX;
      for (int k = 1; k <= n; k++) {
        int weight;
        if((data_l[i-1][k-1]==MAX) || (data_r[k-1][j-1]==MAX))
          weight = MAX;    // Avoid to over flow
        else
          weight = data_l[i-1][k-1] + data_r[k-1][j-1];
        if (weight < data_l1[i-1][j-1]) {
          // Can find shorter path record the pre path to matrix pre
          pre[i-1][j-1] = pre[k-1][j-1];
          data_l1[i-1][j-1] = weight;
        }
      }
    }
  }

  return data_l1;
}


//--------------------------------------------------------------------------
// faster_all_pairs_shortest_paths():
//          compute all pairs shortest path with dynamic programming
//          l_2m was computed by l_m, which is faster than the common method
//--------------------------------------------------------------------------
int **faster_all_pairs_shortest_paths(int **data, int **pre, int rows) {
  int m = 1;
  int **data_l1m = Init(rows);
  data_l1m = data;
  while (m < rows-1) {
    //data_l2m = Initialize(rows);
    data_l1m = extend_shortest_path(data_l1m, data_l1m, pre, rows);
    m = m * 2;
  }
  return data_l1m;
}

//----------------------------------------------------------------------
// Print shortest path according to previous matrix
//----------------------------------------------------------------------
void print_path(int **pre, int i, int j) {
  if (i == j) {
    printf("%d->", i);
  } else if (pre[i-1][j-1] == NIL) {
    printf("There is no path from %d to %d\n", i, j);
  } else {
    print_path(pre, i, pre[i-1][j-1]);
    printf("%d->", j);
  }
}


//--------------------------------------------------------------------
// Print a matrix for debug
//--------------------------------------------------------------------
void print_matrix(int **data, int n) {
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
      printf("%d ", data[i][j]);
    printf("\n");
  }
  printf("\n");
}


//-------------------------------------------------------------------
// FloydWarshall:
//          compute_floyd_K():
//              compute the kth iteration matrix and path matrix
//              Output: The kth matrix
//
//          FloydWarshall():
//              compute all the k times iteration matrix and output
//              the nth matrix which contains all pairs shortest
//              path distance and the previous path record in the pre
//              matrix
//-------------------------------------------------------------------
int **compute_floyd_K(int **data_k_1, int **pre, int rows, int k) {
  int **data_k = Init(rows);
  int weight;
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= rows; j++) {
      if ((data_k_1[i-1][k-1] == MAX) || (data_k_1[k-1][j-1] == MAX))
        weight = MAX;
      else
        weight = data_k_1[i-1][k-1] + data_k_1[k-1][j-1];
      if (weight < data_k_1[i-1][j-1]) {
        data_k[i-1][j-1] = weight;
        pre[i-1][j-1] = pre[k-1][j-1];
      } else {
        data_k[i-1][j-1] = data_k_1[i-1][j-1];
      }
    }
  }
  return data_k;
}

int **FloydWarshall(int **data, int **pre, int rows) {
  int **data_k = Init(rows);
  data_k = data;
  for (int k = 1; k <= rows; k++) {
    data_k = compute_floyd_K(data_k, pre, rows, k);
  }ta
  return data_k;
}

//-------------------------------------------------------------------
//To test 2 algorithm initialize data
//-------------------------------------------------------------------
void Init_test(int **graph, int **pre, int g[][6], int p[][6]) {
  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++) {
      graph[i][j] = g[i][j];
      pre[i][j] = p[i][j];
    }
}

//--------------------------------------------------------------------
// show all the pairs shortest path and distance
//--------------------------------------------------------------------
void show(int **result, int **pre) {
  for (int i = 1; i <= 6; i++) {
    for (int j = i + 1; j <= 6; j++) {
      printf("Shortest path from %d to %d:\t", i, j);
      print_path(pre, i, j);
      printf("\tLength:%d\n", result[i-1][j-1]);
    }
  }
}

int main () {
  int **graph = Init(6);
  int **pre = Init(6);
  int graph_[6][6] = {
    {0, 20, 6, MAX, 16, MAX},
    {20, 0, MAX, 6, MAX, 19},
    {6, MAX, 0, 9, 12, MAX},
    {MAX, 6, 9, 0, MAX, 12},
    {16, MAX, 12, MAX, 0, MAX},
    {MAX, 19, MAX, 12, MAX, 0}
  };

  int pre_[6][6] = {
    {NIL, 1, 1, NIL, 1, NIL},
    {2, NIL, NIL, 2, NIL, 2},
    {3, NIL, NIL, 3, 3, NIL},
    {NIL, 4, 4, NIL, NIL, 4},
    {5, NIL, 5, NIL, NIL, NIL},
    {NIL, 6, NIL, 6, NIL, NIL}
  };

  Init_test(graph, pre, graph_, pre_);

  printf("The test graph:\n\
      1-------------------20------------------2\n\
      -  -                                  - -\n\
      -    6                              6   -\n\
      -      -                          -     -\n\
     16       3------------------------4      19\n\
      -      -                          -     -\n\
      -   12                              12  -\n\
      - -                                   - -\n\
      5---------------------------------------6\n\n\n");

  printf("Use the basic dynamic method:\n");
  int **result = faster_all_pairs_shortest_paths(graph, pre, 6);
  printf("The output weights matrix:\n");
  print_matrix(result, 6);
  printf("The previous path matrix:\n");
  print_matrix(pre, 6);
  show(result, pre);
  printf("\n");

  printf("Use the FloydWarshall algorithm:\n");
  Init_test(graph, pre, graph_, pre_);
  result = FloydWarshall(graph, pre, 6);
  printf("The output weights matrix:\n");
  print_matrix(result, 6);
  printf("The previous path matrix:\n");
  print_matrix(pre, 6);
  show(result, pre);


  free_(graph, 6);
  free_(pre, 6);
  free_(result, 6);

}
