/******************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa5
 * Shuffle.cpp
 * Shuffles a list
 *******************************************/

#include "List.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std;

// shuffle()
// Alters the List& arguement D by performing one shuffle operation
void shuffle(List &D) {
  List a, b;
  int middle = (D.length()) / 2;
  D.moveFront();
  for (int i = 0; i < D.length(); i++) {
    if (i < middle) {
      a.insertBefore(D.peekNext());
      D.moveNext();
    } else {
      b.insertBefore(D.peekNext());
      D.moveNext();
    }
  }
  D.clear();
  while (a.length() != 0 || b.length() != 0) {
    if (b.length() != 0) {
      b.moveFront();
      D.insertBefore(b.peekNext());
      b.eraseAfter();
    }
    if (a.length() != 0) {
      a.moveFront();
      D.insertBefore(a.peekNext());
      a.eraseAfter();
    }
  }
}

int main(int argc, char **argv) {

  // checking that there is one command line arguement
  if (argc > 2) {
    cerr << "Too many arguments supplied. One arguement expected." << endl;
  }

  if (argc < 2) {
    cerr << "Not enough arguments supplied. One arguement expected." << endl;
  }

  // initialize lists and variables
  List cards, copy;
  int numofcards;
  int numofshuffles;

  // read in max number of cards from command line
  numofcards = atoi(argv[1]);

  // print out the top of table
  cout << "deck size" << setw(20) << "shuffle count" << endl;
  cout << "------------------------------" << endl;

  // iterate though the max number of cards
  for (int i = 1; i <= numofcards; i++) {

    // create list for each iteration
    for (int j = 1; j <= i; j++) {
      cards.insertBefore(j);
      copy = cards;
    }
    // shuffle cards once to start the loop
    shuffle(cards);
    numofshuffles++;

    // keep shuffling until the list matches the original list
    while ((cards == copy) == 0) {
      shuffle(cards);
      numofshuffles++;
    }

    // print out final stats
    cout << " " << i << setw(20) << " " << numofshuffles << endl;
    cards.clear();
    numofshuffles = 0;
  }

  return (EXIT_SUCCESS);
}
