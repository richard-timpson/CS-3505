// Hi


#include "dependency_graph.h"
#include <string>



Backend::dependency_graph::dependency_graph()
{

  this->num_pairs=0;

}

Backend::dependency_graph::~dependency_graph()
{
  this->dependees.clear();
  
  this->dependents.clear();

  this->num_pairs=0;

}

int Backend::dependency_graph::get_size()
{
  // Rewrite in Jabrail's way
  return this->num_pairs;
}

int Backend::dependency_graph::get_size_of_dependees(std::string input)
{


  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = dependees.find(input);
  

  if (found == dependees.end())
    {
      return 0;
    }
  else
    {
      return (found->second).size();
    }
}

bool Backend::dependency_graph::has_dependents(std::string input)
{
  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = dependents.find(input);
  

  if (found == dependents.end())
    {
      return false;
    }
  else
    {
      return (found->second).size() > 0;
    }
}

bool Backend::dependency_graph::has_dependees(std::string input)
{

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = dependees.find(input);
  

  if (found == dependees.end())
    {
      return false;
    }
  else
    {
      return (found->second).size() > 0;
    }
}






std::unordered_set<std::string>::const_iterator Backend::dependency_graph::get_dependents(std::string input)
{

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = dependents.find(input);
  

  if (found == dependents.end())
    {
      std::unordered_set<std::string>::const_iterator empty;
      return empty;
    }
  else
    {
      return found->second.begin();
    }

}

std::unordered_set<std::string>::const_iterator Backend::dependency_graph::get_dependees(std::string input)
{

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = dependees.find(input);
  

  if (found == dependees.end())
    {
      std::unordered_set<std::string>::const_iterator empty;
      return empty;
    }
  else
    {
      return found->second.begin();
    }

}



void Backend::dependency_graph::add_dependency(std::string first_par, std::string second_par)
{
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependees = dependees.find(second_par);
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependents = dependents.find(first_par);

  
  // Dealing with first parameter
  if (found_dependees != dependees.end())
    {
      (found_dependees->second).insert(first_par);
    }
  else
    {
      std::unordered_set<std::string> new_set;
      std::pair<std::string, std::unordered_set<std::string>> new_pair (second_par, new_set);
      dependees.insert(new_pair);
      found_dependees->second.insert(first_par);
    }



  // Dealing with second parameter
  if (found_dependents != dependents.end())
    {
      found_dependents->second.insert(second_par);
    }
  else
    {
      std::unordered_set<std::string> new_set;
      std::pair<std::string, std::unordered_set<std::string>> new_pair (first_par, new_set);
      dependents.insert(new_pair);
      found_dependents->second.insert(second_par);
    }

  

}

void Backend::dependency_graph::remove_dependency(std::string first_par, std::string second_par)
{
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependees = dependees.find(second_par);
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependents = dependents.find(first_par);

  std::unordered_set<std::string>::iterator found_s_in_t = (found_dependees->second).find(first_par);
  std::unordered_set<std::string>::iterator found_t_in_s = (found_dependents->second).find(second_par);

  if (found_dependents != dependents.end() && found_dependees != dependees.end())
    {
      if (found_s_in_t != found_dependees->second.end() && found_t_in_s != found_dependents->second.end())
	{
	  found_dependents->second.erase(second_par);
	  found_dependees->second.erase(first_par);
	}
    }
  

}



