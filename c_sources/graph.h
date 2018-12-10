#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <utility>

/*****************************************************************
 *Copyright (c) 2018 http://www.innohub.top/ All Rights Reserved
 *Author: Inno Jia
 *Date: 2018-11-21
 *Description: Define the basic data structure of undirected graph
 *             with the Adjacency-list Representation
 *****************************************************************/

enum Color{white, gray, black};

typedef struct Vertex{
  char name;
  Color color;
  // Using in the BFS
  int d;      // The path length to start vertex  and the priority of prim
  char pre;    // The precursor vertex
  friend bool operator<(const Vertex &a, const Vertex &b) {
    return a.d > b.d;
  }
}Vertex;

typedef struct Edge{
  char a;    // just store the name of vertexes
  char b;
  int weight;

  bool operator==(const Edge &ano)  const{
    return (a == ano.a && b == ano.b);
  }

  bool operator<(const Edge &ano) const {
    return ano.weight - weight < 0;
  }

  void operator=(const Edge &ano)  {
    a = ano.a;
    b = ano.b;
    weight = ano.weight;
  }
}Edge;


class Graph {
  public:
    Graph(Vertex* vertexs, Edge* edges, int v_num, int e_num);
    ~Graph();

    char* get_adjacency_list(Vertex a);
    Vertex get_vertex(char name);
    Vertex get_vertex(int i) {return vertexs[i];}
    Edge get_edge(int i) {return edges[i];}
    int get_vertex_index(char a);
    int get_vertexs_num() {return num_vertexs;}
    int get_edges_num() {return num_edges;}

    void setVertex(Vertex v, int index);      // Access to vertexes
    void reset();                             // Reset the vertexes and edges of the graph
    void reset(int* weights);                 // For MST algorithm test to reset edges' weights
                                                  // Caution: The order of weights and edges are same
    void sortEdges();                         // Sort edges into non-decreasing order by weight
    int get_weights(char a, char b);

  private:
    Vertex* vertexs;
    Edge* edges;
    char** adjacency_list;                    // store the name of vertex, the element
                                                  // order is same to vertexes
    int num_vertexs;
    int num_edges;
};
