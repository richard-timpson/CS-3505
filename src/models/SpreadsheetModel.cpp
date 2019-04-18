#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./Cell.h"
#include "DependencyGraph.h"
#include "SpreadsheetModel.h"
#include <vector>
#include <set>
#include "./CircularException.h"

using json = nlohmann::json;

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
        current_json["contents"] = it->second.get_cell_contents();
        current_json["dependents"] = it->second.get_cell_direct_dependents();

        write_file << current_json;
        it++;
    }

    write_file.close();
}

void SpreadsheetModel::set_cell_contents(std::string name, std::string contents, std::vector<std::string> dependents)
{
    std::unordered_map<std::string, Cell>::const_iterator it = cell_dictionary.find(name);

    // Cell doesn't exist
    if (it == cell_dictionary.end())
    {
        Cell new_cell(name, contents, dependents);
        cell_dictionary.insert({name, new_cell});
        // Adding dependency
        for (std::string dependent: dependents)
        {
            main_graph.add_dependency(name, dependent);
        }
    }
    // Cell exists
    else
    {
        // Get cell, remove current dependencies,add new ones, change contents
        Cell current_cell = it->second;

        for (std::string direct_depedent : current_cell.get_cell_direct_dependents())
        {
            main_graph.remove_dependency(name, direct_depedent);
        }

        for (std::string dependent : dependents)
        {
            main_graph.add_dependency(name, dependent);
        }

        current_cell.set_cell_contents(contents);
        current_cell.set_cell_direct_dependents(dependents);
    }
}

std::string SpreadsheetModel::get_cell_contents(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_cell_contents();
    }
}

std::string SpreadsheetModel::full_send()
{
    json ss;
    json cells;
    for (std::pair<std::string, Cell> cell : this->cell_dictionary)
    {
        cells[cell.second.get_cell_name()] = cell.second.get_cell_contents();
    }
    ss["type"] = "full send";
    ss["spreadsheet"] = cells;
}

std::string SpreadsheetModel::get_name()
{
    return name;
}

std::vector<std::string> SpreadsheetModel::get_cells_to_recalculate(std::string name)
{
    std::set<std::string> names{name};
    return get_cells_to_recalculate(names);
}

std::vector<std::string> SpreadsheetModel::get_cells_to_recalculate(std::set<std::string> names)
{
    std::vector<std::string> changed;
    std::set<std::string> visited;
    for (std::string name: names)
    {
        if (visited.find(name) == visited.end())
        {
            visit(name, name, visited, changed);
        }
    }
    return changed;
}



void SpreadsheetModel::visit(std::string &start, std::string &name, std::set<std::string> & visited, std::vector<std::string> & changed)
{
    visited.insert(name);
    for (std::string n : get_direct_dependents(name))
    {
        if (n == start)
        {
            throw CircularException();
        }
        else if (visited.find(n) == visited.end())
        {
            visit(start, n, visited, changed);
        }
    }
}
