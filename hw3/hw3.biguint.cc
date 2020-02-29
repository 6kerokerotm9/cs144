/*
  Joshua Sjah
  CS 144
  This program defines many methods from the BigUInt class 
*/
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
BigUInt::BigUInt(const BigUInt& b) {
	length = b.length;
	data = new unsigned char[length]; //create a new array using the length of b
	for(int i=0; i<length; i++) {
		data[i] = b.data[i]; //copy the indexes one by one
	}
}

BigUInt& BigUInt::operator=(const BigUInt& b) {
	length = b.length;
	delete []data;
	data = new unsigned char[length];
	for(int i=0; i<length; i++) {
		data[i] = b.data[i];
	}
	return *this;
}

BigUInt& BigUInt::operator+=(unsigned int i) {
	BigUInt temp(i); //create an object of BigUInt using the value of i
	*this += temp; //use the += operator that uses another BigUInt object as the other parameter
	return *this;
}

void BigUInt::SetDigit(int i, int d) {
	if(i > length || i < 0) { //check i to see if it is within the range of the array
		return;
	}
	else if(d < 0 || d > 9) { //make sure d is a value from 0-9
		return;
	}
	data[i] = d;
}

string BigUInt::ToString() {
	string temp = ""; //temporary string to append the numbers to 
	for(int i=length-1; i>=0; i--) {
		temp += to_string(static_cast<int>(data[i])); //uses to string function to convert the int to append to the string
	}
	return temp;
}

bool operator>(const BigUInt& lhs, const BigUInt& rhs) {
    if(lhs.length != rhs.length) {
        return lhs.length > rhs.length; //if different lengths the one that is longer is the greater number
    } 
    for(int i=lhs.length-1; i>=0; i--) {
        if(static_cast<int>(lhs.data[i]) != static_cast<int>(rhs.data[i])) {
			return static_cast<int>(lhs.data[i]) > static_cast<int>(rhs.data[i]); //compares the digits starting from the largest place and goes down 
		}
    }
    return false; //default case if both numbers are equal
}

BigUInt operator+(const BigUInt& b, unsigned int i) {
	BigUInt temp = b; //create temp class to be returned
	temp += i; //use the += operator for the BigUInt class to add the value i to the temp 
	return temp; //return the new value 
}
