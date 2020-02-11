#include "hw2.biguint.h"
#include <cmath>

BigUInt::BigUInt() {
    length = 0;
    data = new unsigned char[length];
    data[0] = 0;
}

BigUInt::BigUInt(unsigned int num) {
    int temp = num;
    length = 0;
    while (temp != 0) { //this loop determines the size of the array 
        length++;
        temp = temp / 10; //goes through each digit of the number
    }
    data = new unsigned char[length]; //set the array 
    for(int i=0; i<length; i++) {
        data[i] = num % 10;
        num = num / 10;
    }
}

BigUInt::~BigUInt() {
    delete []data;
}

void BigUInt::Print() {
    for(int i=length-1; i>=0; i--) {
        cout << static_cast<int>(data[i]);
    }
    cout << endl;
}

void BigUInt::TimesTenPow(unsigned int p) {
	unsigned char temp[length+p]; //temporary array to extend the length of the number
	for(int i=0; i<p; i++) { //fills the array with 0's according to the 10's place
		temp[i] = 0;
	}
	for(int j=0; j<length; j++) { //fills the rest of the number with the original number
		temp[j+p] = data[j];
	}
	length += p; //extends the length of the member variable
	data = new unsigned char[length+p]; //creates a new data field with new length
	for(int k=0; k<(length+p); k++) { //copies the data into the the new data 
		data[k] = temp[k];
	}
}

BigUInt& BigUInt::operator+=(const BigUInt& rhs) {
	int carry = 0; //holds the carry value for addition operations 
	int longest; //holds the longest length between the two numbers
    if(length < rhs.length) {
        longest = rhs.length;
    }
    else { //also handles the case where the number lengths are equal
        longest = length;
    }
    unsigned char temp[longest]; //sets a temporary array to hold the result
    unsigned char rhsTemp[longest]; //two arrays initialized to hold the numbers
    unsigned char lhsTemp[longest];
    
    for(int i=0; i<longest; i++) { //uses loop to set arrays to same lengths
        if(i >= length) {
            rhsTemp[i] = 0; //compensate for the the rest of the number by filling it with zeroes
        }
        else {
            rhsTemp[i] = rhs.data[i]; //set the data when index is in bounds
        }
    }
    for(int j=0; j<longest; j++) {
        if(j >= length) {
            lhsTemp[j] = 0;
        }
        else {
            lhsTemp[j] = data[j];
        }    
    }
    
    for(int k=0; k<longest; k++) {
		temp[k] = rhsTemp[k] + lhsTemp[k] + carry; //add the digits together
		if(temp[k] >= 10) { //if the result exceeds 10 then carry the 1
			temp[k] = temp[k] % 10;
            carry = 1;
		}
        else {
            carry = 0;
        }
	}
    
    if(carry == 1) { //for the end result if there still is a carried 1 then set a new digit
        longest++; //add one extra space in the end of the number for the carried digit
    }
    data = new unsigned char[longest];
    length = longest;
    for(int l=0; l<longest; l++) { //copies the data into the the new data 
		if(carry == 1 && l+1 == longest) { //if a carry is required append the 1 at the end of the array
            data[l] = 1;
        }
        else{
            data[l] = temp[l];
        }
        //cout << static_cast<int>(data[l]) << endl;
	}
	return *this;
}
