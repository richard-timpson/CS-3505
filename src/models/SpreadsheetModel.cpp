#include "SpreadsheetModel.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./Cell.h"
#include "./DependencyGraph.h"

using json = nlohmann::json;

// Create new ss_model object
SpreadsheetModel::SpreadsheetModel(std::string filepath_input, bool new_ss)
{
  if (new_ss)
    {

    }
  else
    {

    }
}

void SpreadsheetModel::open_json_ss_file()
{
    return;
}

void SpreadsheetModel::write_json_ss_file()
{

  int cell_index;
  std::ofstream write_file;
  json current_json;


  write_file.open("../../data/" + this-name + ".json"), std::ios::out);
  std::unordered_map<std::string, int>::iterator it = this->cell_dictionary.begin();

  while(it != this->cell_dictionary.end())
  {
    current_json["name"] = it->first;
    current_json["contents"] = it->second;

    write_file << current_json;
    it++;

  }

  write_file.close();


}



std::string SpreadsheetModel::get_name()
{
    return name;
}

void SpreadsheetModel::set_name(std::string name)
{
    this->name = name;
}

