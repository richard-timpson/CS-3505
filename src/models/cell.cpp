// Hi



#include "cell.h"
#include <string>
#include <vector>


Backend::cell::cell(std::string input, std::vector<std::string> dependents)
{
  this->current_value = input;
}

Backend::cell::~cell()
{
  this->current_value = "";
}

std::string Backend::cell::get_cell_value()
{
  return this->current_value;
}

void Backend::cell::set_cell_value(std::string input)
{
  this->current_value = input;
}

std::vector<std::string> Backend::cell::get_cell_direct_dependents()
{
return this->direct_dependents
}

void Backend::cell::set_cell_direct_dependents(std::vector<std::string> input)
{
  this->direct_dependents = input;
}
