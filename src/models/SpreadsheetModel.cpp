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
        this->name = input_name;
        this->open_json_ss_file();
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
        // bool circular_dependency = circular_dependency_check(name);
        // if (!circular_dependency)
        {
            cell_dictionary.insert({name, new_cell});
        }
        // else
        // {
        //     throw CircularException(name);
        // }
        
    }
    // Cell exists
    else
    {
        Cell *current_cell = &it->second;
        std::cout << "editing existing cell " << std::endl;
        std::cout << "here" << std::endl;
        it->second.direct_dependents = dependents;
        it++;
        current_cell->set_direct_dependents(dependents);

        // get cells to recalculate with throw circular exception if there is one
        bool circular_dependency = circular_dependency_check(name);
        if (!circular_dependency)
        {
            std::cout << "actually setting the cell contents" << std::endl;
            current_cell->set_contents(contents);
            current_cell->set_type(type);
            std::cout << "successfully set cell contents" << std::endl;
            // std::unordered_map<std::string, Cell>::iterator it1 = cell_dictionary.find(name);
            // Cell *new_cell = &it1->second;
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

    // Getting global undo history
    json j_global_history = ss["global_history"];

    std::stack<std::string> new_global_history;
    std::unordered_map<std::string, Cell> new_cell_dictionary;

    for (json::reverse_iterator jcell_it = j_global_history.rbegin(); jcell_it != j_global_history.rend(); ++jcell_it)
    {
        std::cout << *jcell_it << std::endl;
        new_global_history.push(*jcell_it);
    }

    // Setting global history
    this->global_history = new_global_history;

    // Going through the saved cells
    json j_cells = ss["spreadsheet"];
    std::cout << j_cells.type_name() << std::endl;
    

    // Looping through the cells
    for (json::iterator el = j_cells.begin(); el != j_cells.end(); el++)
    // for (auto &el : j_cells.items())
    {
        std::cout << "looping through cells" << std::endl;
        json cell = el.value();
        std::cout << cell.type_name() << std::endl;

        // Creating parts of the cell to be filled
        std::stack<CellEdit> new_cell_revert_history;
        std::stack<CellEdit> new_cell_undo_history;
        std::vector<std::string> new_cell_direct_dependents;
        std::string new_cell_current_contents;
        std::string new_cell_type;
        std::string new_cell_name;

        std::cout << "getting the cell name" << std::endl;
        new_cell_name = el.key();
        std::cout << "getting the cell contents" << std::endl;
        new_cell_current_contents = cell["contents"];
        std::cout << "getting the cell type" << std::endl;
        new_cell_type = cell["type"];

        std::cout << "getting the cell dependnts " << std::endl;
        json j_dependents = cell["dependents"];

        // Going through a cell's Revert personal history's dependents
        for(std::string dep : j_dependents)
        {
            new_cell_direct_dependents.push_back(dep);
        }

        // Making core cell object
        Cell new_cell(new_cell_name, new_cell_current_contents, new_cell_direct_dependents, new_cell_type);


        // Going through a cell's Revert personal history
        json cell_history = cell["cell_history"];
        std::cout << cell_history.type_name() << std::endl;
        for (json::reverse_iterator jcell_it = cell_history.rbegin(); jcell_it != cell_history.rend(); ++jcell_it)
        {
            // Making a cell edit to save
            CellEdit edit;
            json cell_edit = *jcell_it;
            std::cout << cell_edit.type_name() << std::endl;
            edit.contents = cell_edit["contents"];
            edit.name = cell_edit["name"];
            std::vector<std::string> dependents;
            json j_dependents = cell_edit["dependents"];

            // Going through a cell's Revert personal history's dependents
            for(std::string dep : j_dependents)
            {
                dependents.push_back(dep);
            }
            edit.type = cell_edit["type"];
            edit.direct_dependents = dependents;
            std::cout << cell_edit["contents"] << std::endl;
            
            new_cell_revert_history.push(edit);

            // std::cout << cell_edit << std::endl;
        }

        // Saving revert history
        new_cell.personal_history = new_cell_revert_history;

        // Going through a cell's Undo personal history
        json undo_history = cell["undo_history"];
        std::cout << undo_history.type_name() << std::endl;
        for (json::reverse_iterator jcell_it = undo_history.rbegin(); jcell_it != undo_history.rend(); ++jcell_it)
        {
            // Making a cell edit to save
            CellEdit edit;
            json cell_edit = *jcell_it;
            std::cout << cell_edit.type_name() << std::endl;
            edit.contents = cell_edit["contents"];
            edit.name = cell_edit["name"];
            std::vector<std::string> dependents;
            json j_dependents = cell_edit["dependents"];

            // Going through a cell's Undo personal history's dependents
            for(std::string dep : j_dependents)
            {
                dependents.push_back(dep);
            }
            edit.type = cell_edit["type"];
            edit.direct_dependents = dependents;
            std::cout << cell_edit["contents"] << std::endl;
            
            new_cell_undo_history.push(edit);

            // std::cout << cell_edit << std::endl;
        }

        // Saving undo history
        new_cell.undo_history = new_cell_undo_history;

        // Making pair for cell
        std::pair<std::string, Cell> new_cell_pair (new_cell_name, new_cell);

        // Inserting pair for cell
        new_cell_dictionary.insert(new_cell_pair);

        std::cout << el.key() << std::endl;
    }

    // Setting the hsitory and dictionary of this ss model
    this->global_history = new_global_history;
    this->cell_dictionary = new_cell_dictionary;
    // std::unordered_map<std::string, Cell> cell_dictionary;

    // this->cell_dictionary = cell_dictionary;
    input_file.close();
}

void SpreadsheetModel::write_json_ss_file()
{
    std::cout << "writing to json file" << std::endl;
    std::remove(("../../data" + this->get_name() + ".json").c_str());
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
            std::stack<CellEdit> undo_history = cell.second.undo_history;

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
                                          {"dependents", cell_history.top().direct_dependents},
                                          {"type", cell_history.top().type}});
                cell_history.pop();
            }

            json j_undo_history;
            while (undo_history.empty() != true)
            {
                j_undo_history.push_back({{"name", undo_history.top().name},
                                          {"contents", undo_history.top().contents},
                                          {"dependents", undo_history.top().direct_dependents},
                                          {"type", undo_history.top().type}});
                undo_history.pop();
            }

            fields["undo_history"] = j_undo_history;
            fields["cell_history"] = j_cell_history;

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
    write_file.open("../../data/" + this->name + ".json");
    write_file << ss;    
    write_file.close();
    
}

