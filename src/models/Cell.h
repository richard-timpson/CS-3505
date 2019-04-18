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
    Cell(std::string name);
    ~Cell();
    void set_cell_contents(std::string input);
    std::string get_cell_contents();
    std::string get_cell_name();
  private:
    std::string current_value;
};

#endif
