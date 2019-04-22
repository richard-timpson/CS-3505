#ifndef SPREADSHEET_CONTROLLER_H
#define SPREADSHEET_CONTROLLER_H

#include <vector>
#include <string>
#include "../../libs/json.hpp"
#include "../models/SpreadsheetModel.h"
#include "../models/Cell.h"

using json = nlohmann::json;

class SpreadsheetController
{
  public:

    std::mutex mu_lock_file_spreadsheet_txt;
    std::mutex mu_lock_file_user_txt;
    std::mutex mu_lock_spreadsheet_list;
    std::mutex mu_lock_user_list;
    std::mutex mu_lock_admin_list;

    // get a json string that is an array of strings with the spreadsheet names. 
    static std::string get_list_of_users();
    static std::string get_list_of_spreadsheets(std::set<std::shared_ptr<SpreadsheetModel>> spreadsheets);
    static std::string full_send(std::unordered_map<std::string, Cell> & cell_dictionary);
    static bool validate_admin(json message, std::string &error_message);  
    static bool validate_user(json message, std::string &error_message);    
    static bool validate_login_message(json & message);
    static bool check_if_spreadsheet_in_storage(json & message, std::string &spreadsheet);
    static bool handle_edit_message(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static std::string create_type_1_error();
    static std::string create_type_2_error(std::string name);
  private:
    static bool handle_edit(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static bool handle_undo(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static bool handle_revert(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static std::string get_type(json & message);
};


#endif
