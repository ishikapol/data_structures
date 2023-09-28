/***************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa4
 * ListTest.c
 * Test for List ADT
 ***************************************************/

int main(int argc, char *argv[]) {

  List A = newList();
  List B = newList();
  int X[] = {3, 11, 32, 53, 46, 545, 63, 17, 8};

  for (i = 1; i <= 20; i++) {
    append(A, &X[i]);
    prepend(B, &X[i]);
  }
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
    printf("%d ", *(int *)get(B));
  }
  printf("\n");

  List C = newList();
  moveFront(B);
  while (index(B) >= 0) {
    append(C, get(B));
    moveNext(B);
  }
  for (moveFront(C); index(C) >= 0; moveNext(C)) {
    printf("%d ", *(int *)get(C));
  }
  printf("\n");
  equal = (length(B) == length(C));
  moveFront(B);
  moveFront(C);
  while (index(B) >= 0 && equal) {
    equal = (get(B) == get(C));
    moveNext(B);
    moveNext(C);
  }
  printf("B equals C is %s\n", (equal ? "true" : "false"));

  moveFront(A);
  for (int i = 0; i < 3; i++) {
    moveNext(A); // at index 3
  }
  printf("index(A)=%d\n", index(A));
  insertBefore(A, &u); // now at index 2
  printf("index(A)=%d\n", index(A));
  for (int i = 0; i < 10; i++) {
    moveNext(A); // at index 12
  }
  printf("index(A)=%d\n", index(A));

  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));

  freeList(&A);
  freeList(&B);
  freeList(&C);

  return (0);
}
