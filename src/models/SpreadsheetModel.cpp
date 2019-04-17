//Hi

#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./Cell.h"
#include "DependencyGraph.h"
#include "SpreadsheetModel.h"

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
    // go through file and set all jsons to cell objects
    // add to dictioanry and dependencygraph using SetcontentsofCell
    // function call

    std::ifstream input_file("../../data/" + this->name + ".json");
    json jsons = json::parse(input_file);

    for (auto it = jsons.begin(); it != jsons.end(); it++)
    {
        set_cell_contents(it->first, it->second, it->third);
    }
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
        current_json["contents"] = it->second.get_cell_value();
	current_json["dependents"] = it->second.get_cell_direct_dependents();

    write_file << current_json;
    it++;

  }

  write_file.close();
}

void spreadsheet_model::set_cell_contents(std::string name, std::string contents, std::vector<std::string> dependents)
{
  std::unordered_map<std::string,Backend::cell>::const_iterator it = cell_dictionary.find(name);
  


  // Cell doesn't exist
  if (it == cell_dictionary.end())
    {
      Backend::cell new_cell(contents, dependents);
      cell_dictionary.insert({name, new_cell});
      // Adding dependency
      for(std::vector<string>::const_iterator it_dep = dependents.begin(); it_dep != dependents.end(); it_dep++)
	{
	  main_graph.add_dependency(name, it_dep->first);
	}
    }
  // Cell exists
  else
    {
      // Get cell, remove current dependencies,add new ones, change contents
      Backend::cell current_cell = it->second;
      
      // Remove current dependencies
      for(vector<string>::const_iterator it_dep = current_cell.get_direct_dependents().begin(); it_dep != current_cell.get_direct_dependents().end(); it_dep++)
	{
	  main_graph.remove_dependency(name, it_dep->first);
	}
      // Add new Dependencies
      for(vector<string>::const_iterator it_dep = dependents.begin(); it_dep != dependents.end(); it_dep++)
	{
	  main_graph.add_dependency(name, it_dep->first);
	}
      current_cell.set_cell_value(contents);
      current_cell.set_cell_direct_dependents(dependents);

    }
      
}



std::string SpreadsheetModel::get_name()
{
    return name;
}
