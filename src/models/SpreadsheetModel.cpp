#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <boost/lexical_cast.hpp>

#include "../../libs/json.hpp"
#include "./Cell.h"
#include "./CircularException.h"
#include "SpreadsheetModel.h"
#include "CellEdit.h"

using json = nlohmann::json;

bool check_if_int(std::string &contents);
bool check_if_double(std::string &contents);

SpreadsheetModel::SpreadsheetModel(std::string input_name, bool new_ss)
{
    if (new_ss)
    {
        this->name = input_name;
    }
    else
    {
        // this->open_json_ss_file();
    }
}

void SpreadsheetModel::set_cell_contents(std::string name, std::string contents, std::vector<std::string> &dependents, std::string type)
{
    std::cout << "setting the cell contents" << std::endl;
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);

    // Cell doesn't exist
    if (it == cell_dictionary.end())
    {
        Cell new_cell(name, contents, dependents, type);

        cell_dictionary.insert({name, new_cell});
    }
    // Cell exists
    else
    {
        Cell current_cell = it->second;
        std::cout << "editing existing cell " << std::endl;
        std::cout << "here" << std::endl;
        it->second.direct_dependents = dependents;
        it++;
        current_cell.set_direct_dependents(dependents);

        // get cells to recalculate with throw circular exception if there is one
        bool circular_dependency = circular_dependency_check(name);
        if (!circular_dependency)
        {
            std::cout << "actually setting the cell contents" << std::endl;
            current_cell.set_contents(contents);
            current_cell.set_type(type);
            std::cout << "successfully set cell contents" << std::endl;
        }
        else
        {
            throw CircularException(name);
        }
    }
}

std::string SpreadsheetModel::get_cell_contents(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    
    if (it != cell_dictionary.end())
    {
        return it->second.get_contents();
    }
}

std::vector<std::string> SpreadsheetModel::get_cell_direct_dependents(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_direct_dependents();
    }
}

std::string SpreadsheetModel::get_cell_type(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.get_type();
    }
}

std::stack<CellEdit> SpreadsheetModel::get_cell_personal_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.personal_history;
    }
}

void SpreadsheetModel::push_cell_personal_history(std::string name, CellEdit edit)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        it->second.personal_history.push(edit);
    }
}

void SpreadsheetModel::pop_cell_personal_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.personal_history.pop();
    }
}

CellEdit SpreadsheetModel::top_cell_personal_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.personal_history.top();
    }
}

bool SpreadsheetModel::check_cell_personal_history_empty(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.personal_history.empty();
    }
    else
    {
        return true;
    }
    
}

std::stack<CellEdit> SpreadsheetModel::get_cell_undo_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.undo_history;
    }
}

void SpreadsheetModel::push_cell_undo_history(std::string name, CellEdit edit)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        it->second.undo_history.push(edit);
    }
}

void SpreadsheetModel::pop_cell_undo_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.undo_history.pop();
    }
}

CellEdit SpreadsheetModel::top_cell_undo_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.undo_history.top();
    }
}

bool SpreadsheetModel::check_cell_undo_history_empty(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.undo_history.empty();
    }
    else
    {
        return true;
    }
    
}

std::unordered_map<std::string, Cell> SpreadsheetModel::get_cell_dictionary()
{
    return this->cell_dictionary;
}

std::stack<std::string> SpreadsheetModel::get_global_history()
{
    return this->global_history;
}

void SpreadsheetModel::open_json_ss_file()
{
    // go through file and set all jsons to cell objects
    // add to dictioanry and dependencygraph using SetcontentsofCell
    // function call

    std::ifstream input_file("../../data/" + this->name + ".json");
    json ss;
    input_file >> ss;

    json j_global_history = ss["global_history"];

    std::stack<CellEdit> global_history;

    // for (auto& el : j_global_history.items())
    // {
        
    //     std::cout << el.value() << "                      " << el.value() << std::endl;
    //     CellEdit current_edit;
    //     current_edit.name = el.value;
    //     std::cout << current_edit.name << std::endl;
    // }

    //this->global_history = global_history;
/*
    json j_cells = ss["cells"];
    std::unordered_map<std::string, Cell> cell_dictionary;

    for (json::iterator jcell_it = j_global_history.begin(); jcell_it != j_global_history.end(); ++jcell_it)
    {
        cell_dictionary.insert(jcell_it.key, jcell_it.value);
    }

    this->cell_dictionary = cell_dictionary;

    */




    input_file.close();
}

