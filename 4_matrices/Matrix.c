/********************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa4
 * Matrix.c
 * Implementation file for Matrix ADT
 *********************************************/
#include "Matrix.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Structs -------------------------------------------------

// private Entry type
typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
  int column;
  double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
  int size;
  int NNZ;
  List *entries;
} MatrixObj;

// Constructors-Destructors --------------------------------------

// newEntry()
// Returns refernce to new Entry object. Initializes column and value fields.
Entry newEntry(int column, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->column = column;
  E->value = value;
  return E;
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  M->size = n;
  M->NNZ = 0;
  M->entries = malloc((n + 1) * sizeof(List));
  for (int i = 1; i <= n; i++) {
    M->entries[i] = newList();
  }
  return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i <= (*pM)->size; i++) {
      freeList(&(*pM)->entries[i]);
    }

    free((*pM)->entries);
    free(*pM);
    *pM = NULL;
  }
}

// Access functions ----------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling size() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling equals() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size) {
    return 0;
  }
  for (int i = 1; i <= A->size; i++) {
    List N = A->entries[i];
    List M = B->entries[i];
    if (length(N) != length(M)) {
      return 0;
    }
    moveFront(N);
    moveFront(M);
    while (index(N) != -1) {
      if (((Entry)(get(N)))->column != ((Entry)(get(M)))->column) {
        return 0;
      }
      if (((Entry)(get(N)))->value != ((Entry)(get(M)))->value) {
        return 0;
      }
      moveNext(N);
      moveNext(M);
    }
  }
  return 1;
}

// Manipulation procedures ---------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= M->size; i++) {
    clear(M->entries[i]);
  }
  M->NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if (M == NULL) {
    printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  List L = M->entries[i];
  if (x == 0) {
    moveFront(L);
    while (index(L) != -1 && ((Entry)get(L))->column < j) {
      moveNext(L);
    }
    if (index(L) != -1) {
      Entry E = (Entry)get(L);
      freeEntry(&E);
      delete (L);
      M->NNZ--;
    }
  } else if (x != 0) {
    if (length(L) != 0) {
      moveFront(L);
      while (index(L) != -1 && ((Entry)get(L))->column < j)
        moveNext(L);
      if (index(L) == -1) {
        append(L, newEntry(j, x));
        M->NNZ++;
      } else if (((Entry)get(L))->column == j) {
        ((Entry)get(L))->value = x;
      } else {
        insertBefore(L, newEntry(j, x));
        M->NNZ++;
      }
    } else {
      prepend(L, newEntry(j, x));
      M->NNZ++;
    }
  }
}

