#include <iostream>
#include <exception>

struct CircularException : public std::exception
{
    const char * what () const throw ()
    {
        return "Circular Exception";
    }
};
