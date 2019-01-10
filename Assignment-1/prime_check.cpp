#include <iostream>
#include <cmath>
#include<cstdlib>
using namespace std;
int main (int argc, char** argv)
{
  int argument = atoi( argv[1]);
  bool isPrime;
  if (argument <= 1){
    isPrime = true;
  }
  else {
  isPrime = true;
     for (int i = 2; i < argument; i++) {
       if (argument%i == 0) {
	 isPrime = false;
       }
     }
  }
  if (isPrime) {
    cout << "prime" << endl;
  }
  else {
    cout << "not prime" << endl;
  }
  
}
