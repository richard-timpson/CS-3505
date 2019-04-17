#include "../controllers/SpreadsheetController.h"
#include <string>
#include <iostream>
#include "../../libs/json.hpp"

using json = nlohmann::json;

int main()
{
    std::cout << "Test 1: Getting list of spreadsheets" << std::endl;
    std::string sheets = SpreadsheetController::get_list_of_spreadsheets();
    std::cout << "\t" << sheets << std::endl;
    std::cout << "Test 1 finished " << std::endl;

    std::cout << "Test 2: Getting current user" << std::endl;
    json message;
    message["type"] = "open";
    message["username"] = "hello";
    message["password"] = "hi";
    std::string error_message;
    bool is_valid = SpreadsheetController::validate_user(message.dump(), error_message);
    std::cout << "Test 2 finished " << std::endl;


    std::cout << "Test 3: creating new user" << std::endl;
    json message2;
    message2["type"] = "open";
    message2["username"] = "hey";
    message2["password"] = "hey";
    std::string error_message2;
    bool is_valid2 = SpreadsheetController::validate_user(message2.dump(), error_message);
    std::cout << "Test 3 finished " << std::endl;


    std::cout << "Test 4: invalid string type on user validation" << std::endl;
    json message3;
    message3["random"] = "open";
    std::string error_message3;
    bool is_valid3 = SpreadsheetController::validate_user(message3.dump(), error_message);
    if (is_valid3)
    {
        std::cout << "Test failed " << std::endl;
    }
    else 
    {
        std::cout << "Test succedded " << std::endl;
    }
    std::cout << "Test 4 finished " << std::endl;
}