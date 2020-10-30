/*
Joshua Sjah
CS 144
This program creates a class that emulates a rational fraction
with functions that operate on the rational numbers
test test test
*/

#include <iostream>
using namespace std;

class Rational {
private:
	int numerator, denominator;

public:

	//constructors
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int num, int den) {
		numerator = num;
		denominator = den;
	}

	//getters
	int getNumerator() {
		return numerator;
	}

	int getDenominator() {
		return denominator;
	}

	//overloaded functions for const calls
	int getNumerator() const{
		return numerator;
	}

	int getDenominator() const{
		return denominator;
	}

	//setters
	void setNumerator(int num) {
		numerator = num;
	}

	void setDenominator(int den) {
		if (den == 0) { //checks the value to see if it is valid to use in a denominator
			return;
		}
		denominator = den;
	}

	void Print() {
		cout << numerator << "/" << denominator << endl;
	}

	void Reduce() {
		int temp = 9; //number used to check the divisibility of the numerator and the denominator
		while(temp != 1) { //will keep checking both numbers against temp until it cannot be further reduced
			if (numerator % temp == 0 && denominator % temp == 0) { //checks to see if the num and denom can both be reduced by a mcf
				numerator = numerator / temp; 
				denominator = denominator / temp;
			}
			else {
				temp--; //moves on to the next number if the numerator and denominator cannot be evenly divided by temp
			}
		}
	}
	
	void operator +=(const Rational& rhs) {
		int rhsNum = rhs.numerator; //temporary variable to hold the numerator of rhs
		if(denominator != rhs.denominator) {
			numerator *= rhs.denominator;
			rhsNum *= denominator;
			denominator *= rhs.denominator;
		}
		numerator += rhsNum;
	}
};

Rational operator *(const Rational& lhs, const Rational& rhs) {
	Rational merged;
	merged.setNumerator(lhs.getNumerator() * rhs.getNumerator());
	merged.setDenominator(lhs.getDenominator() * rhs.getDenominator());
	return merged;
}

Rational operator +(const Rational& lhs, const Rational& rhs) {
	Rational merged;
	int rhsNum = rhs.getNumerator(); //temporary variable to hold the numerator of rhs
	int tempDen = lhs.getDenominator();
	if(lhs.getDenominator() != rhs.getDenominator()) {
		merged.setNumerator(lhs.getNumerator() * rhs.getDenominator());
		rhsNum *= lhs.getDenominator();
		tempDen *= rhs.getDenominator();
	}
	rhsNum += merged.getNumerator();
	merged.setNumerator(rhsNum);
	merged.setDenominator(tempDen);
	return merged;
}

bool operator ==(const Rational& lhs, const Rational& rhs) {
	Rational num1 = lhs;
	Rational num2 = rhs;
	num1.Reduce();
	num2.Reduce();
	return (num1.getNumerator() == num2.getNumerator()) && (num1.getDenominator() == num2.getDenominator());
}

int main() {
  Rational r1;
  Rational r2(12,36);
  r1.Print();
  r2.Print();
  r1.Reduce();
  r2.Reduce();  
  r1.Print();  
  r2.Print();  
  Rational r3(1,2);  
  Rational r4(2,3);  
  r4 += r3;  
  r4.Print();
  Rational r5(3,8);
  Rational r6(2,5);  
  Rational r7;  
  r7 = r5 + r6;  
  r7.Print();  
  r7.Reduce();  
  r7.Print();  
  Rational r8;  
  r8 = r5 * r6;  
  r8.Print();  
  r8.Reduce();  
  r8.Print();  
  Rational r9(36, 12);  
  Rational r10(12, 4);  
  if (r9 == r10) {
      cout << "equal" << endl;
  }
  else {
      cout << "not equal" << endl;  
  }  
  return 0;
}
