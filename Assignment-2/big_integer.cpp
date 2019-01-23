


#include <iostream>
#include "big_integer.h"

using namespace std;

/*
Default Constructor
*/
big_integer::big_integer()
{
    this->integer = "0";
}

/*
Standard constructor with string input
*/
big_integer::big_integer (string larg_int) 
{
  this->integer= larg_int;
}

/*
Copy constructor
*/
big_integer::big_integer(const big_integer &big_int_2)
{
  this->integer= big_int_2.integer;
}

/*
Overloading equals operator
*/
big_integer& big_integer::operator= (const big_integer &rhs) 
{
  this->integer = rhs.integer;
  return *this;
}

/*
Get value function
*/
string big_integer::get_value() const
{
    return this->integer;
}

/*
Overloading plus operator
*/
 const big_integer big_integer::operator+(const big_integer& rhs)
{
  string sum = add_two_strings(this->integer, rhs.integer);
  big_integer number(sum);
  return number;
}

/*
Overloading minus operator
*/
const big_integer big_integer::operator-(const big_integer& rhs)
{
  string difference = subtract_two_strings(this->integer, rhs.integer);
  big_integer number(difference);
  return number;
}

/*
Overloading multiplication operator
*/
const big_integer big_integer::operator*(const big_integer& rhs)
{
  string product = multiply_two_strings(this->integer, rhs.integer);
  big_integer number(product);
  return number;
}

/*
Overloading division operator
*/
const big_integer big_integer::operator/(const big_integer& rhs)
{
  big_integer number;
  return number;
}

/*
Overloading modulo operator
*/
const big_integer big_integer::operator%(const big_integer& rhs)
{
  big_integer number;
  return number;
}


/*Helper Methods*/

string big_integer::add_two_strings(string left, string right) 
{
  // variable for keeping the result
  string result = "";
  
  // keeping track of the positions in the string as we perform the operation
  int left_pos = left.size() - 1;
  int right_pos = right.size() - 1;

  // the value of the carry as we propogate through the addition
  int carry = 0;
  
  while (left_pos >= 0 || right_pos >=0 || carry > 0)
  {
    // calculate the sum for one column of digits
    int sum = 0;
    
    if (left_pos >= 0)
      sum += left[left_pos] - '0';
    if (right_pos >= 0)
      sum += right[right_pos] - '0';

    sum += carry;

    // now that we have the sum, we can determine what the carry and result should be

    carry = sum / 10;
    sum = sum % 10;

    // put the result in the final string and remove ascii bias
    result.insert (0, 1, (char)('0'+sum));

    // decrement positions in the string for the next iteratoin
    left_pos--;
    right_pos--;

  }

  // strip out any leading 0's from the integer, but leave at least 1 digit. 
  while (result.size() > 1 && result[0] == '0')
    result.erase(0,1);

  return result;
}

string big_integer::subtract_two_strings(string left, string right) 
{
  // variable for keeping the result
  string result = "";
 
  // if right is bigger than the left, return 0
  if (is_bigger(right, left)) 
  {
    result = "0";
    return result;
  }
 
  
  // keeping track of the positions in the string as we perform the operation
  int left_pos = left.size() - 1;
  int right_pos = right.size() - 1;
  // using a carry to determine if we need to decrement the left hand value based on previous calcuation
  int carry = 0;

  while ( left_pos >= 0 || right_pos >= 0)
  {
        
    // store the values of the strings as integers for easier maintenance
    int left_value = left[left_pos] - '0';
    int right_value = right[right_pos] - '0';
    
    
    // if the index of the right value is less than 0, use 0 for rights value. 
    if (right_pos < 0)
    {
      right_value = 0;
    }

    // calculate the difference of the two values. 
    // also subtract carry from left_value; carry will either be 1 or 0, depending on previous calcuation
    int difference = (left_value - carry) - right_value;

    // if the difference is less than 0, add 10 to the difference, and make the carry a 1. 
    if (difference < 0)
    {
      carry = 1;
      difference += 10;
    }
    // if the difference is not less than 0, make sure to set carry to 0. 
    else 
    {
      carry = 0;
    }



    // append the difference to the results string
    result.insert (0, 1, (char)('0'+difference));

    // decrement the indexes
    right_pos --;
    left_pos--;
    
  }

  // strip out any leading 0's from the integer, but leave at least 1 digit. 
  while (result.size() > 1 && result[0] == '0')
    result.erase(0,1);

  return result;
}

string big_integer:: multiply_two_strings (string number, string multiplier)
{
  // Perform long multiplication.  The result is the working sum and
  //   will be the product.  Do a small example on paper to see this
  //   algorithm work.

  string product = "0";

  // Loop through the digits of the multiplier in MSD to LSD order.

  for (int multiplier_pos = 0; multiplier_pos < multiplier.size(); multiplier_pos++)
  {
    // Multiply the product by 10.

    product.append("0");

    // Add in the correct number of copies of the number.  (Slow algorithm.)
    //   Notice that I count in ASCII.  ;)

    for (int i = '0'; i < multiplier[multiplier_pos]; i++)
      product = add_two_strings(product, number);
  }

  return product;
}


bool big_integer::is_bigger(string a, string b)
{
  // strip out any leading 0's from both numbers before performing checks. 
  while (a.size() > 0  && a[0] == '0')
    a.erase(0,1);
  while (b.size() > 0  && b[0] == '0')
    b.erase(0,1);

  int size_a = a.size();
  int size_b = b.size();
  // if a is bigger than b, return true, else return false
  if (size_a > size_b)
    return true;
  else if (size_a < size_b)
    return false;
  
  // if they are the same size, loop through both and compare their values. 
  // if it's ever the case that b's value is less than a's value, through the loop,
  // this means that b is less than a. 
  else if (size_a = size_b)
  {
    for (int i = 0; i < size_a; i++ ) 
    {
      if (a[i] > b[i])
	return true;
      else if (a[i] < b[i])
	return false;
    }
    return false;
  }
}


