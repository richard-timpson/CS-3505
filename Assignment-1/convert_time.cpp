#include <iostream>
#include <cmath>
using namespace std;

int main () 
{
  double seconds_decimal;
  cout << "Enter a time in seconds: ";
  cin >> seconds_decimal;
  int result = round(seconds_decimal);
  int hours = result / 3600;
  int minutes = ((result % 3600) * 60) / 60;
  
  cout << result  << " seconds\n";
  cout << hours << "hours\n";
  cout << minutes << "minutes \n";
  // convert seconds to hours. 
  // take the remainder of hours and convert to minutes
  // take the remainder of minutes and convert to hours. 
}
