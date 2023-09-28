/******************************************
* Ishika Pol
* Cruz ID: 8122087
* pa1
* Lex.c
* Main Program
*******************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include"List.h"
#define MAX_LEN 300

int main(int argc, char* argv[]){
   
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
  
   // counting the number of lines in the input file
   char line[MAX_LEN]; 
   int numoflines = 0;
   while (fgets(line, MAX_LEN, input) != NULL) {
      numoflines++;
   }

   // creating the array
   char **lines = malloc(numoflines * sizeof(char *));

   // reset input file
   fclose(input);
   input = fopen(argv[1], "r");
   
   for (int a = 0; a < numoflines; a++) {
      lines[a] = malloc(sizeof(line));
   }

   // copying over data from input file to array
   int n = 0; 
   while (fgets(line, MAX_LEN, input) != NULL) {
      strcpy(lines[n], line);
      n++;     
   }

   // creating new list to store sorted data
   List Lex = newList();
   append(Lex, 0);
  
   for (int j = 1; j<numoflines; j++) {
      moveFront(Lex);
      for (int m = length(Lex) - 1; m >= 0; m--) {
         if (strcmp(lines[j], lines[get(Lex)]) < 0 || strcmp(lines[j], lines[get(Lex)]) == 0) {
            insertBefore(Lex, j);
            break;
         }
         else if (strcmp(lines[j], lines[get(Lex)]) > 0) {
            if (index(Lex) == length(Lex)-1) {
               append(Lex, j);
               break;
            }
            else {
               moveNext(Lex);
            }
         }
      }
   } 
   
   // storing data from Lex into output file
   for (moveFront(Lex); index(Lex)>=0; moveNext(Lex)) {
      fprintf(output, "%s", lines[get(Lex)]);
   }

   // freeing all memory and closing files
   for (int b = 0; b < numoflines; b++) {
      free(lines[b]);
   }
   free(lines);
   freeList(&Lex);
   fclose(input);
   fclose(output);
   return 0;
}
