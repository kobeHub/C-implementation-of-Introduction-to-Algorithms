#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <queue>
#include <set>
#include <vector>
#include "graph.h"
#include <algorithm>
/*****************************************************************
 *Copyright (c) 2018 http://www.innohub.top/ All Rights Reserved
 *Author: Inno Jia
 *Date: 2018-11-21
 *Description: An implement and test of undirected graph algorothm
 *             Search algorithms:
 *                -- BFS
 *                -- DFS
 *             Minimum Spanning Trees:
 *                -- Kruskal
 *                -- Prim
 *             output:
 *                -- Print the BFS and DFS tree of G(E, V)
 *                -- Print the MST of the 2 algorithms
 *****************************************************************/


//----------------------------------------------------------------
// BFS(G, s):
//          From the vertex s to do BFS, generate the BFS tree
//          All edges weights set to 0. During the procession,
//          the global variables are stored in the structure
//          of Vertex, and all the Vertex and edges are packaged
//          -- dis_list: every vertex to s in the tree.
//          -- pre_list: every vertex precursor vertex.
//          -- cur_queue: the vertexes
//----------------------------------------------------------------

void BFS(Graph *graph, Vertex start) {
  std::queue<Vertex> cur_queue;

  printf("The BFS tree for vertex %c:\n", start.name);
  cur_queue.push(start);
  while(!cur_queue.empty()) {
    Vertex cur_u = cur_queue.front();
    cur_queue.pop();
    cur_u.color = gray;
    printf("%c-->", cur_u.name);
    char* adjacency_ele = graph->get_adjacency_list(cur_u);

    int length = strlen(adjacency_ele);
    for(int i = 0; i < length; i++) {
      Vertex cur_v = graph->get_vertex(adjacency_ele[i]);
      if(cur_v.color == white) {
        cur_v.color = gray;
        cur_v.d = cur_u.d + 1;
        cur_v.pre = cur_u.name;
        graph->setVertex(cur_v, graph->get_vertex_index(adjacency_ele[i]));
        cur_queue.push(cur_v);
      }
    }
    cur_u.color = black;
    graph->setVertex(cur_u, graph->get_vertex_index(cur_u.name));
  }
}


//---------------------------------------------------------------
// DFS(G, s):
//          From vertex do DFS and generate the DFS tree
//          Difference from book:
//                Just record the start time with d, do not
//                record end time f. Just print the DFS tree.
//--------------------------------------------------------------
void DFS_visit(Graph *graph, Vertex start, int time) {
  start.color = gray;  // being visit
  start.d = time;
  graph->setVertex(start, graph->get_vertex_index(start.name));

  printf("%c-->", start.name);
  char* adjacency_ele = graph->get_adjacency_list(start);
  int length = strlen(adjacency_ele);
  for(int i = 0; i < length; i++) {
    Vertex cur_v = graph->get_vertex(adjacency_ele[i]);
    if(cur_v.color == white) {
      cur_v.pre = start.name;
      cur_v.color = gray;
      time++;
      cur_v.d = time;
      graph->setVertex(cur_v, graph->get_vertex_index(adjacency_ele[i]));
      DFS_visit(graph, cur_v, time);
    }
  }
  start.color = black;
  graph->setVertex(start, graph->get_vertex_index(start.name));
}


//----------------------------------------------------------------
// MST-Kruskal:
//            It find a safe edge to add to the growing forest
//            by finding, all of the edges that connect any two
//            trees in the forest, an edge(u, v) of the least
//            weight
//----------------------------------------------------------------
std::set<Edge> FindSet(std::vector<std::set<Edge> > forest, char target) {
  std::set<Edge>::iterator in;
  for(unsigned int i = 0; i < forest.size(); i++) {
    std::set<Edge> result = forest[i];
    for(in = result.begin(); in != result.end(); in++) {
      Edge curr = *in;
      if((target == curr.a) || (target == curr.b)) {
        return result;
      }
    }
  }
}

void print_set(std::set<Edge> result) {
  std::set<Edge>::iterator it;
  for(it = result.begin(); it != result.end(); it++) {
    printf("{%c, %c}-->", (*it).a, (*it).b);
  }
  printf("\n");
}


