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
<<<<<<< HEAD
    static bool validate_user(json message, std::string &error_message);    
    static bool validate_login_message(json & message);
    static std::string create_type_1_error();
=======
    static bool validate_user(std::string json_message, std::string &error_message);    
>>>>>>> SpreadsheetModel
};


#endif
