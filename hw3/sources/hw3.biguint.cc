#include <iostream>
#include "hw3.biguint.h"

using namespace std;

/*** PART 1: CODE FROM HOMEWORK 2. DO NOT MODIFY ***/

BigUInt::BigUInt() {
  data = new unsigned char[1];
  data[0] = 0;
  length = 1;
}

BigUInt::BigUInt(unsigned int n) {
  // First pass: Figure out how many digits there are.
  int num_digits = 1;
  int d = n;
  while (d >= 10) {
    d /= 10;
    num_digits++;
  }
  // Second pass: Create and fill the array of digits.
  data = new unsigned char[num_digits];
  int pos = 0;
  data[pos] = 0;
  while (n > 0) {
    data[pos] = n % 10;
    n /= 10;
    pos++;
  }
  length = num_digits;
}

BigUInt::~BigUInt() {
  delete [] data;
}

void BigUInt::Print() {
  for (int i = length - 1; i >= 0; i--) {
    cout << (int) data[i];
  }
  cout << endl;
}


ostream& operator<<(ostream&os, const BigUInt& b) {
  for (int i = b.length - 1; i >= 0; i--) {
    os << (int) b.data[i];
  }
  os << endl;
  return os;
}

void BigUInt::TimesTenPow(unsigned int p) {
  int new_length = length + p;
  unsigned char* old = data;
  data = new unsigned char[new_length];
  for (int i = 0; i < p; i++) {
    data[i] = 0;
  }
  for (int i = 0; i < length; i++) {
    data[i+p] = old[i];
  }
  length = new_length;
}

BigUInt& BigUInt::operator+=(const BigUInt& rhs) {
  // Part 1: If the other number is bigger, allocate more space.
  if (rhs.length > length) {
    unsigned char* old = data;
    data = new unsigned char[rhs.length];
    for (int i = 0; i < length; i++) {
      data[i] = old[i];
    }
    for (int i = length; i < rhs.length; i++) {
      data[i] = 0;
    }
    length = rhs.length;
    delete [] old;
  }

  // Part 2: Sum the two numbers.
  unsigned char carry = 0;
  for (int i = 0; i < rhs.length; i++) {
    data[i] += rhs.data[i] + carry;
    if (data[i] >= 10) {
      carry = 1;
      data[i] -= 10;
    } else {
      carry = 0;
    }
  }
  if (carry > 0) {
    for (int i = rhs.length; i < length; i++) {
      data[i] += carry;
      if (data[i] >= 10) {
        carry = 1;
        data[i] -= 10;
      } else {
        carry = 0;
      }
    }
  }


  // Part 3: If last carry is 1, then allocate one more digit.
  if (carry > 0) {
    unsigned char* old = data;
    data = new unsigned char[length+1];
    for (int i = 0; i < length; i++) {
      data[i] = old[i];
    }
    data[length] = 1;
    length++;
    delete [] old;
  }

  return *this;
}

/*** PART II: WRITE YOUR HOMEWORK 3 CODE BELOW THIS LINE ***/
