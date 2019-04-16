#include "SpreadsheetController.h"
#include <iostream>
#include <fstream>

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
    json spreadsheets;
    spreadsheets["type"] = "list";
    spreadsheets["spreadsheets"] = {};
    if (count != 0)
    {
        std::cout << "count is 0" << std::endl;
        for (std::vector<std::string>::iterator it = spreadsheet_names.begin(); it != spreadsheet_names.end(); it++)
        {
            spreadsheets["spreadsheets"].push_back(*it);
        }
        return spreadsheets.dump();
    }
    else 
    {
        return "[]";
    }
}