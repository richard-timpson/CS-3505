#ifndef CELLEDIT
#define CELLEDIT

#include <string>
#include <vector>


struct CellEdit
{
    std::string name;
    std::string contents;
    std::vector<std::string> direct_dependents;
    std::string type;
};

#endif