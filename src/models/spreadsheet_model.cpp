//Hi


#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../../libs/json.hpp"
#include "./cell.h"
#include "dependency_graph.h"

using jsonf = nlohmann::json;

// Create new ss_model object
spreadsheet_model(std::string filepath_input, bool new_ss)
{
  if (new_ss)
    {

    }
  else
    {

    }
}

open_Json_ss__file()
{

}

write_Json_ss_file()
{

  int cell_index;
  std::ofstream write_file;
  json current_json;


  write_file.open"../../data/" + this-name + ".json"), std::ios::out);
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

