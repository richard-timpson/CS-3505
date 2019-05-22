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


    static std::string get_list_of_users(std::vector<UserModel> users);
    static std::string get_list_of_spreadsheets(std::set<std::shared_ptr<SpreadsheetModel>> spreadsheets);
    static std::string full_send(std::unordered_map<std::string, std::shared_ptr<Cell>> & cell_dictionary);
    static bool validate_admin(json message, std::string &error_message); 
    /**
     * Compares the json message for the spreadsheet selection
     * to the current list of users. If the user part of the message
     * isn't in the list of users, we need to create a user and add it. 
     * If it is, check the password, and add the user to the spreadsheet
     */ 
    static bool validate_user(json message, std::shared_ptr<SpreadsheetModel> sm);    
    static bool validate_login_message(json & message);
    static bool check_if_spreadsheet_in_storage(json & message, std::string &spreadsheet);
    static bool handle_edit_message(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static std::string create_type_1_error();
    static std::string create_type_2_error(std::string name);
    static std::vector<std::string> split(std::string s, std::string delimiter);
    
  private:
    static bool handle_edit(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static bool handle_undo(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static bool handle_revert(json & message, std::shared_ptr<SpreadsheetModel> sm);
    static std::string get_type(json & message);
};


#endif
