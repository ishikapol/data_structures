/***************************************************
* Ishika Pol
* Cruz ID: 8122087
* pa3
* GraphTest.c
* Test for Graph ADT
***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]){

   Graph A = newGraph(7);
   
   addArc(A, 1, 4);
   addArc(A, 2, 3);
   addArc(A, 2, 5);
   addArc(A, 3, 6);
   addArc(A, 1, 2);
   addArc(A, 5, 7);
   addArc(A, 6, 7);
   addArc(A, 4, 6);
   addArc(A, 7, 4);
   addArc(A, 5, 6);
   addArc(A, 3, 1);

   printf("\nGraph A: \n");
   printGraph(stdout, A);

   Graph C = copyGraph(A);
   Graph T = transpose(A);

   printf("\n");
   printf("Copy of A: \n");
   printGraph(stdout, C);
   printf("\n");
   printf("Transpose of A: \n");
   printGraph(stdout, T);

   printf("\n");
   printf("Before DFS\n");
   printf("________________\n");
   printf("\n");

   printf("Order of A: %d\n", getOrder(A));
   printf("Size of A: %d\n", getSize(A));
   printf("\n");
   printf("x:  d  f  p\n");
   for(int i=1; i<=7; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
   }

   printf("\n");
   printf("\n");
   printf("After DFS\n");
   printf("________________\n");
   printf("\n");

   List B = newList();
   for (int i = 1; i <= 7; i++) {
      append(B, i);
   }

   DFS(A, B);
   printf("List after DFS: ");
   printList(stdout, B);
   printf("\n");

   printf("Order of A: %d\n", getOrder(A));
   printf("Size of A: %d\n", getSize(A));
   printf("\n");
   printf("x:  d  f  p\n");
   for(int i=1; i<=7; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
   }

   printf("\n");
   printf("\n");
   printf("After DFS with Transpose Graph\n");
   printf("________________\n");
   printf("\n");

   DFS(T, B);
   printf("Transpose List after DFS: ");
   printList(stdout, B);
   printf("\n");

   printf("Order of T: %d\n", getOrder(T));
   printf("Size of T: %d\n", getSize(T));
   printf("\n");
   printf("x:  d  f  p\n");
   for(int i=1; i<=7; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }

   freeGraph(&A);
   freeGraph(&T);
   freeGraph(&C);
   freeList(&B);
   return(0);
}


