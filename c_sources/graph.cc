#include "graph.h"


//----------------------------------------------------------
// Graph::Graph
//        Initialize the basic Graph structure
//        "vertexs": the list of vertexes
//        "edges": the list of edges
//----------------------------------------------------------
Graph::Graph(Vertex* vertexs, Edge* edges, int v_num, int e_num) {
  this->vertexs = vertexs;
  this->edges = edges;
  num_vertexs = v_num;
  num_edges = e_num;

  adjacency_list = (char**)malloc(sizeof(char*)*num_vertexs);
  int *count_vertex =new int[num_vertexs]();
  int i, j;
  for(i = 0; i < num_vertexs; i++) {
    for(j = 0; j < num_edges; j++) {
      if(vertexs[i].name == edges[j].a || vertexs[i].name == edges[j].b)
        count_vertex[i]++;
    }
  }
  for(i = 0; i < num_vertexs; i++) {
    adjacency_list[i] = (char*)malloc(sizeof(char)*count_vertex[i]);
    // printf("%c:%d\n", vertexs[i].name, count_vertex[i]);
  }
  delete [] count_vertex;

  for(i = 0; i < num_vertexs; i++) {
    int index = 0;
    for(j = 0; j < num_edges; j++) {
      if(vertexs[i].name == edges[j].a) {
        adjacency_list[i][index] = edges[j].b;
        index++;
      }else if(vertexs[i].name == edges[j].b) {
        adjacency_list[i][index] = edges[j].a;
        index++;
      }
    }
  }
}

//---------------------------------------------------------
// Release all the space
//---------------------------------------------------------
Graph::~Graph(){
  for(int i = 0; i < num_vertexs; i++) {
    free(adjacency_list[i]);
    adjacency_list[i]  = NULL;
  }
  free(adjacency_list);
  adjacency_list = NULL;

  free(vertexs);
  free(edges);
}


//---------------------------------------------------------
// Get a adjacency list of a Vertex
//---------------------------------------------------------
char* Graph::get_adjacency_list(Vertex a) {
  int index = get_vertex_index(a.name);
  return adjacency_list[index];
}


//---------------------------------------------------------
// Get a Vertex's index in the vertexes list by its name
//---------------------------------------------------------
int Graph::get_vertex_index(char a) {
  for(int i = 0; i < num_vertexs; i++) {
    if(a == vertexs[i].name)
      return i;
  }
  return -1;
}


//---------------------------------------------------------
// Get a vertex by its name
//---------------------------------------------------------
Vertex Graph::get_vertex(char name) {
  return vertexs[get_vertex_index(name)];
}


//----------------------------------------------------------
// Provide an interface to edit vertexes
//----------------------------------------------------------
void Graph::setVertex(Vertex v, int index) {
  vertexs[index] = v;
}


//----------------------------------------------------------
// Reset the vertexes'
//----------------------------------------------------------
void Graph::reset() {
  for(int i = 0; i < num_vertexs; i++) {
    vertexs[i].color = white;
    vertexs[i].d = INT_MAX - 1000;
    vertexs[i].pre = '*';
  }
}


//----------------------------------------------------------
// Reset vertexes and edges
//----------------------------------------------------------
void Graph::reset(int* weights) {
  this->reset();
  for(int i = 0; i < num_edges; i++) {
    edges[i].weight = weights[i];
  }
}


//---------------------------------------------------------
// sort edges
//---------------------------------------------------------
void Graph::sortEdges() {
  for(int i = num_edges-1; i > 0; i--) {
    for(int j = 0; j < i; j++) {
      if(edges[j].weight > edges[j+1].weight) {
        std::swap(edges[j], edges[j+1]);
      }
    }
  }
}

int Graph::get_weights(char a, char b) {
  for(int i = 0; i < num_edges; i++) {
    Edge cur = edges[i];
    if((cur.a==a&&cur.b==b) || (cur.a==b&&cur.b==a))
      return cur.weight;
  }
  return INT_MAX;
}

