
#include "Cell.h"
#include <string>

Cell::Cell(std::string name, std::string type)
{
    this->name = name;
    this->current_contents = "";
    this->type = type;
}

Cell::Cell(std::string name, std::string contents, std::string type)
{
    this->name = name;
    this->current_contents = contents;
    this->type = type;
}

Cell::Cell(std::string name, std::string contents, std::vector<std::string> direct_dependents, std::string type)
{
    this->name = name;
    this->current_contents = contents;
    this->direct_dependents = direct_dependents;
    this->type = type;
}


std::string Cell::get_cell_contents()
{
    return this->current_contents;
}

std::string Cell::get_cell_name()
{
    return this->name;
}

std::vector<std::string> Cell::get_cell_direct_dependents()
{
    return this->direct_dependents;
}

void Cell::set_cell_direct_dependents(std::vector<std::string> direct_dependents)
{
    this->direct_dependents = direct_dependents;
}

void Cell::set_cell_contents(std::string contents)
{
    this->current_contents = contents;
}
