// Hi



#include "cell.h"
#include <string>


Backend::cell::cell(std::string input)
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

