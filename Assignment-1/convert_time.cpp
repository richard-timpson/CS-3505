#include <iostream>
#include <cmath>
using namespace std;

int main () 
{
  double seconds_decimal;
  cout << "Enter a time in seconds: ";
  cin >> seconds_decimal;
  int seconds_rounded = round(seconds_decimal);
  int hours = seconds_rounded / 3600;
  int minutes = ((seconds_rounded % 3600) / 60);
  int seconds = ((seconds_rounded % 3600))% 60; 
  cout << seconds_rounded << " seconds --> ";
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
  cout << seconds << "\n";
  // convert seconds to hours. 
  // take the remainder of hours and convert to minutes
  // take the remainder of minutes and convert to hours. 
}
