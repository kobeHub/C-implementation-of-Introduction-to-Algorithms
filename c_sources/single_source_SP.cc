#include "graph.h"
#include <string.h>
#include "pri_queue.h"
#include <vector>
#include <stack>

#define MAX (INT_MAX - 1000)    // Avoiding the overflow

/*******************************************************************
 * Copyright (c) 2018 http://www.innohub.top/ All Rights Reserved
 * Author: Inno Jia
 * Date: 2018-12-10
 * Description: Implement the classic single source shortest path
 *              algorithm and do some tests
 * Compile:   g++ single_source_SF.cc graph.cc -std=c++14 -o single
 * Usage:     ./single
 *******************************************************************/


//******************************************************************
// Relax(u, v, w):
//      Do the edges relax, relax the vertex weights from +Inf to
//      the weights of the shortest path from s.
//      Just record the previous vertex and update vertex weights
//
//
//      With Relax:
//          -- for BF and an edge provided
//******************************************************************

void Relax(Graph *graph, Vertex u, Vertex v, Edge e) {
  if (u.d + e.weight < v.d) {
    v.d = u.d + e.weight;
    v.pre = u.name;
    graph->setVertex(v, graph->get_vertex_index(v.name));
  }
}

void Init(Graph *graph, Vertex s) {
  graph->reset();
  s.d = 0;
  s.pre = '*';
  s.color = white;
  graph->setVertex(s, graph->get_vertex_index(s.name));
}


using namespace std;


//*******************************************************************
// BF(Graph *):
//        Bellman-Ford implementation, for every vertex in the
//        undirected Graph do Relax operation, and do it |V| - 1
//        times, then every vertex record the shortest path from
//        source to itself.
//
//        Caution: The graph never include any negative weights
//                  rings.
//*******************************************************************
bool BF(Graph *graph) {
  int num_vertexs = graph->get_vertexs_num();
  int num_edges = graph->get_edges_num();
  Vertex u, v;
  Edge current;
  for (int i = 0; i < num_vertexs - 1; i++) {
    for (int j = 0; j < num_edges; j++) {
      current = graph->get_edge(j);
      u = graph->get_vertex(current.a);
      v = graph->get_vertex(current.b);
      // Be caution: the test example was in a undirected graph
      // So every edge relax twice
      Relax(graph, u, v, current);
      Relax(graph, v, u, current);
    }
  }

  // Identify there is negative weights ring or not
  for (int j = 0; j < num_edges; j++) {
    current = graph->get_edge(j);
    u = graph->get_vertex(current.a);
    v = graph->get_vertex(current.b);
    if(current.weight + u.d < v.d)
      return false;
  }

  return true;
}

// Transform the output of A-E to 10-14
void print_(char r) {
  switch(r){
    case 'A':
      printf("10");
      break;
    case 'B':
      printf("11");
      break;
    case 'C':
      printf("12");
      break;
    case 'D':
      printf("13");
      break;
    case 'E':
      printf("14");
      break;
    default:
      printf("%c", r);
      break;
  }
}

//-----------------------------------------------------------------------------
// eval_BF(Graph *, Vertex):
//      Every vertex except source find its Shortest path by the record of
//      pre and evaluate the output
//-----------------------------------------------------------------------------
void eval_BF(Graph *graph, Vertex source) {
  if (BF(graph)) {
    printf("Bellman-Ford algorithm\n");
    printf("The single shortest path from %c to every vertex:\n", source.name);
    Vertex curr;
    for (int i = 0; i < graph->get_vertexs_num(); i++) {
      stack<Vertex> output;
      curr = graph->get_vertex(i);
      //printf("%c %d\n", curr.name, curr.name != source.name);
      if (curr.name != source.name) {
        printf("To vertex %d: %c->", i, source.name);

        Vertex now = curr;
        while (now.name != source.name) {
          // The output should include all vertexes except source vertex
          output.push(now);
          now = graph->get_vertex(now.pre);
        }

        while(!output.empty()) {
          now = output.top();
          output.pop();
          print_(now.name);
          printf("->");
        }
      } else {
        printf("To vertex %c itself:", source.name);
      }
      printf("  Path length: %d\n", curr.d);
    }
  } else {
    printf("There is no single shortest path from vertex %c in graph\n", source.name);
  }
}


