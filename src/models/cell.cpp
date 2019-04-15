// Hi



#include "cell.h"
#include <string>


Backend::cell::cell(object input)
{
  this->current_value = input;
}

Backend::cell:~cell()
{
  this->current_value = NULL;
}

object Backend::cell::get_cell_value()
{
  return this->current_value;
}

void Backend::cell::set_cell_value(object input)
{
  this->current_value = input;
}

