/*
 * The dependency graph class is for dealing with seeing the cells on
 * the spreadsheet that relate to other cells. This class will keep,
 *  track of which cells are a dependent or depeende of other cells.
 *
 */

#include "dependency_graph.h"
#include <string>



Backend::dependency_graph::dependency_graph()
{
  num_pairs=0;
}

Backend::dependency_graph::~dependency_graph()
{
  this->depended_on_by_graph.clear();
  this->depends_on_graph.clear();
  this->num_pairs=0;

}

int Backend::dependency_graph::get_size()
{
  return this->num_pairs;
}

int Backend::dependency_graph::get_size_of_dependees(std::string input)
{


  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = depends_on_graph.find(input);
  

  if (found == depends_on_graph.end())
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
  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = depended_on_by_graph.find(input);
  

  if (found == depended_on_by_graph.end())
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

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = depends_on_graph.find(input);
  

  if (found == depends_on_graph.end())
    {
      return false;
    }
  else
    {
      return (found->second).size() > 0;
    }
}

void Backend::dependency_graph::get_dependents(std::string input)
{

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = depended_on_by_graph.find(input);
  

  if (found == depended_on_by_graph.end())
    {
      //Return empty iterator
    }
  else
    {
      //return (found->second.begin());
      //return //Empty iterator
    }

}

void Backend::dependency_graph::get_dependees(std::string input)
{

  std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator found = depends_on_graph.find(input);
  

  if (found == depends_on_graph.end())
    {
      //return //Empty iterator
    }
  else
    {
      //return found->second.begin();
    }

}

void Backend::dependency_graph::add_dependency(std::string first_par, std::string second_par)
{
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_depends = depends_on_graph.find(second_par);
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_depended = depended_on_by_graph.find(first_par);

  
  // Dealing with first parameter
  if (found_depends != depends_on_graph.end())
    {
      (found_depends->second).insert(first_par);
    }
  else
    {
      std::unordered_set<std::string> new_set;
      std::pair<std::string, std::unordered_set<std::string>> new_pair (second_par, new_set);
      depends_on_graph.insert(new_pair);
      found_depends->second.insert(first_par);
    }



  // Dealing with second parameter
  if (found_depended != depended_on_by_graph.end())
    {
      found_depended->second.insert(second_par);
    }
  else
    {
      std::unordered_set<std::string> new_set;
      std::pair<std::string, std::unordered_set<std::string>> new_pair (first_par, new_set);
      depended_on_by_graph.insert(new_pair);
      found_depended->second.insert(second_par);
    }

  

}

void Backend::dependency_graph::remove_dependency(std::string first_par, std::string second_par)
{
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_depends = depends_on_graph.find(second_par);
  std::unordered_map<std::string, std::unordered_set<std::string>>::iterator found_depended = depended_on_by_graph.find(first_par);

  std::unordered_set<std::string>::iterator found_s = (found_depends->second).find(first_par);
  std::unordered_set<std::string>::iterator found_t = (found_depended->second).find(second_par);

  if (found_depended != depended_on_by_graph.end() && found_depends != depends_on_graph.end())
    {
      if (found_s != found_depends->second.end() && found_t != found_depended->second.end())
	{
	  found_depended->second.erase(second_par);
	  found_depends->second.erase(first_par);
	}
    }
  

}



