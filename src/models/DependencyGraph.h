/*
 * The dependency graph class is for dealing with seeing the cells on
 * the spreadsheet that relate to other cells. This class will keep,
 *  track of which cells are a dependent or depeende of other cells.
 *
 */

#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H

#include <string>
#include <unordered_set>
#include <unordered_map>

class DependencyGraph
{
  public:
    DependencyGraph();
    ~DependencyGraph();

    int get_size();
    int get_size_of_dependees(std::string input);
    bool has_dependents(std::string input);
    bool has_dependees(std::string input);
    std::unordered_set<std::string>::const_iterator get_dependents(std::string input);
    std::unordered_set<std::string>::const_iterator get_dependees(std::string input);
    void add_dependency(std::string first, std::string second);
    void remove_dependency(std::string first, std::string second);
    void replace_dependents(std::string first, std::unordered_set<std::string>::const_iterator(std::string input));
    void replace_dependees(std::string first, std::unordered_set<std::string>::const_iterator(std::string input));


    std::unordered_map<std::string, std::unordered_set<std::string>> dependees;

    std::unordered_map<std::string, std::unordered_set<std::string>> dependents;

    int num_pairs;

  private:
};

#endif
