#ifndef CELLEDIT_H
#define CELLEDIT_H


struct CellEdit
{
    std::string name;
    std::string contents;
    std::vector<std::string> direct_dependents;
    std::string type;
};

#endif