// Matrix Arithmetic operations ----------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling copy() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  Matrix copy = newMatrix(A->size);
  for (int i = 1; i <= A->size; i++) {
    for (moveFront(A->entries[i]); index(A->entries[i]) != -1;
         moveNext(A->entries[i])) {
      Entry x = (Entry)get(A->entries[i]);
      append(copy->entries[i], newEntry(x->column, x->value));
    }
  }
  copy->NNZ = A->NNZ;
  return copy;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  Matrix trans = newMatrix(A->size);
  for (int i = 1; i <= A->size; i++) {
    for (moveFront(A->entries[i]); index(A->entries[i]) != -1;
         moveNext(A->entries[i])) {
      Entry x = (Entry)get(A->entries[i]);
      append(trans->entries[x->column], newEntry(i, x->value));
    }
  }
  trans->NNZ = A->NNZ;
  return trans;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  Matrix M = copy(A);
  if (x == 0) {
    makeZero(M);
  }
  for (int i = 1; i <= M->size; i++) {
    for (moveFront(M->entries[i]); index(M->entries[i]) != -1;
         moveNext(M->entries[i])) {
      ((Entry)get(M->entries[i]))->value *= x;
    }
  }
  return M;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling sum() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Matrix Error in sum(): Matrix sizes do not match\n");
    exit(EXIT_FAILURE);
  }
  if (A == B) {
    return scalarMult(2, A);
  }
  Matrix M = newMatrix(A->size);
  for (int i = 1; i <= M->size; i++) {
    moveFront(A->entries[i]);
    moveFront(B->entries[i]);
    while (index(A->entries[i]) != -1 && index(B->entries[i]) != -1) {
      Entry a = (Entry)get(A->entries[i]);
      Entry b = (Entry)get(B->entries[i]);
      if (a->column == b->column) {
        if (a->value + b->value != 0) {
          append(M->entries[i], newEntry(a->column, a->value + b->value));
          M->NNZ++;
        }
        moveNext(A->entries[i]);
        moveNext(B->entries[i]);
      } else if (a->column < b->column) {
        append(M->entries[i], newEntry(a->column, a->value));
        M->NNZ++;
        moveNext(A->entries[i]);
      } else if (a->column > b->column) {
        append(M->entries[i], newEntry(b->column, b->value));
        M->NNZ++;
        moveNext(B->entries[i]);
      }
    }
    while (index(A->entries[i]) != -1) {
      Entry a = (Entry)get(A->entries[i]);
      append(M->entries[i], newEntry(a->column, a->value));
      M->NNZ++;
      moveNext(A->entries[i]);
    }
    while (index(B->entries[i]) != -1) {
      Entry b = (Entry)get(B->entries[i]);
      append(M->entries[i], newEntry(b->column, b->value));
      M->NNZ++;
      moveNext(B->entries[i]);
    }
  }
  return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling diff() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Matrix Error in diff(): Matrix sizes do not match\n");
    exit(EXIT_FAILURE);
  }
  if (A == B) {
    return scalarMult(0, A);
  }
  Matrix N = scalarMult(-1, B);
  Matrix M = sum(A, N);
  freeMatrix(&N);
  return M;
}

// dot()
// Helper fucntion for product()
double dot(List N, List M) {
  double prod = 0.0;
  moveFront(N);
  moveFront(M);
  while (index(N) != -1 && index(M) != -1) {
    if (((Entry)get(N))->column < ((Entry)get(M))->column) {
      moveNext(N);
    } else if (((Entry)get(N))->column > ((Entry)get(M))->column) {
      moveNext(M);
    } else if (((Entry)get(N))->column == ((Entry)get(M))->column) {
      prod += (((Entry)get(N))->value * ((Entry)get(M))->value);
      moveNext(N);
      moveNext(M);
    }
  }
  return prod;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling product() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Matrix Error in product(): Matrix sizes do not match\n");
    exit(EXIT_FAILURE);
  }
  Matrix M = newMatrix(A->size);
  if (A->NNZ == 0 || B->NNZ == 0) {
    return M;
  }
  Matrix N = transpose(B);
  for (int i = 1; i <= A->size; i++) {
    if (length(A->entries[i]) > 0) {
      for (int j = 1; j <= N->size; j++) {
        if (length(N->entries[j]) > 0) {
          double prod = dot(A->entries[i], N->entries[j]);
          if (prod != 0) {
            append(M->entries[i], newEntry(j, prod));
            M->NNZ++;
          }
        }
      }
    }
  }
  freeMatrix(&N);
  return M;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero
// rows are not printed. Each non-zero row is represented as one line
// consisting of the row number, followed by a colon, a space, then a
// space separated list of pairs "(col, val)" giving the column numbers
// and non-zero values in that row. The double val will be rounded to 1
// decimal point.
void printMatrix(FILE *out, Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (M->NNZ != 0) {
    for (int i = 1; i <= M->size; i++) {
      if (length(M->entries[i]) != 0) {
        fprintf(out, "%d:", i);
        for (moveFront(M->entries[i]); index(M->entries[i]) != -1;
             moveNext(M->entries[i])) {
          fprintf(out, " (%d, %0.1f)", ((Entry)get(M->entries[i]))->column,
                  ((Entry)get(M->entries[i]))->value);
        }
        fprintf(out, "\n");
      }
    }
  }
}
