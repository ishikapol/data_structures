/***************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa2
* FindPath.c
* Finds the Shortest Path
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
      addEdge(G, vert1, vert2);
   }
   
   // print out graph
   printGraph(output, G);
   
   // running BFS and getPath and printing out results
   while (fscanf(input, "%d %d", &vert1, &vert2) != EOF && (vert1 != 0 && vert2 != 0)){
      List L = newList();

      BFS(G, vert1);
      getPath(L, G, vert2);
         
      if (getDist(G, vert2) == INF) {
            fprintf(output, "\nThe distance from %d to %d is infinity\n", vert1, vert2);
            fprintf(output, "No %d-%d path exists\n", vert1, vert2);
            fprintf(output, "\n");
      }

      else {
         fprintf(output, "\nThe distance from %d to %d is %d\n", vert1, vert2, getDist(G, vert2));
         fprintf(output, "A shortest %d-%d path is: ", vert1, vert2);
         printList(output, L);
         fprintf(output, "\n");
      }         

      freeList(&L);
   }

   // freeing all memory and closing files
   freeGraph(&G);
   fclose(input);
   fclose(output);
   return 0;
}
