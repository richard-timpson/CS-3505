#ifndef SPREADSHEET_CONTROLLER_H
#define SPREADSHEET_CONTROLLER_H

#include <vector>
#include <string>
#include "../../libs/json.hpp"
#include "../models/SpreadsheetModel.h"

using json = nlohmann::json;

class SpreadsheetController
{
  public:
    // get a json string that is an array of strings with the spreadsheet names. 
    static std::string get_list_of_spreadsheets();
    static bool validate_user(json message, std::string &error_message);    
    static bool validate_login_message(json & message);
    static bool check_if_spreadsheet_in_storage(json & message, std::string &spreadsheet);
    static std::string create_type_1_error();
};


#endif
