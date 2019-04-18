/*
 * The dependency graph class is for dealing with seeing the cells on
 * the spreadsheet that relate to other cells. This class will keep,
 *  track of which cells are a dependent or depeende of other cells.
 *
 */

#include "DependencyGraph.h"
#include <string>



DependencyGraph::DependencyGraph()
{

  this->num_pairs=0;

}

DependencyGraph::~DependencyGraph()
{
  this->dependees.clear();
  
  this->dependents.clear();

  this->num_pairs=0;

}

int DependencyGraph::get_size()
{
  // Rewrite in Jabrail's way
  return this->num_pairs;
}

int DependencyGraph::get_size_of_dependees(std::string input)
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

bool DependencyGraph::has_dependents(std::string input)
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

bool DependencyGraph::has_dependees(std::string input)
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


std::unordered_set<std::string>::const_iterator DependencyGraph::get_dependents(std::string input)
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

std::unordered_set<std::string>::const_iterator DependencyGraph::get_dependees(std::string input)
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



void DependencyGraph::add_dependency(std::string first_par, std::string second_par)
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

void DependencyGraph::remove_dependency(std::string first_par, std::string second_par)
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

void DependencyGraph::replace_dependents(std::string first_par, std::unordered_set<std::string>::const_iterator replace_dependents_set(std::string input))
{
    std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependents = dependents.find(first_par);

      //DependencyGraph::remove_dependency();

}

void DependencyGraph::replace_dependees(std::string first_par, std::unordered_set<std::string>::const_iterator(std::string input))
{
    std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_dependees = dependees.find(first_par);

        //Make a new hashset
        //Convert for each loop to go through new hashset 
        //DependencyGraph::remove_dependency();

      //

}



