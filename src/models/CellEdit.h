/* Struct that represents a single cell edit, 
    used for the undo and revert history of cells. */
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