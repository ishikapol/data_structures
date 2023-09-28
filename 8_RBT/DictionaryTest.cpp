/***************************************************
 * Ishika Pol
 * Cruz ID: 8122087
 * pa8
 * DictionaryTest.cpp
 * Test client for Dictionary ADT
 ***************************************************/

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string s;
  int x;
  string S[] = {"jinx",    "five", "found", "pear",
                "anxious", "we",   "flour", "perfect"};

  Dictionary A;
  Dictionary B;

  cout << endl;

  for (int i = 0; i < 4; i++) {
    A.setValue(S[i], i + 1);
  }

  cout << "A.size() = " << A.size() << endl << A << endl;

  B = A;
  cout << B << endl;

  B.setValue("pear", 2);

  Dictionary C = B;

  cout << "C.size() = " << C.size() << endl << C << endl;

  cout << "A==A is " << (A == A ? "true" : "false") << endl;
  cout << "B==A is " << (B == A ? "true" : "false") << endl;
  cout << "C==B is " << (C == B ? "true" : "false") << endl << endl;

  cout << B.getValue("five") << endl;
  B.getValue("five") *= 3;
  cout << B.getValue("five") << endl << endl;

  cout << "A.size() = " << A.size() << endl << A << endl;
  cout << A.pre_string() << endl;

  for (C.end(); C.hasCurrent(); C.prev()) {
    s = C.currentKey();
    x = C.currentVal();
    cout << "(" + s + ", " << x << ") ";
  }
  cout << endl << endl;

  return (EXIT_SUCCESS);
}
