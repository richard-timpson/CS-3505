#ifndef SPREADSHEET_CONTROLLER_H
#define SPREADSHEET_CONTROLLER_H

#include <vector>
#include <string>
#include "../../libs/json.hpp"


class SpreadsheetController
{
  public:
    // get a json string that is an array of strings with the spreadsheet names. 
    static std::string get_list_of_spreadsheets();
    static bool validate_user(std::string json_message, std::string &error_message);    
};


#endif
