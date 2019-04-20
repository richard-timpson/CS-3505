/*
 *  The spreadsheet model class is for dealing with seeing the users on
 * the spreadsheet part of the connection process. This class will verify,
 * and validate user logins when they attempt to open a spreadsheet and 
 *  are on the spreadsheet.
 *
 */

#ifndef SPREADSHEETMODEL_H
#define SPREADSHEETMODEL_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include "Cell.h"
#include "CellEdit.h"

class SpreadsheetModel
{
  public:
    SpreadsheetModel(std::string filepath, bool new_ss);

    void set_name(std::string name);
    std::string get_name();
    std::stack<CellEdit> get_global_history();

    void set_cell_contents(std::string name, std::string contents, std::vector<std::string> dependents, std::string type);
    std::string get_cell_contents(std::string name);
    std::string get_cell_type(std::string name);
    std::vector<std::string> get_cell_direct_dependents(std::string name);
    std::stack<CellEdit> get_cell_personal_history(std::string name);
    void push_cell_personal_history(std::string name, CellEdit input);
    void pop_cell_personal_history(std::string name);
    CellEdit top_cell_personal_history(std::string name);
    std::unordered_map<std::string, Cell> get_cell_dictionary();

    void open_json_ss_file();
    void write_json_ss_file();

    void do_edit(std::string cell_name, std::string contents, std::vector<std::string> &dependents, std::string type);
    void do_undo();
    void do_revert(std::string name);

    bool circular_dependency_check(std::string name);
    bool circular_dependency_check(std::set<std::string> names);
    
    bool check_cell_personal_history_empty(std::string name);

  private:
    bool visit(std::string &start, std::string &name, std::set<std::string> & visited, std::vector<std::string> & changed);
    bool edit_made;
    std::unordered_map<std::string, Cell> cell_dictionary;
    std::stack<CellEdit> global_history;
    std::string name;
};

#endif
