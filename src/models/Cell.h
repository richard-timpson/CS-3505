/**
 * Cell class for storing values of the spreadsheet.
 * Also holds an undo history and revert history that applies
 * to the single cell, which can be used to make the correct edits
 * when the undo and revert commands are called. This class is used
 * to represent the main state of the spreadsheet in the spreadsheet model. 
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
    // constructor. TODO: probably don't need all 3
    Cell(std::string name, std::string type);
    Cell(std::string name, std::string contents, std::string type);
    Cell(std::string name, std::string contents, std::vector<std::string> direct_dependents, std::string type);

    // contents
    void set_contents(std::string input);
    std::string get_contents();

    // direct_dependents, used for circular dependency check
    void set_direct_dependents(std::vector<std::string> &);
    std::vector<std::string> get_direct_dependents();
    std::vector<std::string> direct_dependents;

    // name
    std::string get_name();

    // type
    std::string get_type();
    void set_type(std::string type);
    
    /* We made revert_history and undo_history public for easier access
        so we didn't have to get pointers to them in memory. Might not be
        the best way to do this, so it's worth looking into for fix. */

    // keeps track of the revert history for the cell
    std::stack<CellEdit> revert_history;

    // keeps track of the undo_history for the cell
    std::stack<CellEdit> undo_history;
  private:
    // represents contents of cell
    std::string current_contents;

    // the type of the cell, because we store all contents as strings
    std::string type;

    // the cell name
    std::string name;

};

#endif