void SpreadsheetModel::write_json_ss_file()
{

    json ss;
    json cells;
    json fields;
    if (cell_dictionary.begin() == cell_dictionary.end())
    {
        std::cout << "setting cells to empty object " << std::endl;
        cells = json({});
    }
    else
    {
        for (std::pair<const std::string, Cell> cell : cell_dictionary)
        {
            std::cout << "entered loop in write_json " << std::endl;
            std::string name = cell.second.get_name();
            std::string contents = cell.second.get_contents();
            std::string type = cell.second.get_type();
            std::vector<std::string> dependents = cell.second.get_direct_dependents();
            std::stack<CellEdit> cell_history = cell.second.personal_history;

            fields["contents"] = contents;
            fields["type"] = type;
            fields["dependents"] = dependents;

            json j_cell_history;
            // loop through all of the stack edits
            std::cout << "" << cell_history.empty() << std::endl;
            while (cell_history.empty() != true)
            {
                j_cell_history.push_back({{"name", cell_history.top().name},
                                          {"contents", cell_history.top().contents},
                                          {"dependents", cell_history.top().direct_dependents}});
                cell_history.pop();
            }

            fields["history"] = j_cell_history;

            cells[name] = fields;
        }
    }

    ss["spreadsheet"] = cells;

    std::stack<std::string> global_history = this->get_global_history();
    json j_global_history;
    // loop through all of the stack edits
    
    while (global_history.empty() != true)
    {
        j_global_history.push_back(global_history.top());
        global_history.pop();
    }

    ss["global_history"] = j_global_history;

    std::ofstream write_file;
    write_file.open("../../data/" + this->name + ".json", std::ios::out);
    write_file << ss;
    write_file.close();
}

std::string SpreadsheetModel::get_name()
{
    return name;
}

bool SpreadsheetModel::circular_dependency_check(std::string name)
{
    std::set<std::string> names{name};
    return circular_dependency_check(names);
}

bool SpreadsheetModel::circular_dependency_check(std::set<std::string> names)
{
    std::vector<std::string> changed;
    std::set<std::string> visited;
    for (std::string name : names)
    {
        if (visited.find(name) == visited.end())
        {
            return visit(name, name, visited, changed);
        }
    }
    return false;
}

bool SpreadsheetModel::visit(std::string &start, std::string &name, std::set<std::string> &visited, std::vector<std::string> &changed)
{
    visited.insert(name);
    std::vector<std::string> dependents = get_cell_direct_dependents(name);
    for (std::string n : dependents)
    {
        if (n == start)
        {
            return true;
        }
        else if (visited.find(n) == visited.end())
        {
            return visit(start, n, visited, changed);
        }
    }
    return false;
}

void SpreadsheetModel::do_edit(std::string cell_name, std::string contents, std::vector<std::string> &dependents, std::string type)
{
    try
    {
        this->set_cell_contents(cell_name, contents, dependents, type);
    }
    catch (const CircularException &e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    CellEdit edit;
    edit.name = cell_name;
    edit.contents = contents;
    edit.direct_dependents = dependents;
    edit.type = type;
    this->global_history.push(edit.name);
    this->push_cell_personal_history(cell_name, edit);
    this->push_cell_undo_history(cell_name, edit);
}

void SpreadsheetModel::do_undo()
{
    std::cout << "calling do undo" << std::endl;
    if (!this->global_history.empty())
    {
        // get the last edit from the global history
        std::string name = this->global_history.top();
        this->global_history.pop();

        // find the name from the edit, and pop off the cells undo_history
        this->pop_cell_undo_history(name);
        CellEdit edit;
        
        if (this->check_cell_undo_history_empty(name))
        {
            edit.name = name;
            edit.contents = "";
            std::vector<std::string> dep;
            edit.direct_dependents = dep;
            edit.type = "string";
        }
        else
        {
            edit = this->top_cell_undo_history(edit.name);
        }
        try
        {
            this->set_cell_contents(edit.name, edit.contents, edit.direct_dependents, edit.type);
            this->push_cell_personal_history(edit.name, edit);
        }
        catch(const CircularException& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void SpreadsheetModel::do_revert(std::string name)
{
    std::cout << "calling do revert" << std::endl;
    // pop the latest change on the cell's personal history
    CellEdit edit;
    if (!this->check_cell_personal_history_empty(name))
    {
        this->pop_cell_personal_history(name);

        if (this->check_cell_personal_history_empty(name))
        {
            edit.name = name;
            edit.contents = "";
            std::vector<std::string> dep;
            edit.direct_dependents = dep;
            edit.type = "string";
        }
        else
        {
            edit = this->top_cell_personal_history(name);
        }
        try
        {
            this->set_cell_contents(edit.name, edit.contents, edit.direct_dependents, edit.type);
            this->global_history.push(edit.name);
            this->push_cell_undo_history(edit.name, edit);
        }
        catch (const CircularException &e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
}

bool check_if_int(std::string &contents)
{
    int number;
    try
    {
        number = boost::lexical_cast<int>(contents);
        return true;
    }
    catch (boost::bad_lexical_cast &e)
    {
        return false;
    }
}

bool check_if_double(std::string &contents)
{
    double number;
    try
    {
        number = boost::lexical_cast<double>(contents);
        return true;
    }
    catch (boost::bad_lexical_cast &e)
    {
        return false;
    }
}