void SpreadsheetModel::write_ss_file_if_needed()
{
    std::ifstream read_file;
    read_file.open("../../data/spreadsheets.txt");
    std::string line;
    while (std::getline(read_file,line ))
    {
        if (line == this->get_name())
        {
       	    std::cout << "not writing to spreadsheets.txt file" <<std::endl;
            return;
        }
    }
    read_file.close();
    std::cout << "writing spreadsheet " << this->get_name() << " to spreadsheets.txt file" << std::endl;
    std::ofstream write_file;
    write_file.open("../../data/spreadsheets.txt", std::ios_base::out | std::ios_base::app);
    write_file << this->get_name() << std::endl;
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
    // Change the cell's contents, then add the CellEdit struct
    //  to the global history as well as the cell's personal history.
}

void SpreadsheetModel::do_undo()
{
    std::cout << "calling do undo" << std::endl;
    if (!this->global_history.empty())
    {
        std::cout << "checked that global history is empty " << std::endl;
        // get the last edit from the global history
        std::string name = this->global_history.top();
        this->global_history.pop();

        // find the name from the edit, and pop off the cells undo_history
        this->pop_cell_undo_history(name);
        CellEdit edit;

        if (this->check_cell_undo_history_empty(name))
        {
            std::cout << "undo history is empty" << std::endl;
            edit.name = name;
            edit.contents = "";
            std::vector<std::string> dep;
            edit.direct_dependents = dep;
            edit.type = "string";
        }
        else
        {
            std::cout << "undo history isn't empty" << std::endl;
            edit = this->top_cell_undo_history(edit.name);
        }
        try
        {
            std::cout << "setting the cell contents in undo " << std::endl;
            this->set_cell_contents(edit.name, edit.contents, edit.direct_dependents, edit.type);
            this->push_cell_personal_history(edit.name, edit);
        }
        catch (const CircularException &e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
}

void SpreadsheetModel::do_revert(std::string name)
{
    std::cout << "calling do revert" << std::endl;
    // pop the latest change on the cell's personal history
    CellEdit edit;
    if (this->check_cell_personal_history_empty(name))
    {
        edit.name = name;
        edit.contents = "";
        std::vector<std::string> dep;
        edit.direct_dependents = dep;
        edit.type = "string";
        try
        {
            std::cout << "setting cell contents" << std::endl;
            this->set_cell_contents(edit.name, edit.contents, edit.direct_dependents, edit.type);
            this->global_history.push(name);
        }
        catch (const CircularException &e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
    else 
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
            std::cout << "setting cell contents in revert" << std::endl;
            this->set_cell_contents(edit.name, edit.contents, edit.direct_dependents, edit.type);
            this->global_history.push(edit.name);
            this->push_cell_undo_history(edit.name, edit);
        }
        catch (const CircularException &e)
        {
            std::cerr << "circular dependency in revert" << std::endl;;
            this->push_cell_personal_history(edit.name, edit);
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
