/*
CS 3505
Richard Timpson
1/10/19
Convert Time Program

The program will ask the user to input a number in seconds, and output those seconds
as hours, minutes, and seconds. 

*/


// including relevant libraries
#include <iostream>
using namespace std;

int main () 
{
  // storing the user input as a double in the case of a decimal
  double seconds_decimal;
  cout << "Enter a time in seconds: ";
  cin >> seconds_decimal;

  // rounding the number and storing as an integer
  int seconds_rounded =(int)(seconds_decimal + .5);

  // performing calculations for each aspect of the time
  int hours = seconds_rounded / 3600;
  int minutes = ((seconds_rounded % 3600) / 60);
  int seconds = ((seconds_rounded % 3600))% 60; 

  // outputting the seconds
  cout << seconds_rounded << " seconds --> ";
  
  // the following checks check if the hours, minutes, or seconds are above 10
  // if they are, print a 0 before the number so that we are using the proper format. 
  if (hours < 10 ) {
    cout << "0";
  }
  cout << hours << ":";
  if (minutes < 10) {
    cout << "0";
  }
  cout << minutes << ":";
  if (seconds < 10){
    cout << "0";
  }
  // finish the output. 
  cout << seconds << "\n"; 
}
