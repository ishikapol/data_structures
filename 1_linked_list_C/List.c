/********************************************
* Ishika Pol
* Cruz ID: 8122087
* pa1
* List.c
* Implementation file for List ADT
*********************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs ------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node prev;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors --------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Creates and returns a new empty List.
List newList(void) {
   List L;
   L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
   if (pL!=NULL && *pL!=NULL) {
      while (length(*pL) != 0) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions ----------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   return L->length;
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   if (L->cursor==NULL) {
      L->index = -1;
   }
   return L->index;
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   if (L->length <= 0){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   if (L->length <= 0){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }   
   return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0 || L->index < 0){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL) {
      printf("List Error: cursor is not defined\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor->data;
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Manipulation procedures ---------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
   if( L==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while (length(L) != 0) {
      deleteFront(L);
   }   
   L->cursor = NULL;
   L->index = -1;
}

// set()
// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0 || L->index < 0){
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL) {
      printf("List Error: cursor is not defined\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0){
      L->index = 0;
      L->cursor = L->front;   
   }
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0){
      L->index = length(L)-1;
      L->cursor = L->back;
   }
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor!=NULL && L->index!=0) {
      L->index = index(L) - 1;      
      L->cursor = L->cursor->prev;
   }
   if (L->cursor!=NULL && L->index==0) {
      L->cursor = NULL;
   }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor!=NULL && L->index!=length(L)) {
      L->index = index(L) + 1;
      L->cursor = L->cursor->next;
   }
   if (L->cursor!=NULL && L->index==length(L)) {
      L->cursor = NULL;
   }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
   Node N = newNode(x);   
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL) {
      L->index++;
   }
   if(L->length > 0) {
      N->prev = L->front->prev;
      L->front->prev = N;      
      N->next = L->front; 
      L->front = N;  
   }else{ 
      L->front = L->back = N;
   }
   L->length++;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
   Node N = newNode(x);
  if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }   
   if(L->length > 0) { 
      N->next = L->back->next;      
      L->back->next = N;
      N->prev = L->back;
      L->back = N;      
   }else{ 
      L->front = L->back = N;
   }
   L->length++;
}

// insertBefore()
//  Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
   Node N = newNode(x);
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0 || L->index < 0){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == L->front) {
      N->next = L->front;
      L->front->prev = N;      
      L->front = N;
   }  
   else {
      N->prev = L->cursor->prev;   
      N->next= L->cursor;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
  }
   L->index++;
   L->length++;
}


// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
   Node N = newNode(x);
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0 || L->index < 0){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == L->back) {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
else {
   N->next = L->cursor->next;   
   N->prev = L->cursor;
   L->cursor->next->prev = N;
   L->cursor->next = N;
}
   L->length++;
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0 ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   if( length(L)>1 ) { 
      L->front = L->front->next;
      freeNode(&N);
      L->front->prev = NULL;      
      if (L->index == 0) {
          L->cursor = NULL;
          L->index = -1;
      }
      L->index--;
      L->length--;
   }
   else{
      freeNode(&N); 
      L->front = L->back = NULL;
      L->index = -1;
      L->length = 0; 
   }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0 ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->back;
   if( length(L)>1 ) {   
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
      if (L->index == length(L)-1) {
         L->cursor = NULL;
         L->index = -1;
      }
      L->length--;
   }
   else{
      freeNode(&N);
      L->back = L->front = NULL;
      L->index = -1;
      L->length = 0;
   }
}


// delete()
// Delete cursor element, making cursor undefined.  Pre: length()>0, index()>=0
void delete(List L) {
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   if( L->cursor == NULL || L->length == 0 || L->index == -1){
      return;
   }
   if (L->cursor == L->front) {
      deleteFront(L);
      return;
   }
   if (L->cursor == L->back) {
      deleteBack(L);
      return;
   }
   if( length(L)>1 ) {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&L->cursor);
      L->length--;
      return;
   }
}

// Other operations --------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L) {
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List Copy = newList();
   if (length(L) == 0) {
      return Copy;
   }
   for(N = L->front; N != L->back; N = N->next){
      append(Copy, N->data);
   }
   append(Copy, L->back->data);
   return Copy;
}

