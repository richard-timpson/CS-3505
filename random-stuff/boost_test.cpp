#include <boost/version.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std:: cout << "Boost version: "
	     << BOOST_VERSION / 10000 
	     << "."
	     << BOOST_VERSION / 100 % 1000
	     << "."
	     << BOOST_VERSION % 100
	     << std::endl;
  std::cout << "boost version: " << BOOST_LIB_VERSION << std::endl;
  return 0;
}
