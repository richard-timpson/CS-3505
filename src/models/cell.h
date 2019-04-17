/**
 * Cell class for storing values of the spreadsheet.
 *
 *
 *
 */
#ifndef CELL_H
#define CELL_H

#include <string>

class Cell
{
  public:
    cell(std::string input);
    ~cell();
    void set_cell_value(std::string input);
    std::string get_cell_contents();

  private:
    std::string current_value;
}

#endif
