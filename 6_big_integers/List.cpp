/*****************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa6
 * List.cpp
 * Implementation file for List ADT
 ******************************************************/

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Private Constructor -----------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
  data = x;
  prev = nullptr;
  next = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
  frontDummy = new Node(-1);
  backDummy = new Node(0);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List(const List &L) {
  frontDummy = new Node(-1);
  backDummy = new Node(0);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
  Node *N = L.frontDummy->next;
  while (N != L.backDummy) {
    this->insertAfter(N->data);
    moveNext();
    N = N->next;
  }
  moveFront();
}

// Destructor
List::~List() {
  while (num_elements > 0) {
    clear();
  }
  delete frontDummy;
  delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.int
int List::length() const { return num_elements; }

// front()
// Returns the front element in this List.
// pre : length() > 0
ListElement List::front() const {
  if (num_elements == 0) {
    throw std::length_error("List: front(): empty List");
  }
  return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
  if (num_elements == 0) {
    throw std::length_error("List: back(): empty List");
  }
  return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
  if (pos_cursor < 0 || pos_cursor > length()) {
    throw std::length_error("List: position(): cursor not in list");
  }
  return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
  if (position() >= length()) {
    throw std::length_error(
        "List: peekNext(): element after cursor not in list");
  }
  return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
  if (position() <= 0) {
    throw std::length_error(
        "List: peekPrev(): element before cursor not in list");
  }
  return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
  moveFront();
  while (length() > 0) {
    eraseAfter();
  }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
  if (num_elements == 0) {
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    return;
  }
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
  return;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
  if (num_elements == 0) {
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    return;
  }
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = length();
  return;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. pre: position()<length()
ListElement List::moveNext() {
  if (position() >= length()) {
    throw std::length_error("List: moveNext(): cursor not in list");
  }
  beforeCursor = beforeCursor->next;
  afterCursor = afterCursor->next;
  pos_cursor++;
  return afterCursor->prev->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that was
// passed over. pre: position()>0
ListElement List::movePrev() {
  if (position() <= 0) {
    throw std::length_error("List: movePrev(): cursor not in list");
  }
  beforeCursor = beforeCursor->prev;
  afterCursor = afterCursor->prev;
  pos_cursor--;
  return beforeCursor->next->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
  Node *N = new Node(x);
  N->next = afterCursor;
  N->prev = beforeCursor;
  afterCursor->prev = N;
  beforeCursor->next = N;
  afterCursor = N;
  num_elements++;
  return;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
  Node *N = new Node(x);
  N->next = afterCursor;
  N->prev = beforeCursor;
  afterCursor->prev = N;
  beforeCursor->next = N;
  beforeCursor = N;
  num_elements++;
  pos_cursor++;
  return;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
  if (position() < length()) {
    Node *N = new Node(x);
    N->next = afterCursor->next;
    N->prev = beforeCursor;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor = N;
  }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
  if (position() > 0) {
    Node *N = new Node(x);
    N->prev = beforeCursor->prev;
    N->next = afterCursor;
    beforeCursor->next = afterCursor;
    afterCursor->prev = N;
    beforeCursor = N;
  }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
  if (position() >= length()) {
    throw std::length_error("List: eraseAfter(): cursor at end of list");
  }
  Node *N = afterCursor;
  afterCursor = afterCursor->next;
  beforeCursor->next = afterCursor;
  afterCursor->prev = beforeCursor;
  num_elements--;
  delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
  if (position() <= 0) {
    throw std::length_error("List: eraseBefore(): cursor at beginning of list");
  }
  Node *N = beforeCursor;
  beforeCursor = beforeCursor->prev;
  beforeCursor->next = afterCursor;
  afterCursor->prev = beforeCursor;
  pos_cursor--;
  num_elements--;
  delete N;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
  Node *N = new Node(x);
  while (position() < length()) {
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    pos_cursor++;
    if (beforeCursor->data == N->data) {
      return pos_cursor;
    }
  }
  pos_cursor = length();
  return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
  Node *N = new Node(x);
  while (position() > 0) {
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    if (afterCursor->data == N->data) {
      return pos_cursor;
    }
  }
  pos_cursor = 0;
  return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the
// frontmost occurrance of each element, and removing all other occurances.
// The cursor is not moved with respect to the retained elements, i.e. it
// lies between the same two retained elements that it did before cleanup()
// was called.
void List::cleanup() {
  Node *curr = nullptr;
  Node *aftercurr = nullptr;
  Node *cursor = frontDummy->next;
  int cursor_position = 0;
  while (cursor != backDummy) {
    cursor_position += 1;
    curr = cursor;
    aftercurr = cursor->next;
    while (aftercurr != backDummy) {
      if (cursor->data == aftercurr->data) {
        curr->next = aftercurr->next;
        aftercurr->next->prev = curr;
        delete aftercurr;
        aftercurr = curr->next;
        num_elements--;
        if (cursor_position < pos_cursor) {
          pos_cursor--;
        }
      } else {
        curr = aftercurr;
        aftercurr = curr->next;
      }
    }
    cursor = cursor->next;
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const {
  List K;
  Node *N = this->frontDummy->next;
  Node *M = L.frontDummy->next;
  while (N != this->backDummy) {
    K.insertBefore(N->data);
    N = N->next;
  }
  while (M != L.backDummy) {
    K.insertBefore(M->data);
    M = M->next;
  }
  K.moveFront();
  return K;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
  Node *N = nullptr;
  std::string s = "";
  for (N = frontDummy; N != nullptr; N = N->next) {
    s += std::to_string(N->data) + " ";
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const {
  bool eq = false;
  Node *N = nullptr;
  Node *M = nullptr;
  eq = (this->num_elements == R.num_elements);
  N = this->frontDummy;
  M = R.frontDummy;
  while (eq && N != nullptr) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream &operator<<(std::ostream &stream, const List &L) {
  return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List &A, const List &B) { return A.List::equals(B); }

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L) {
  if (this != &L) {
    List temp = L;
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(num_elements, temp.num_elements);
  }
  return *this;
}
