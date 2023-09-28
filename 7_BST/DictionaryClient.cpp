/***************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa7
 * DictionaryClient.cpp
 * A test client for the Dictionary ADT
 ****************************************************/

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string s;
  int x;
  string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

  cout << "a" << endl;

  Dictionary A;
  Dictionary B;
  cout << "b" << endl;
  cout << endl;

  // insert some pairs into A
  for (int i = 0; i < 8; i++) {
    cout << "c" << endl;
    A.setValue(S[i], i + 1);
  }
  cout << "d" << endl;
  // call operator=()
  B = A;

  cout << "A.size() = " << A.size() << endl << A << endl;
  cout << "B.size() = " << B.size() << endl << B << endl;

  B.setValue("bar", 9);

  // call copy constructor
  Dictionary C = B;

  cout << "B.size() = " << B.size() << endl << B << endl;
  cout << "C.size() = " << C.size() << endl << C << endl;

  // check operator==()
  cout << "A==B is " << (A == B ? "true" : "false") << endl;
  cout << "B==C is " << (B == C ? "true" : "false") << endl;
  cout << "C==A is " << (C == A ? "true" : "false") << endl << endl;

  // perform alterations on A
  cout << A.getValue("happy") << endl;
  A.getValue("happy") *= 10; // change the value associated with "happy"
  cout << A.getValue("happy") << endl << endl;
  A.remove("one");
  A.remove("two");

  // check state of A
  cout << "A.size() = " << A.size() << endl << A << endl;
  cout << A.pre_string() << endl;

  // do forward iteration on B
  for (B.begin(); B.hasCurrent(); B.next()) {
    s = B.currentKey();
    x = B.currentVal();
    cout << "(" + s + ", " << x << ") ";
  }
  cout << endl << endl;

  // do reverse iteration on C
  for (C.end(); C.hasCurrent(); C.prev()) {
    s = C.currentKey();
    x = C.currentVal();
    cout << "(" + s + ", " << x << ") ";
  }
  cout << endl << endl;

  // check exceptions
  try {
    A.getValue("blah");
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.remove("blah");
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.currentKey();
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.currentVal();
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.next();
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }
  try {
    A.prev();
  } catch (logic_error &e) {
    cout << e.what() << endl;
    cout << "   continuing without interruption" << endl;
  }

  cout << endl;

  return (EXIT_SUCCESS);
}
