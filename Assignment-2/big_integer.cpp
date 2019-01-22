


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
Destructor that does nothing
*/
big_integer::~big_integer()
{
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
// const big_integer big_integer::operator+(const big_integer& rhs)
// {

// }

/*
Overloading minus operator
*/
// const big_integer big_integer::operator-(const big_integer& rhs)
// {

// }

/*
Overloading multiplication operator
*/
// const big_integer big_integer::operator*(const big_integer& rhs)
// {

// }

/*
Overloading division operator
*/
// const big_integer big_integer::operator/(const big_integer& rhs)
// {

// }

/*
Overloading modulo operator
*/
// const big_integer big_integer::operator%(const big_integer& rhs)
// {

// }