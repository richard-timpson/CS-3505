//Hi


#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./cell.h"
#include "dependency_graph.h"
#include "spreadsheet_model.h"

using json = nlohmann::json;

// Create new ss_model object
spreadsheet_model::spreadsheet_model(std::string filepath_input, bool new_ss)
{
  if (new_ss)
    {

    }
  else
    {

    }
}

void spreadsheet_model::open_Json_ss_file()
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

void spreadsheet_model::write_Json_ss_file()
{

  int cell_index;
  std::ofstream write_file;
  json current_json;


  write_file.open("../../data/" + this->name + ".json", std::ios::out);
  std::unordered_map<std::string, Backend::cell>::iterator it = this->cell_dictionary.begin();

  while(it != this->cell_dictionary.end())
  {
    current_json["name"] = it->first;
    current_json["contents"] = it->second.get_cell_value();

    write_file << current_json;
    it++;

  }

  write_file.close();


}

