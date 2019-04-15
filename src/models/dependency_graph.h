

#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace Backend
{
  class dependency_graph
  {
  public:
    
    dependency_graph();
    ~dependency_graph();

    int get_size();
    int get_size_of_dependees(std::string input);
    bool has_dependents(std::string input);
    bool has_dependees(std::string input);
    std::unordered_set<std::string>::const_iterator get_dependents(std::string input);
    std::unordered_set<std::string>::const_iterator get_dependees(std::string input);
    void add_dependency(std::string first, std::string second);
    void remove_dependency(std::string first, std::string second);
    // Replace dependents and dependees methods go here.
    
    
    std::unordered_map<std::string, std::unordered_set<std::string>> dependees;

    std::unordered_map<std::string, std::unordered_set<std::string>> dependents;

    int num_pairs;
    
  private:
    
    
  };
}


#endif
