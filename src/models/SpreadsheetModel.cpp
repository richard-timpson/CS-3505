#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./Cell.h"
#include "DependencyGraph.h"
#include "SpreadsheetModel.h"

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

    for (auto it = jsons.begin(); it != jsons.end(); it++)
    {
        // Set contents of cell and dictionary of cells
    }
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

        write_file << current_json;
        it++;
    }

    write_file.close();
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
