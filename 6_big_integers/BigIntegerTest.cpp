/***************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa6
 * BigIntegerTest.cpp
 * Test for BigInteger ADT
 ****************************************************/

#include "BigInteger.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  BigInteger A("12345");
  BigInteger B("98760");

  BigInteger C = A + B;
  BigInteger D = B + A;
  BigInteger E = B - B;
  BigInteger F = B - A;
  BigInteger G = B * A;
  BigInteger H = A * A;

  cout << "C = " << C << endl;
  cout << "D = " << D << endl;
  cout << "E = " << E << endl;
  cout << "F = " << F << endl;
  cout << "G = " << G << endl;
  cout << "H = " << H << endl;

  cout << "(A==A) = " << ((A == B) ? "True" : "False") << endl;
  cout << "(A==B) = " << ((A == B) ? "True" : "False") << endl;
  cout << "(A<B)  = " << ((A < B) ? "True" : "False") << endl;
  cout << "(A<D) = " << ((A == B) ? "True" : "False") << endl;
  cout << "(A<=B) = " << ((A <= B) ? "True" : "False") << endl;
  cout << "(A>B)  = " << ((A > B) ? "True" : "False") << endl;
  cout << "(B>E) = " << ((A == B) ? "True" : "False") << endl;
  cout << "(A>=B) = " << ((A >= B) ? "True" : "False") << endl << endl;

  cout << "A compare B =  " << A.compare(B) << endl;
  cout << "C compare D =  " << C.compare(D) << endl;
  cout << "G compare H =  " << G.compare(H) << endl;

  cout << endl;

  return EXIT_SUCCESS;
}
