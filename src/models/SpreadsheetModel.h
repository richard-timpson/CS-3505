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
#include "../../libs/json.hpp"

class SpreadsheetModel
{
  public:
    std::string get_name();
    void set_name(std::string name);
  private:
    std::string name;
};

#endif
