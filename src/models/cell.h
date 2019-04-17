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
<<<<<<< HEAD
    std::string get_cell_contents();

  private:
    std::string current_value;
=======
    std::string get_cell_value();
  private:
    std::string current_value;
  };
>>>>>>> SpreadsheetModel
}

#endif
