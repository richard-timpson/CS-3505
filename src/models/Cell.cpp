#include <string>
#include "Cell.h"

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

//changed
std::string Cell::get_contents()
{
    return this->current_contents;
}

std::string Cell::get_name()
{
    return this->name;
}

std::string Cell::get_type()
{
    return this->type;
}

std::vector<std::string> Cell::get_direct_dependents()
{
    return this->direct_dependents;
}

void Cell::set_direct_dependents(std::vector<std::string> direct_dependents)
{
    this->direct_dependents = direct_dependents;
}

void Cell::set_contents(std::string contents)
{
    this->current_contents = contents;
}
