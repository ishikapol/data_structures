/*****************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa3
* Graph.h
* Header file for Graph ADT
*****************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdbool.h>
#include "List.h"
#define NIL 0
#define UNDEF -1

// Exported type -------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-Destructors --------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG);


// Access functions ----------------------------------------------

// getOrder()
// Returns the number of verticies in the Graph
int getOrder(Graph G);

// getSize()
// Returns the size of the Graph
int getSize(Graph G);

// getParent()
// Returns the parent of vertex u in the Depth First tree created by DFS(), or NIL 
// if DFS() has not yet been called. Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of vertex u. Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of vertex u. Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u); 


// Manipulation procedures ---------------------------------------

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to 
// the adjacency List of u. Pre: 1 <= u <= n, 1 <= v <= n
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but 
// not u to the adjacency List of v). Pre: 1 <= u <= n, 1 <= v <= n
void addArc(Graph G, int u, int v); 

// DFS()
// Performs the depth first search algorithm on G. Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);


// Other operations --------------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
