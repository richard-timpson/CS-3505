/**
 * Cell class for storing values of the spreadsheet.
 *
 *
 *
 */
#ifndef CELL_H
#define CELL_H

#include <string>

namespace Backend
{
  class cell
  {
  public:
    cell(object input);
    ~cell();
    void set_cell_value(object input);
    object get_cell_value();
  private:
    objcet current_value;
  }
}

#endif
