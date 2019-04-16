#include "SpreadsheetController.h"
#include <iostream>
#include <fstream>
#include "../../libs/json.hpp"
#include "../models/user_model.h"
#include "./network_controller.h"
#include <string>
#include <iterator>
#include <list>

using json = nlohmann::json;

std::string SpreadsheetController::get_list_of_spreadsheets()
{
    std::ifstream file("../../data/spreadsheets.txt");
    std::string line;
    std::vector<std::string> spreadsheet_names;
    int count = 0;
    while (std::getline(file, line))
    {
        spreadsheet_names.push_back(line);
        count ++;
    }
    if (count != 0)
    {
        std::cout << "count is 0" << std::endl;
        json spreadsheets;
        for (std::vector<std::string>::iterator it = spreadsheet_names.begin(); it != spreadsheet_names.end(); it++)
        {
            spreadsheets.push_back(*it);
        }
        return spreadsheets.dump();
    }
    else 
    {
        return "[]";
    }
}



/*
 * The spreadsheet model class is for dealing with seeing the users on
 * the spreadsheet part of the connection process. This class will verify,
 * and validate user logins when they attempt to open a spreadsheet and 
 *  are on the spreadsheet.
 *
 */

bool  SpreadsheetController::validate(std::string input_username, std::string input_password)
{

  // Go line by line to find if user matches, then check if the assword matches, then check if the spreadsheet exists.

  std::ifstream file("../../data/logins.txt");
  std::string line;
  while (std::getline(file, line))
  {
    
  }

}
