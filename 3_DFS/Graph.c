/********************************************
* Ishika Pol
* Cruz ID: 8122087
* pa3
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
   int time;
   int *parent;
   int *discover;
   int *finish;
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
   G->time = UNDEF;
   G->adjlist = malloc((n+1) * sizeof(List));
   G->parent = malloc((n+1) * sizeof(int));
   G->discover = malloc((n+1) * sizeof(int));
   G->finish = malloc((n+1) * sizeof(int));
   G->color = malloc((n+1) * sizeof(int));
   for (int i = 1; i <= n; i++) {
      G->adjlist[i] = newList();
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
      G->color[i] = 0;
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
   free((*pG)->discover);
   free((*pG)->finish);
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
   return G->parent[u];
}

// getDiscover()
// Returns the discover time of vertex u. Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u) {
   if (G==NULL) {
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G)) {
      printf("Graph Error: calling getDiscover() on an empty tree\n");
      exit(EXIT_FAILURE);
   }
   return G->discover[u];
}

// getFinish()
// Returns the finish time of vertex u. Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) {
   if (G==NULL) {
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (u < 1 || u > getOrder(G)) {
      printf("Graph Error: calling getFinish() on an empty tree\n");
      exit(EXIT_FAILURE);
   }
   return G->finish[u];
}


// Manipulation procedures ---------------------------------------

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

// visit()
// Helper fucntion for DFS
void visit(Graph G, List S, int x) {
   if (G==NULL) {
      printf("Graph Error: calling visit() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (S == NULL) {
      printf("List Error: calling visit() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   G->time++;
   G->discover[x] = G->time;
   G->color[x] = 1;
   for (moveFront(G->adjlist[x]); index(G->adjlist[x]) >= 0; moveNext(G->adjlist[x])) {
      int idx = get(G->adjlist[x]);
      if (G->color[idx] == 0) {
         G->parent[idx] = x;
         visit(G, S, idx);
      }
   }
   G->color[x] = 2;
   G->time++;
   G->finish[x] = G->time;
   prepend(S, x);
}

// DFS()
// Performs the depth first search algorithm on G. Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
   if (G==NULL) {
      printf("Graph Error: calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if (S == NULL) {
      printf("List Error: calling DFS() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(S) != getOrder(G)) {
      printf("List Error: error in DFS(), list length doesn't match graph order\n");
      exit(EXIT_FAILURE);
   }
   for (int i = 1; i <= getOrder(G); i++) {
      G->color[i] = 0;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   List L = copyList(S);
   clear(S);
   G->time = 0;
   for (moveFront(L); index(L) >= 0; moveNext(L)) {
      int idx = get(L);
      if (G->color[idx] == 0) {
         visit(G, S, idx);
      }
   }
   freeList(&L);
}


// Other operations --------------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph trans = newGraph(getOrder(G));
   for (int i = 1; i <= G->order; i++) {
      moveFront(G->adjlist[i]);
      while (index(G->adjlist[i]) != -1) {
         int x = get(G->adjlist[i]);
         addArc(trans, x, i);
         moveNext(G->adjlist[i]);
      }
   }
   return trans;
}

// copyGraph()
// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
   if (G==NULL) {
      printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph copy = newGraph(getOrder(G));
   for (int i = 1; i <= G->order; i++) {
      moveFront(G->adjlist[i]);
      while (index(G->adjlist[i]) != -1) {
         int x = get(G->adjlist[i]);
         addArc(copy, i, x);
         moveNext(G->adjlist[i]);
      }
   }
   return copy;
}


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
  
