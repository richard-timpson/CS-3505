#include "../controllers/SpreadsheetController.h"
#include <string>
#include <iostream>

int main()
{
    std::string sheets = SpreadsheetController::get_list_of_spreadsheets();
    std::cout << sheets << std::endl;
}