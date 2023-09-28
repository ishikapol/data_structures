/***************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa4
 * Sparse.c
 * Uses the sparseness of a matrix to compute matrix operations
 ***************************************************/

#include "List.h"
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

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

  // scan in all inputs from file and create new matrices
  int n, a, b;
  fscanf(input, " %d %d %d", &n, &a, &b);
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);

  // assign values from input file to matrices
  int row, column;
  double value;
  for (int i = 1; i <= a; i++) {
    fscanf(input, " %d %d %lf", &row, &column, &value);
    changeEntry(A, row, column, value);
  }

  for (int i = 1; i <= b; i++) {
    fscanf(input, " %d %d %lf", &row, &column, &value);
    changeEntry(B, row, column, value);
  }

  // perform matrix operations
  fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(output, A);
  fprintf(output, "\n");

  fprintf(output, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(output, B);
  fprintf(output, "\n");

  Matrix C = scalarMult(1.5, A);
  fprintf(output, "(1.5)*A =\n");
  printMatrix(output, C);
  fprintf(output, "\n");

  Matrix D = sum(A, B);
  fprintf(output, "A+B =\n");
  printMatrix(output, D);
  fprintf(output, "\n");

  Matrix E = sum(A, A);
  fprintf(output, "A+A =\n");
  printMatrix(output, E);
  fprintf(output, "\n");

  Matrix F = diff(B, A);
  fprintf(output, "B-A =\n");
  printMatrix(output, F);
  fprintf(output, "\n");

  Matrix G = diff(A, A);
  fprintf(output, "A-A =\n");
  printMatrix(output, G);
  fprintf(output, "\n");

  Matrix H = transpose(A);
  fprintf(output, "Transpose(A) =\n");
  printMatrix(output, H);
  fprintf(output, "\n");

  Matrix I = product(A, B);
  fprintf(output, "A*B =\n");
  printMatrix(output, I);
  fprintf(output, "\n");

  Matrix J = product(B, B);
  fprintf(output, "B*B =\n");
  printMatrix(output, J);
  fprintf(output, "\n");

  // freeing all memory and closing files
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&H);
  freeMatrix(&I);
  freeMatrix(&J);
  fclose(input);
  fclose(output);
  return 0;
}
