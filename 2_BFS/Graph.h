/*****************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa2
* Graph.h
* Header file for Graph ADT
*****************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdbool.h>
#include "List.h"
#define NIL 0
#define INF -1

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
// Returns the order of the Graph
int getOrder(Graph G);

// getSize()
// Returns the size of the Graph
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has 
// not yet been called.
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL 
// if BFS() has not yet been called. Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() 
// has not yet been called. Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends 
// to L the value NIL if no such path exists. Pre: getSource(G)!=NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);


// Manipulation procedures ---------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to 
// the adjacency List of u.
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but 
// not u to the adjacency List of v).
void addArc(Graph G, int u, int v); 

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, 
// and source fields of G accordingly.
void BFS(Graph G, int s);


// Other operations --------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
