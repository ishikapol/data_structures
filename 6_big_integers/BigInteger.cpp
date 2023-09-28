/*****************************************************
 * Ishika Pol
 * Cruz ID: ipol@ucsc.edu
 * pa6
 * BigInteger.cpp
 * Implementation file for BigInteger ADT
 *******************************************************/

#include "BigInteger.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#define power 9
#define base 1000000000

using namespace std;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() {
  List digits;
  signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
  if (s[0] != '+' && s[0] != '-' && !(isdigit(s[0]))) {
    throw invalid_argument("BigInteger: Constructor: non-numeric string");
  }
  if (s[0] == '+') {
    s = s.substr(1, s.length() - 1);
    signum = 1;
  } else if (s[0] == '-') {
    s = s.substr(1, s.length() - 1);
    signum = -1;
  } else {
    signum = 1;
  }
  string numbers = "";
  for (int i = s.length() - power; i >= 1 - power; i -= power) {
    if (i >= 0 && !isdigit(s[i])) {
      throw invalid_argument(
          "BigInteger: Constructor: non-numeric string middle");
    }
    if (i <= 0) {
      numbers = s.substr(0, i + power);
      digits.insertAfter(stol(numbers));
    } else {
      numbers = s.substr(i, power);
      digits.insertAfter(stol(numbers));
    }
  }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger &N) {
  digits = N.digits;
  signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const { return signum; }

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger &N) const {
  string thisbi = this->digits.to_string();
  string Nbi = N.digits.to_string();
  if (sign() == 1 && N.sign() == -1) {
    return 1;
  }
  if (sign() == -1 && N.sign() == 1) {
    return -1;
  }
  if (sign() == -1 && N.sign() == -1) {
    if (thisbi.length() < Nbi.length()) {
      return 1;
    }
    if (thisbi.length() > Nbi.length()) {
      return -1;
    } else {
      for (size_t i = 0; i < thisbi.length(); i++) {
        if (thisbi[i] < Nbi[i]) {
          return 1;
        }
        if (thisbi[i] > Nbi[i]) {
          return -1;
        }
      }
    }
  }
  if (sign() == 1 && N.sign() == 1) {
    if (thisbi.length() > Nbi.length()) {
      return 1;
    }
    if (thisbi.length() < Nbi.length()) {
      return -1;
    } else {
      for (size_t i = 1; i < thisbi.length(); i++) {
        if (thisbi[i] > Nbi[i]) {
          return 1;
        }
        if (thisbi[i] < Nbi[i]) {
          return -1;
        }
      }
    }
  }
  return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
  signum = 0;
  digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
  if (sign() == 0) {
    return;
  }
  signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger &N) const {
  BigInteger A;
  BigInteger thisbi = *this;
  BigInteger Nbi = N;

  List listthis = thisbi.digits;
  List listN = Nbi.digits;
  List listA = A.digits;

  if (thisbi.sign() == 0 && Nbi.sign() == 0) {
    return Nbi;
  }
  if (thisbi.sign() == 0 && Nbi.sign() != 0) {
    return thisbi;
  }
  if (thisbi.sign() != 0 && Nbi.sign() == 0) {
    return Nbi;
  }
  if (thisbi.sign() == -1 && Nbi.sign() == 1) {
    thisbi.negate();
    A = N.sub(thisbi);
    thisbi.negate();
    return A;
  }
  if (thisbi.sign() == 1 && Nbi.sign() == -1) {
    Nbi.negate();
    A = thisbi.sub(Nbi);
    A.negate();
    return A;
  }

  listthis.moveBack();
  listN.moveBack();

  long carry = 0;
  long idx;
  for (int i = listthis.position(); i > 0; i--) {
    if (listN.position() > 0) {
      idx = listthis.peekPrev() + listN.peekPrev() + carry;
      carry = idx / base;
      idx = idx % base;
      listA.insertAfter(idx);
      listthis.movePrev();
      listN.movePrev();
    }
  }
  while (listthis.position() > 0) {
    idx = listthis.peekPrev() + carry;
    carry = idx / base;
    idx = idx % base;
    listA.insertAfter(idx);
    listthis.movePrev();
  }
  while (listN.position() > 0) {
    idx = listN.peekPrev() + carry;
    carry = idx / base;
    idx = idx % base;
    listA.insertAfter(idx);
    listN.movePrev();
  }
  if (carry != 0) {
    listA.insertAfter(carry);
  }
  A.digits = listA;
  return A;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger &N) const {
  BigInteger A;
  BigInteger thisbi = *this;
  BigInteger Nbi = N;

  List listthis = thisbi.digits;
  List listN = Nbi.digits;
  List listA = A.digits;

  if (thisbi.sign() == 0 && Nbi.sign() == 0) {
    return Nbi;
  }

  if (thisbi.sign() == 0 && Nbi.sign() != 0) {
    Nbi.negate();
    return Nbi;
  }

  if (thisbi.sign() != 0 && Nbi.sign() == 0) {
    return thisbi;
  }

  if (thisbi.sign() == -1 && Nbi.sign() == 1) {
    thisbi.negate();
    A = Nbi.add(thisbi);
    return A;
  }

  if (thisbi.sign() == 1 && Nbi.sign() == -1) {
    Nbi.negate();
    A = Nbi.add(thisbi);
    A.negate();
    return A;
  }
  if (thisbi.sign() == -1 && Nbi.sign() == -1) {
    thisbi.negate();
    Nbi.negate();
    A = thisbi.sub(Nbi);
    A.negate();
    return A;
  }

  if (thisbi == Nbi) {
    return A;
  }

  if (thisbi > Nbi) {
    A = Nbi.sub(thisbi);
    A.negate();
    return A;
  }

  listthis.moveBack();
  listN.moveBack();
  long carry = 0;
  long idx;

  for (int i = listthis.position(); i > 0; i--) {
    if (listthis.peekPrev() <= listN.peekPrev()) {
      idx = listN.peekPrev() - carry - listthis.peekPrev();
      if (listN.peekPrev() > 0) {
        carry = 0;
      }
    } else {
      idx = listN.peekPrev() + base - listthis.peekPrev() - carry;
      carry = 1;
    }
    listA.insertAfter(idx);
    listthis.movePrev();
    listN.movePrev();
  }
  while (listN.position() > 0) {
    if ((listN.peekPrev() - carry) <= 0) {
      idx = listN.peekPrev() - carry;
      if (listN.peekPrev() > 0) {
        carry = 0;
      }
    } else {
      idx = listN.peekPrev() + base - carry;
      carry = 1;
    }
    listA.insertAfter(idx);
    listN.movePrev();
  }
  A.digits = listA;
  A.signum = 1;
  return A;
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const {
  BigInteger M;
  return M;
}

// Other Functions ---------------------------------------------------------

// padd()
// Helper function for to_string(), inserts zeros in base 10 digits (found
// online)
int padd(int x) {
  if (x / 10 == 0) {
    return 1;
  } else {
    return 1 + padd(x / 10);
  }
}

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
  string s = "";
  if (sign() == 0) {
    s += '0';
  } else {
    if (sign() == -1) {
      s += '-';
    }
    digits.moveFront();
    for (int i = digits.position(); i < digits.length(); i++) {
      if (i != 0) {
        int count = padd(digits.peekNext());
        for (int n = 0; n < (power - count); n++) {
          s += '0';
        }
        s += std::to_string(digits.peekNext());
        digits.moveNext();
      }
      if (i == 0) {
        s += std::to_string(digits.peekNext());
        digits.moveNext();
      }
    }
  }
  return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
  return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == 0) {
    return true;
  }
  return false;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == -1) {
    return true;
  }
  return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) <= 0) {
    return true;
  }
  return false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) == 1) {
    return true;
  }
  return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B) {
  if (A.compare(B) >= 0) {
    return true;
  }
  return false;
}

// operator+()
// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
  return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B) {
  BigInteger temp = A;
  A = temp.add(B);
  return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
  return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
  BigInteger temp = A;
  A = temp.sub(B);
  return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
  return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
  BigInteger temp = A;
  A = temp.mult(B);
  return A;
}
