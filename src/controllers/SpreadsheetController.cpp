#include "SpreadsheetController.h"
#include <iostream>
#include <fstream>
#include "../../libs/json.hpp"
#include <string>
#include <iterator>
#include <list>

using json = nlohmann::json;

std::vector<std::string> split(std::string s, std::string delimiter);

std::string SpreadsheetController::get_list_of_spreadsheets()
{
    std::ifstream file("../../data/spreadsheets.txt");
    std::string line;
    std::vector<std::string> spreadsheet_names;
    int count = 0;
    while (std::getline(file, line))
    {
        spreadsheet_names.push_back(line);
        count++;
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

std::string SpreadsheetController::full_send(std::unordered_map<std::string, Cell> & cell_dictionary)
{
    json ss;
    json cells;
    if (cell_dictionary.begin() == cell_dictionary.end())
    {
        std::cout << "setting cells to empty object " << std::endl;
        cells = json({});
    }
    else
    {
        for (std::pair<std::string, Cell> cell : cell_dictionary)
        {
            std::cout << "entered loop in full send " << std::endl;
            std::string name = cell.second.get_name();
            std::string contents = cell.second.get_contents();
            std::string type = cell.second.get_type();
            if (type == "int")
            {
                cells[name] = stoi(contents);
            }
            else if (type == "double")
            {
                cells[name] = stod(contents);
            }
            else
            {
                cells[name] = contents;
            }
        }
    }
    
    ss["type"] = "full send";
    ss["spreadsheet"] = cells;
    return ss.dump();
}

bool SpreadsheetController::validate_user(json message, std::string &error_message)
{
    if (!validate_login_message(message)) return false;
    if (message.value("type", " ") != "open")
    {
        error_message = "Didn't send correct message type";
        return false;
    }
    std::ifstream file("../../data/users.txt");
    std::string line;
    bool valid_user;
    while (std::getline(file, line))
    {
        std::vector<std::string> current_line = split(line, " ");
        std::vector<std::string>::iterator it = current_line.begin();
        std::string username = *it;
        it++;
        std::string password = *it;
        if (message.value("username", " ") != username && message.value("password", " ") != password)
        {
            valid_user = false;
        }
        else
        {
            valid_user = true;
            file.close();
            return true;
        }
    }
    file.close();

    std::ofstream write_file;
    write_file.open("../../data/users.txt", std::ios::app);
    write_file << message.value("username", " ") << " " << message.value("password", " ") << std::endl;
    write_file.close();
    return true;
}

bool SpreadsheetController::validate_login_message(json & message)
{
    if (message.value("username", "-1") == "-1" || message.value("password", "-1") == "-1" || message.value("type", "-1") == "-1" || message.value("name", "-1") == "-1")
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool SpreadsheetController::check_if_spreadsheet_in_storage(json & message, std::string & spreadsheet)
{
    std::ifstream file("../../data/spreadsheets.txt");
    std::string line;
    std::vector<std::string> spreadsheet_names;
    int count = 0;
    while (std::getline(file, line))
    {
        if (message.value("name", "-1") == line)
        {
            spreadsheet = line;
            return true;
        }
    }
    return false;
}

bool SpreadsheetController::handle_edit_message(json & message)
{
    std::string type = message.value("type", "-1");
    if (type == "-1") return false;
    if (type == "edit") return handle_edit();
    if (type == "undo") return handle_undo();
    if (type == "revert") return handle_revert();

}

bool SpreadsheetController::handle_edit()
{
    
}

std::string SpreadsheetController::create_type_1_error()
{
    json message = {
        {"type", "error"},
        {"code", 1},
        {"source", " "}};
    return message.dump();
}

std::string SpreadsheetController::create_type_1_error()
{
    json message = {
        {"type", "error"},
        {"code", 1},
        {"source", " "}};
    return message.dump();
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
