#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <set>
#include <boost/lexical_cast.hpp>

#include "../../libs/json.hpp"
#include "./Cell.h"
#include "./CircularException.h"
#include "SpreadsheetModel.h"

using json = nlohmann::json;

bool check_if_int(std::string &contents);
bool check_if_double(std::string &contents);

SpreadsheetModel::SpreadsheetModel(std::string input_name, bool new_ss)
{
    if (new_ss)
    {
        this->name = input_name;
    }
    else
    {
        // this->open_json_ss_file();
    }
}

void SpreadsheetModel::set_cell_contents(std::string name, std::string contents, std::vector<std::string> dependents)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);

    // Cell doesn't exist
    if (it == cell_dictionary.end())
    {
        std::string type;
        bool is_int = check_if_int(contents);
        if (is_int)
        {
            type = "int";
        }
        else
        {
            bool is_double = check_if_double(contents);
            if (is_double)
            {
                type = "double";
            }
            else
            {
                type = "string";
            }
        }
        Cell new_cell(name, contents, dependents, type);
        cell_dictionary.insert({name, new_cell});
    }
    // Cell exists
    else
    {
        Cell *current_cell = &it->second;
        current_cell->set_direct_dependents(dependents);

        // get cells to recalculate with throw circular exception if there is one
        bool circular_dependency = circular_dependency_check(name);
        if (!circular_dependency)
        {
            current_cell->set_contents(contents);
            std::unordered_map<std::string, Cell>::iterator it1 = cell_dictionary.find(name);
            Cell *new_cell = &it1->second;
        }
        else
        {
            throw CircularException();
        }
    }
}

std::string SpreadsheetModel::get_cell_contents(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_contents();
    }
}

std::vector<std::string> SpreadsheetModel::get_cell_direct_dependents(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_direct_dependents();
    }
}

std::string SpreadsheetModel::get_cell_type(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_type();
    }
}

std::unordered_map<std::string, Cell> SpreadsheetModel::get_cell_dictionary()
{
    return this->cell_dictionary;
}

void SpreadsheetModel::open_json_ss_file()
{
    // go through file and set all jsons to cell objects
    // add to dictioanry and dependencygraph using SetcontentsofCell
    // function call

    std::ifstream input_file("../../data/" + this->name + ".json");
    json jsons = json::parse(input_file);

    // for (auto it = jsons.begin(); it != jsons.end(); it++)
    // {
    //     set_cell_contents(it->first, it->second, it->third);
    // }
    input_file.close();
}

void SpreadsheetModel::write_json_ss_file()
{
    int cell_index;
    std::ofstream write_file;
    json current_json;

    write_file.open("../../data/" + this->name + ".json", std::ios::out);
    std::unordered_map<std::string, Cell>::iterator it = this->cell_dictionary.begin();

    while (it != this->cell_dictionary.end())
    {
        current_json["name"] = it->first;
        current_json["contents"] = it->second.get_contents();
        current_json["dependents"] = it->second.get_direct_dependents();

        write_file << current_json;
        it++;
    }

    write_file.close();
}


std::string SpreadsheetModel::get_name()
{
    return name;
}

bool SpreadsheetModel::circular_dependency_check(std::string name)
{
    std::set<std::string> names{name};
    return circular_dependency_check(names);
}

bool SpreadsheetModel::circular_dependency_check(std::set<std::string> names)
{
    std::vector<std::string> changed;
    std::set<std::string> visited;
    for (std::string name : names)
    {
        if (visited.find(name) == visited.end())
        {
            return visit(name, name, visited, changed);
        }
    }
    return false;
}

bool SpreadsheetModel::visit(std::string &start, std::string &name, std::set<std::string> &visited, std::vector<std::string> &changed)
{
    visited.insert(name);
    for (std::string n : get_cell_direct_dependents(name))
    {
        if (n == start)
        {
            return true;
        }
        else if (visited.find(n) == visited.end())
        {
            return visit(start, n, visited, changed);
        }
    }
    return false;
}

void SpreadsheetModel::do_edit()
{

}

void SpreadsheetModel::do_undo()
{

}

void SpreadsheetModel::do_revert(std::string name)
{

}



bool check_if_int(std::string &contents)
{
    int number;
    try
    {
        number = boost::lexical_cast<int>(contents);
        return true;
    }
    catch (boost::bad_lexical_cast &e)
    {
        return false;
    }
}

bool check_if_double(std::string &contents)
{
    double number;
    try
    {
        number = boost::lexical_cast<double>(contents);
        return true;
    }
    catch (boost::bad_lexical_cast &e)
    {
        return false;
    }
}