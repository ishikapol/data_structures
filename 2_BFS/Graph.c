/********************************************
* Ishika Pol
* Cruz ID: 8122087
* pa2
* Graph.c
* Implementation file for Graph ADT
*********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"

// Structs -------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
   List *adjlist;
   int order;
   int size;
   int source;
   int *parent;
   int *distance;
   int *color;
} GraphObj;


// Constructors-Destructors --------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n) {
   Graph G;
   G = malloc(sizeof(GraphObj));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   G->adjlist = malloc((n+1) * sizeof(List));
   G->parent = malloc((n+1) * sizeof(int));
   G->distance = malloc((n+1) * sizeof(int));
   G->color = malloc((n+1) * sizeof(int));
   for (int i = 1; i < (n+1); i++) {
      G->adjlist[i] = newList();
      G->parent[i] = NIL;
      G->distance[i] = INF;
   }
   return G;
} 

// freeGraph()
// Frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
   for (int i = 1; i <= (*pG)->order; i++) {
      freeList(&(*pG)->adjlist[i]);
   }
   free((*pG)->adjlist);
   free((*pG)->parent);
   free((*pG)->distance);
   free((*pG)->color);
   free(*pG);
   *pG = NULL;
}


// Access functions ----------------------------------------------

// getOrder()
// Returns the order of the Graph
int getOrder(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}


// getSize()
// Returns the size of the Graph
int getSize(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has 
// not yet been called.
int getSource(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (G->source == NIL) {
      return NIL;
   }
   return G->source;
}

// getParent()
// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL 
// if BFS() has not yet been called. Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   if (G==NULL) {
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G)) {
      printf("Graph Error: calling getParent() on an empty tree\n");
      exit(EXIT_FAILURE);
   }
   if (G->source == NIL) {
      return NIL;
   }
   return G->parent[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() 
// has not yet been called. Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
   if (G==NULL) {
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G)) {
      printf("Graph Error: calling getDist() on an empty tree\n");
      exit(EXIT_FAILURE);
   }
   if (G->source == NIL) {
      return INF;
   }
   return G->distance[u];
}


// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends 
// to L the value NIL if no such path exists. Pre: getSource(G)!=NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
   if( L==NULL ){
      printf("List Error: calling getPath() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (G==NULL) {
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (getSource(G)==NIL || u < 1 || u > getOrder(G)) {
      printf("Graph Error: calling getPath() on an empty tree\n");
      exit(EXIT_FAILURE);
   }
   if (G->source == u) {
      append(L, u);
   }
   else if (G->parent[u] == NIL) {
      append(L, NIL);
   }
   else {
      getPath(L, G, G->parent[u]);
      append(L, u);
   }
}


// Manipulation procedures ---------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for (int i = 1; i <= G->order; i++) {
      clear(G->adjlist[i]);
   }
   for  (int i = 1; i <= G->order; i++) {
      G->color[i] = 0;
      G->distance[i] = 0;
      G->parent[i] = 0;
   }
   G->size = 0;
   G->source = NIL;
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to 
// the adjacency List of u.
void addEdge(Graph G, int u, int v) {
   if (G==NULL) {
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
      printf("Verticies Error: error in addArc(), verticies out of bounds\n");
      exit(EXIT_FAILURE);
   }
   if (u != v) {
      addArc(G, u, v);
      addArc(G, v, u);
      G->size--;
   }
}

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but 
// not u to the adjacency List of v).
void addArc(Graph G, int u, int v) {
   if (G==NULL) {
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (G->adjlist[u] == NULL) {
      printf("List Error: calling addArc() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
      printf("Verticies Error: error in addArc(), verticies out of bounds\n");
      exit(EXIT_FAILURE); 
   }
   if (G->adjlist[u] == 0) {
      append(G->adjlist[u], v);
      G->size++;
      return;
   }
   moveFront((G->adjlist[u]));
   while (index(G->adjlist[u]) != -1 && get(G->adjlist[u]) < v) {
      moveNext(G->adjlist[u]);
   }
   if (index(G->adjlist[u]) == -1) {
      append(G->adjlist[u], v);
   }
   else {
      insertBefore(G->adjlist[u], v);
   }
   G->size++;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, 
// and source fields of G accordingly.
void BFS(Graph G, int s) {
   if (G==NULL) {
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (s < 0 || s > G->order) {
      printf("Source Error: error in BFS(), source is not in range\n");
      exit(EXIT_FAILURE);
   }
   G->source = s;
   for (int i = 1; i <= getOrder(G); i++) {
       G->color[i] = 0;
       G->distance[i] = INF;
       G->parent[i] = NIL;
   }
   G->color[s] = 1;
   G->distance[s] = 0;
   G->parent[s] = NIL;
   List L = newList();
   append(L, s);
   while (length(L) > 0) {
      int vertex = front(L);
      deleteFront(L);
      moveFront(G->adjlist[vertex]);
      while (index(G->adjlist[vertex]) >= 0) {
         int idx = get(G->adjlist[vertex]);
         if (G->color[idx] == 0) {
             G->color[idx] = 1;
             G->distance[idx] = G->distance[vertex] + 1;
             G->parent[idx] = vertex;
             append(L, idx);
         }
         moveNext(G->adjlist[vertex]);
      }
      G->color[vertex] = 2;
   }
   freeList(&L);
}


// Other operations --------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for (int i = 1; i <= G->order; i++) {
      fprintf(out, "%d:", i);
      moveFront(G->adjlist[i]);
      while (index(G->adjlist[i]) != -1) {
         fprintf(out, " %d", get(G->adjlist[i]));
         moveNext(G->adjlist[i]);
      }
      fprintf(out, "\n");
   }
}
  
