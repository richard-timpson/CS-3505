#include "SpreadsheetController.h"
#include <iostream>
#include <fstream>

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

bool SpreadsheetController::validate_user(std::string json_message, std::string &error_message)
{
    json message = json::parse(json_message);
    if (message.value("username", "-1") == "-1" || message.value("password", "-1") == "-1" || message.value("type", "-1") == "-1")
    {
        error_message = "String not in valid form";
        return false;
    }
    if ( message.value("type", " ") != "open")
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
        if (message.value("username", " ") != username && message.value("password", " " ) != password)
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