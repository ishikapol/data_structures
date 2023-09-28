/***************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa3
* FindComponents.c
* Finds components of graph
***************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {

   // checking that there are two command line arguements
   if (argc > 3) {
      fprintf(stderr, "Too many arguments supplied. Two arguments expected.\n");
   }
   if (argc < 3) {
      fprintf(stderr, "Not enough arguments supplied. Two arguments expected.\n");
   }

   // opening files
   FILE *input = fopen(argv[1], "r");
   if (input == NULL) {
      fprintf(stderr, "Error: failed to open input file.\n");
   }
   
   FILE *output = fopen(argv[2], "w");
   if (output == NULL) {
      fprintf(stderr, "Error opening file to write output.\n");
   }

   // get size of the graph and create new graph
   int n, vert1, vert2;
   fscanf(input, "%d", &n);
   Graph G = newGraph(n);

   // add verticies from input file to graph
   while (fscanf(input, "%d %d", &vert1, &vert2) != EOF && (vert1 != 0 && vert2 != 0)) {
      addArc(G, vert1, vert2);
   }

   // print out graph
   fprintf(output, "Adjacency list representation of G:\n");
   printGraph(output, G);

   // creating a list with the same length as the graph
   Graph T = transpose(G);
   List L = newList();
   for (int i = 1; i <= getOrder(G); i++) {
      append(L, i);
   }

   // running DFS on the original graph and its transpose
   DFS(G, L);
   DFS(T, L);

   // finding the amount of strongly connected components
   int numofscc;
   for (int i = 1; i <= getOrder(G); i++) {
      if (getParent(T, i) == NIL) {
         numofscc++;
      }
   }
   fprintf(output, "\nG contains %d strongly connected components:\n", numofscc);
  
   // finding the strongly connected components and printing them out 
   int path = numofscc;
   for (int i = 1; i <= numofscc; i++) {
      fprintf(output, "Component %d:", i);
      for (moveFront(L); index(L) != -1; moveNext(L)) {
         if (getParent(T, get(L)) == NIL) {
            path--;
         }
         if (path == (i-1)) {
            fprintf(output, " %d", get(L));
         }
      }
      fprintf(output, "\n");
      path = numofscc; 
   }
         
   // freeing all memory and closing files
   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);
   fclose(input);
   fclose(output);
   return 0;
}
