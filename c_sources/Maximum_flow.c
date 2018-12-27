#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*******************************************************************
 * Copyright © 2018 http://www.innohub.top/ All Rights Reserved
 * Author: Inno Jia
 * Date: 2018-12-27
 * Description: Test for maximum flow problem, implement the
 *              Ford-Fulkerson method with time complexion of
 *              O(E * |f*|) which f* is one of the maximum flow
 *              and E is the edges set of the graph
 *
 * Definition:
 *   Flow network:
 *                 G=(V, E) is a directed graph, and each edge(u, v)
 *                 of E has a non-negative capacity value c(u, v);
 *                 If the edge set includes (u, v), there will not be
 *                 a (v, u); the capacity of the unconnected vertex is
 *                 0; and there is no loop in the graph.
 *                 Then the graph G is a Flow network.
 *   Flow:
 *                 Supposed G=(V, E) is a flow network and its capacity
 *                 is c, the flow is a real value function f:
 *                 V x V -> R.
 *
 *   Maximum flow:
 *                 Given a flow network G, a source vertex s, a
 *                 sink t, the maximum flow is the one
 *                 with the largest value.
 *
 * Compile:        gcc Maximum_flow.c -o max
 * Usage:          ./max
 *******************************************************************/

#define V 8     // Test for 8 vertexes

//------------------------------------------------------------------
// dfs_visit:
//      Do DFS to get an augmentation path from s to t from the
//      residual graph, can also be implement with BFS
//------------------------------------------------------------------
void dfs_visit(int graph[V][V], int vertex, int t, int *visited, int *previous) {
  for (int i = 0; i < V; i++) {
    if (graph[vertex][i] > 0 && i == t) {
      previous[i] = vertex;
      visited[i] = 1;
      return ;
    }
    if (graph[vertex][i] > 0 && visited[i] == 0) {
      previous[i] = vertex;
      visited[i] = 1;
      dfs_visit(graph, i, t, visited, previous);
    }
  }
}

//------------------------------------------------------------------
// find_path:
//     Return true if there is path from source S to sink t in
//     residual graph. The path store in the *previous
//------------------------------------------------------------------
int find_path(int graph[V][V], int s, int t, int *previous) {
  // Boolean visited to mark the vertex visted
  int *visited = (int*)malloc(sizeof(int) * V);
  memset(visited, 0, sizeof(int) * V);

  dfs_visit(graph, s, t, visited, previous);
  int result = visited[t];
  free(visited);
  return result;
}

// Transfer number to vertex name
void print_(int k) {
  switch(k) {
    case 0:
      printf("s->");
      break;
    case 1:
      printf("a->");
      break;
    case 2:
      printf("b->");
      break;
    case 3:
      printf("c->");
      break;
    case 4:
      printf("d->");
      break;
    case 5:
      printf("e->");
      break;
    case 6:
      printf("f->");
      break;
    case 7:
      printf("t->");
      break;
  }
}

// Recursive print the augmentation path
void print_one_path(int s, int t, int* previous) {
  if (s == t)
    print_(s);
  else {
    print_one_path(s, previous[t], previous);
    print_(t);
  }
}

//---------------------------------------------------------------------
// FordFulkerson:
//        Return the maximum flow from s to t in the given graph
//        Every iteration try to find an augmentation path in the
//        residual graph, and update the residual graph.
//
//        Print all the path visited
//---------------------------------------------------------------------
int FordFulkerson(int graph[V][V], int s, int t) {
  int u, v;
  int max_flow = 0;   // Initialize to 0

  // Initialize the residual graph and fill the residual graph
  // with given capacity in the origin graph
  // residual_g[i][j] indicates residual capacity of edge from i
  // to j, if there is no edge, the value is 0
  int residual_g[V][V];
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      residual_g[i][j] = graph[i][j];
    }
  }

  int *previous = (int*)malloc(sizeof(int)*V);

  while(find_path(residual_g, s, t, previous)) {
    // Find the minimum capacity od edges of path P
    int path_flow = INT_MAX;
    for (v = t; v != s; v=previous[v]) {
      u = previous[v];
      if (residual_g[u][v] < path_flow)
        path_flow = residual_g[u][v];
    }
    print_one_path(s, t, previous);
    printf(" Flow: %d\n", path_flow);
    // update residual capacity of the edge
    for (v = t; v != s; v = previous[v]) {
      u = previous[v];
      residual_g[u][v] -= path_flow;
      residual_g[v][u] += path_flow;
    }

    max_flow += path_flow;
  }
  free(previous);

  return max_flow;
}


int main () {
  int graph[V][V] = {
    {0, 2, 0, 2, 0, 2, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  printf("All the augmentation path:\n");
  printf("\nThe maximum flow of the graph: %d", FordFulkerson(graph, 0, 7));
}
