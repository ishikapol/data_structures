/***************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa2
* GraphTest.c
* Test for Graph ADT
***************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]){

   Graph A = newGraph(7);
   
   addEdge(A, 1, 3);
   addEdge(A, 2, 3);
   addEdge(A, 2, 5);
   addEdge(A, 3, 6);
   addEdge(A, 1, 2);
   addEdge(A, 5, 7);
   addEdge(A, 6, 7);
   addEdge(A, 4, 6);

   printf("\nGraph: \n");
   printGraph(stdout, A);
   printf("\n");

   printf("Order of A: %d\n", getOrder(A));
   printf("Size of A: %d\n", getSize(A));
   printf("Source of A: %d\n", getSource(A));
   printf("Parent of A: %d\n", getParent(A, 1));

   List B = newList();

   BFS(A, 7);
   printf("\nThe distance from 1 to 7 is %d\n", getDist(A, 1));
   printf("The shortest 1-7 path is: ");
   getPath(B, A, 1);
   printList(stdout, B);
   printf("\n");

   makeNull(A);
   printf("\nNull Graph: \n");
   printGraph(stdout, A);
   printf("\n");

   freeGraph(&A);
   freeList(&B);
   return(0);
}

