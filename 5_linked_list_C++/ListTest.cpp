/***************************************************
 * Ishika Pol
 * Cruz ID: 8122087
 * pa5
 * ListTest.cpp
 * Test client for List ADT
 ***************************************************/

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  int i;
  List A, B;
  for (i = 1; i <= 12; i++) {
    A.insertAfter(i);
    B.insertBefore(i);
  }

  cout << endl;
  cout << "A = " << A << endl;
  cout << "A.position() = " << A.position() << endl;
  cout << "B = " << B << endl;
  cout << "B.position() = " << B.position() << endl;
  cout << endl;

  A.moveBack();
  B.moveFront();

  cout << "A = " << A << endl;
  cout << "A.position() = " << A.position() << endl;
  cout << "B = " << B << endl;
  cout << "B.position() = " << B.position() << endl;

  cout << endl << "A: ";
  A.moveBack();
  for (i = 1; i <= 4; i++) {
    cout << A.movePrev() << " ";
  }
  cout << endl << "A.position() = " << A.position() << endl;

  cout << endl << "B: ";
  B.moveFront();
  for (i = 1; i <= 8; i++) {
    cout << B.moveNext() << " ";
  }
  cout << endl << "B.position() = " << B.position() << endl;

  cout << endl;
  cout << "A==B is " << (A == B ? "true" : "false") << endl;
  cout << endl;

  cout << B.findNext(11) << endl;
  cout << B << endl;
  B.eraseBefore();
  B.eraseAfter();
  cout << B << endl;
  cout << B.position() << endl;
  cout << A.findPrev(3) << endl;
  A.eraseBefore();
  A.eraseAfter();
  cout << B << endl;
  cout << B.position() << endl;
  cout << endl;

  for (i = 9; i >= 1; i--) {
    A.insertAfter(i);
    A.movePrev();
  }
  cout << "A = " << A << endl;
  for (i = 1; i <= 10; i++) {
    A.moveNext();
  }
  cout << A.position() << endl;
  A.cleanup();
  cout << "A = " << A << endl;
  cout << A.position() << endl;
  cout << endl;

  List C = A;
  cout << "C==A is " << (C == A ? "true" : "false") << endl;

  cout << endl;

  cout << "A = " << A << endl;
  cout << A.position() << endl;
  cout << "B = " << B << endl;
  cout << B.position() << endl;
  List D = A.concat(B);
  cout << "D = " << D << endl;
  cout << "length: " << D.length() << endl;
  cout << "front: " << D.front() << endl;
  cout << "back: " << D.back() << endl;
  cout << "position: " << D.position() << endl;
  for (i = 1; i <= 7; i++) {
    cout << "peekNext: " << D.peekNext() << endl;
    D.insertBefore(-i);
    cout << D.moveNext() << endl;
  }
  cout << "D = " << D << endl;

  cout << endl;

  return (EXIT_SUCCESS);
}
