
#include "Cell.h"
#include <string>


Cell::Cell(std::string input)
{
  this->current_value = input;
}

Cell::~Cell()
{
  this->current_value = "";
}

std::string Cell::get_cell_value()
{
  return this->current_value;
}

void Cell::set_cell_value(std::string input)
{
  this->current_value = input;
}

