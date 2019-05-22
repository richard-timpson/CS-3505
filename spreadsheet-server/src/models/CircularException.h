#include <iostream>
#include <exception>
#include <string>
class CircularException : public std::exception
{
  public:
    CircularException(std::string cell_name)
    {
        this->cell_name = cell_name;
    }
    const char * what () const throw ()
    {
        return cell_name.c_str();
    }
  private:
    std::string cell_name;

};