void Kruskal(Graph *graph) {
  graph->sortEdges();    // Non-decreasing
  std::vector<std::set<Edge> > forest; // The forest, initial with all the vertexes last generate a tree

  int num_vertexs = graph->get_vertexs_num();
  int num_edges = graph->get_edges_num();
  for(int i = 0; i < num_vertexs; i++) {
    std::set<Edge> tree;
    Vertex init_before = graph->get_vertex(i);
    Edge init_edge = {init_before.name, '0', INT_MAX};      // Initialize the set, make vertexes into edges
    tree.insert(init_edge);
    forest.push_back(tree);
  }
  static std::set<Edge> result;      // Hold the Spanning Tree
  forest.push_back(result);

  for(int i = 0; i < num_edges; i++) {
    Edge curr = graph->get_edge(i);
    std::set<Edge> a, b;
    a = FindSet(forest, curr.a);
    b = FindSet(forest, curr.b);
    if(a != b) {
      std::set<Edge> branch;
      branch.insert(curr);
      set_union(
        result.begin(), result.end(),
        branch.begin(), branch.end(),
        inserter(result, result.begin())
      );
      //auto iter_a = std::find(forest.begin(), forest.end(), a);
      //if(iter_a != forest.end()) {
      //  forest.erase(iter_a);
      //}
      //auto iter_b = std::find(forest.begin(), forest.end(), b);
      //if(iter_b != forest.end()) {
      //  forest.erase(iter_b);
      //}
    }
  }

  print_set(result);
}


//---------------------------------------------------------------
// MST-Prim
//
//---------------------------------------------------------------
bool exist_in(std::priority_queue<Vertex> q, char target) {
  while(!q.empty()){
    Vertex curr = q.top();
    q.pop();
    if(curr.name == target) {
      return true;
    }
  }
  return false;
}

void Prim(Graph *graph, Vertex start) {
  std::priority_queue<Vertex> pri;
  start.d = 0;
  graph->setVertex(start, graph->get_vertex_index(start.name));
  int num_vertexs = graph->get_vertexs_num();
  for(int i = 0; i < num_vertexs; i++) {
    pri.push(graph->get_vertex(i));
  }

  while(!pri.empty()) {
    Vertex curr = pri.top();
    pri.pop();
    char* adjacency_ele = graph->get_adjacency_list(curr);
    int length = strlen(adjacency_ele);

    for(int i = 0; i < length; i++) {
      int weight_v = graph->get_weights(curr.name, adjacency_ele[i]);
      Vertex cur_v = graph->get_vertex(adjacency_ele[i]);
      if(exist_in(pri, adjacency_ele[i]) && weight_v < cur_v.d) {
        cur_v.pre = curr.name;
        cur_v.d = weight_v;
        graph->setVertex(cur_v, graph->get_vertex_index(adjacency_ele[i]));
      }
    }
  }

  for(int i = 0; i < num_vertexs; i++) {
    Vertex curr = graph->get_vertex(i);
    printf("{%c, %c}-->", curr.pre, curr.name);
  }
}



int main() {
  Vertex vertexs[9];
  Edge edges[14];

  vertexs[0] = {'a', white, INT_MAX, '0'};
  vertexs[1] = {'b', white, INT_MAX, '0'};
  vertexs[2] = {'c', white, INT_MAX, '0'};
  vertexs[3] = {'d', white, INT_MAX, '0'};
  vertexs[4] = {'e', white, INT_MAX, '0'};
  vertexs[5] = {'f', white, INT_MAX, '0'};
  vertexs[6] = {'g', white, INT_MAX, '0'};
  vertexs[7] = {'h', white, INT_MAX, '0'};
  vertexs[8] = {'i', white, INT_MAX, '0'};

  edges[0] = {'a', 'b', 14};
  edges[1] = {'a', 'h', 8};
  edges[2] = {'b', 'h', 11};
  edges[3] = {'b', 'c', 8};
  edges[4] = {'c', 'i', 2};
  edges[5] = {'c', 'd', 7};
  edges[6] = {'c', 'f', 4};
  edges[7] = {'d', 'f', 14};
  edges[8] = {'d', 'e', 9};
  edges[9] = {'e', 'f', 10};
  edges[10] = {'f', 'g', 2};
  edges[11] = {'i', 'g', 6};
  edges[12] = {'g', 'h', 1};
  edges[13] = {'h', 'i', 7};

  int weights[] = {14, 8, 11, 8, 2, 7, 4, 14, 9, 10, 2, 6, 1, 7};

  Graph *graph = new Graph(vertexs, edges, 9, 14);
  BFS(graph, vertexs[0]);
  graph->reset();
  printf("\nThe DFS tree for vertex %c:\n", vertexs[0].name);
  DFS_visit(graph, vertexs[0], 0);

  graph->reset(weights);
  printf("\n\nThe MST of Prim:\n");
  Prim(graph, vertexs[0]);
  printf("\nThe MST of Kruskal\n");
  graph->reset(weights);
  Kruskal(graph);

}
