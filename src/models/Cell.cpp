
#include "Cell.h"
#include <string>

Cell::Cell(std::string name)
{
    this->name = name;
    this->current_contents = "";
}

Cell::Cell(std::string name, std::string contents)
{
    this->name = name;
    this->current_contents = contents;
}

Cell::Cell(std::string name, std::string contents, std::vector<std::string> direct_dependents)
{
    this->name = name;
    this->current_contents = contents;
    this->direct_dependents = direct_dependents;
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

void Cell::set_cell_contents(std::string input)
{
    this->current_contents = input;
}
