/*
CS 3505
Richard Timpson
1/10/19
Prime Number Checker

Program should take in one input, and will output to the console whether or not that number is a prime nubmer

*/

// including relevant libraries
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;


void isPrime(uint64_t argument);

int main(int argc, char **argv)
{
    // storing the argument as an integer
    uint64_t argument = atoi(argv[1]);
    isPrime(argument);

    // isPrime(17);
    // isPrime(62015621);
    
}


void isPrime(uint64_t argument) 
{

    // setting a flag that tells us whether or not the number is prime
    bool isPrime;


    if (argument == 0)
    {
        isPrime = false;
    }

    // if the argument is 1 or less, it isnt considered a prime number, set to true
    else if (argument <= 1)
    {
        isPrime = false;
    }
    // if argument is 2, it is a prime number
    else if (argument == 2)
    {
        isPrime = true;
    }
    else
    {
        // if it isn't, loop through every possible number that could divide the argument up to
        // square root of number, only checking odd numbers. If number is divisible by 2, we know it's not prime. 
        // if one of those arguments has a clean division, with no remainder, the number
        // is not prime.
        isPrime = true;
        if (argument % 2 == 0)
        {
            isPrime = false;
        }
        else 
        {
            for (int i = 3; i < sqrt(argument); i+= 2)
            {
                if (argument % i == 0)
                {
                    isPrime = false;
                    break;
                }
            }
        }
        // if we reach the end of the loop and the number is prime, the flag will be true
    }
    // perform simple check to determine the output.
    if (isPrime)
    {
        cout << "prime" << endl;
    }
    else
    {
        cout << "not prime" << endl;
    }
}