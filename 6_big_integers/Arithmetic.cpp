/******************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa6
 * Arithmetic.cpp
 * Prints out arithmetic operations done on big integers
 *******************************************/

#include "BigInteger.h"
#include "List.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {

  // checking that there are two command line arguments
  if (argc > 3) {
    cerr << "Too many arguments supplied. Two arguments expected." << endl;
  }

  if (argc < 3) {
    cerr << "Not enough arguments supplied. Two arguments expected." << endl;
  }

  // opening files
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  // initializing strings to store big ints
  string line1, blank, line2;

  // reading the big ints and storing them in the string
  getline(input, line1);
  getline(input, blank);
  getline(input, line2);

  // initialize and assign values to big ints
  BigInteger two("2");
  BigInteger three("3");
  BigInteger nine("9");
  BigInteger sixteen("16");

  BigInteger A(line1);
  BigInteger B(line2);
  BigInteger C = A + B;
  BigInteger D = A - B;
  BigInteger E = A - A;
  BigInteger F = (three * A) - (two * B);
  BigInteger G = A * B;
  BigInteger H = A * A;
  BigInteger I = B * B;
  BigInteger J = (nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B));

  // print out the arithmetic operations
  output << A.to_string() << endl << endl;
  output << B.to_string() << endl << endl;
  output << C.to_string() << endl << endl;
  output << D.to_string() << endl << endl;
  output << E.to_string() << endl << endl;
  output << F.to_string() << endl << endl;
  output << G.to_string() << endl << endl;
  output << H.to_string() << endl << endl;
  output << I.to_string() << endl << endl;
  output << J.to_string() << endl << endl;

  // close all files and return 0
  input.close();
  output.close();
  return 0;
}
