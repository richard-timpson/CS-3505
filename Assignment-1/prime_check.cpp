/*
CS 3505
Richard Timpson
1/10/19

Program should take in one input, and will output to the console whether or not that number is a prime nubmer

 */

// including relevant libraries
#include <iostream>
#include <cmath>
#include<cstdlib>

using namespace std;

int main (int argc, char** argv)
{
  // storing the argument as an integer
  int argument = atoi( argv[1]);

  // setting a flag that tells us whether or not the number is prime
  bool isPrime;
  
  // if the argument is 1 or less, it is considered a prime number, set to true
  if (argument <= 1){
    isPrime = true;
  }
  else {
    // if it isn't, loop through every possible number that could divide the argument
    // if one of those arguments has a clean division, with no remainder, the number
    // is not prime. 
  isPrime = true;
     for (int i = 2; i < argument; i++) {
       if (argument%i == 0) {
	 isPrime = false;
       }
     }
     // if we reach the end of the loop and the number is prime, the flag will be true
  }
  // perform simple check to determine the output. 
  if (isPrime) {
    cout << "prime" << endl;
  }
  else {
    cout << "not prime" << endl;
  }
  
}
