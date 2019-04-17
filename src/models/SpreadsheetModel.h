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
#include "./cell.h"
#include "dependency_graph.h"

class SpreadsheetModel
{
  public:
    SpreadsheetModel(std::string filepath, bool new_ss);
    void open_Json_ss_file();
    void write_Json_ss_file();
    std::string get_name();
    void set_name(std::string name);
    bool edit_made;
  private:
    std::unordered_map<std::string, cell> cell_dictionary;
    dependency_graph main_graph;
    std::string name;
    
    
};


#endif
