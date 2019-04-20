/**
 * Cell class for storing values of the spreadsheet.
 *
 *
 *
 */
#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <stack>
#include "CellEdit.h"

class Cell
{
  public:
    Cell(std::string name, std::string type);
    Cell(std::string name, std::string contents, std::string type);
    Cell(std::string name, std::string contents, std::vector<std::string> direct_dependents, std::string type);
    void set_contents(std::string input);
    void set_direct_dependents(std::vector<std::string>);
    void set_type(std::string type);
    std::string get_contents();
    std::string get_name();
    std::string get_type();
    std::stack<CellEdit> get_personal_history();
    std::vector<std::string> get_direct_dependents();
    std::stack<CellEdit> personal_history;
    std::stack<CellEdit> undo_history;
  private:
    std::string current_contents;
    std::string type;
    std::string name;
    std::vector<std::string> direct_dependents;

};

#endif
