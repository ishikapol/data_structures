/******************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa7
 * Order.cpp
 * Orders a dictionary
 *******************************************/

#include "Dictionary.h"
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
  ifstream input;
  input.open(argv[1]);
  if (!input.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
    return (EXIT_FAILURE);
  }

  ofstream output;
  output.open(argv[2]);
  if (!output.is_open()) {
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return (EXIT_FAILURE);
  }

  // initialize variables
  Dictionary A;
  string line;
  string tokenBuffer;
  string token;
  size_t begin, end, line_length;
  int i, token_count, line_count;

  // read in lines and store words in dictionary (from fileio.cpp)
  while (getline(input, line)) {
    line_count++;
    line_length = line.length();
    token_count = 0;
    tokenBuffer = "";
    begin = min(line.find_first_not_of(" ", 0), line_length);
    end = min(line.find_first_of(" ", begin), line_length);
    token = line.substr(begin, end - begin);
    while (token != "") {
      tokenBuffer += "" + token;
      token_count++;
      begin = min(line.find_first_not_of(" ", end + 1), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end - begin);
    }
    A.setValue(tokenBuffer, i + 1);
    i++;
  }

  // print out words in order
  output << A.to_string() << endl << endl;
  output << A.pre_string() << endl;

  // close all files and return 0
  input.close();
  output.close();
  return 0;
}
