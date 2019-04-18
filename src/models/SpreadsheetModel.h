/*
 * The spreadsheet model class is for dealing with seeing the users on
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
#include "Cell.h"
#include "DependencyGraph.h"

class SpreadsheetModel
{
  public:
    SpreadsheetModel(std::string filepath, bool new_ss);
    void open_json_ss_file();
    void write_json_ss_file();
    std::string get_name();
    std::string full_send();
    void set_name(std::string name);
    void set_cell_contents(std::string name, std::string contents, std::vector<std::string> dependents);
    std::string get_cell_contents(std::string name);
    bool circular_dependency_check(std::string name);
    bool circular_dependency_check(std::set<std::string> names);
    std::vector<std::string> get_direct_dependents(std::string name);
    bool edit_made;
  private:
    bool visit(std::string &start, std::string &name, std::set<std::string> & visited, std::vector<std::string> & changed);
    std::unordered_map<std::string, Cell> cell_dictionary;
    DependencyGraph main_graph;
    std::string name;
    
    
};


#endif