//********************************************************************
// Dijkstra(Graph *, Vertex):
//        Use a priority queue to store all the vertexes and each
//        iteration extract the minimum d vertex, and do relax for its
//        every adjacency vertex
//
//        output use a stack also can use recursive
//********************************************************************
void Dijkstra(Graph *graph, Vertex source) {
  vector<Vertex> path;
  pri_queue<Vertex> vertexes;

  Vertex curr, adj;
  for(int i = 0; i < graph->get_vertexs_num(); i++) {
    curr = graph->get_vertex(i);
    vertexes.push(curr);
  }
  //vertexes.push(source);

  char *adjacency_list;
  while(!vertexes.empty()) {
    curr = vertexes.top();
    curr.color = black;
    graph->setVertex(curr, graph->get_vertex_index(curr.name));
    vertexes.pop();
    path.push_back(curr);

    adjacency_list = graph->get_adjacency_list(curr);
    int weight;
    for (unsigned int i = 0; i < strlen(adjacency_list); i++) {
      adj = vertexes.get(adjacency_list[i]);
      if (adj.color != black) {
        // The vertex adj is in the queue
        weight = curr.d + graph->get_weights(curr.name, adjacency_list[i]);
        if (weight < adj.d) {
          adj.d = weight;
          adj.pre = curr.name;
          vertexes.remove(adj);
          vertexes.push(adj);
        }
      }
    }
  }
  printf("Dijkstra algorithm\n");
  printf("The single shortest path from %c to every vertex:\n", source.name);
  //Vertex curr;
  vector<Vertex>::iterator it;
  for (it = path.begin(); it != path.end(); it++) {
      stack<Vertex> output;
      curr = *it;
      if (curr != source) {
        //printf("To vertex %c: %c->", print_(curr.name), source.name);
        printf("To vertex ");
        print_(curr.name);
        printf(": %c->", source.name);

        while (curr != source) {
          // The output should include all vertexes except source vertex
          output.push(curr);
          curr = graph->get_vertex(curr.pre);
        }

        while(!output.empty()) {
          curr = output.top();
          output.pop();
          print_(curr.name);
          printf("->");
        }
      } else {
        printf("To vertex %c itself", source.name);
      }
      printf("   Path length:%d \n", curr.d);
    }

}


int main() {
  Vertex vertexs[15];
  Edge edges[30];

  vertexs[0] = {'0', white, 0, '*'};
  vertexs[1] = {'1', white, MAX, '*'};
  vertexs[2] = {'2', white, MAX, '*'};
  vertexs[3] = {'3', white, MAX, '*'};
  vertexs[4] = {'4', white, MAX, '*'};
  vertexs[5] = {'5', white, MAX, '*'};
  vertexs[6] = {'6', white, MAX, '*'};
  vertexs[7] = {'7', white, MAX, '*'};
  vertexs[8] = {'8', white, MAX, '*'};
  vertexs[9] = {'9', white, MAX, '*'};
  vertexs[10] = {'A', white, MAX, '*'};
  vertexs[11] = {'B', white, MAX, '*'};
  vertexs[12] = {'C', white, MAX, '*'};
  vertexs[13] = {'D', white, MAX, '*'};
  vertexs[14] = {'E', white, MAX, '*'};

  edges[19] = {'1', '2', 2};
  edges[20] = {'1', '9', 1};
  edges[2] = {'1', 'D', 2};
  edges[3] = {'2', '4', 9};
  edges[4] = {'2', '7', 1};
  edges[5] = {'2', '3', 6};
  edges[6] = {'2', 'B', 7};
  edges[7] = {'2', 'A', 4};
  edges[8] = {'2', 'D', 8};
  edges[9] = {'3', '9', 9};
  edges[10] = {'3', '6', 1};
  edges[11] = {'3', 'A', 9};
  edges[12] = {'4', '9', 10};
  edges[13] = {'4', '8', 7};
  edges[14] = {'4', '7', 2};
  edges[15] = {'4', 'C', 7};
  edges[16] = {'4', '6', 2};
  edges[17] = {'6', 'C', 5};
  edges[18] = {'6', 'D', 3};
  edges[0] = {'0', 'B', 4};
  edges[1] = {'0', 'D', 3};
  edges[21] = {'7', '8', 8};
  edges[22] = {'7', 'E', 5};
  edges[23] = {'B', 'C', 10};
  edges[24] = {'5', 'C', 6};
  edges[25] = {'8', '9', 3};
  edges[26] = {'8', 'C', 8};
  edges[27] = {'D', 'E', 8};
  edges[28] = {'9', 'E', 6};
  edges[29] = {'C', 'E', 10};

  Graph *graph = new Graph(vertexs, edges, 15, 30);
  eval_BF(graph, vertexs[0]);
  Init(graph, vertexs[0]);
  Dijkstra(graph, vertexs[0]);
  //eval_dijkstra(graph, vertexs[0]);
  //delete graph;
}
