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
        // if we are creating a new spreadsheet set the name
        this->name = input_name;
        // TODO: not sure what this function does
        // this->create_new_json_file();
    }
    else
    {
        // if we aren't creating a new spreadsheet, set the name
        this->name = input_name;
        // load from the json file
        this->read_json_ss_file();
    }
}

void SpreadsheetModel::set_cell_contents_and_type(std::string name, std::string contents, std::string type)
{
    std::cout << "setting the cell contents" << std::endl;
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);

    // Get a reference to the current cell
    Cell *current_cell = &it->second;
    current_cell->set_contents(contents);
    current_cell->set_type(type);

}

void SpreadsheetModel::set_cell_direct_dependents(std::string name, std::vector<std::string> & dependents)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    Cell *current_cell = &it->second;
    current_cell->direct_dependents = dependents;
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

std::stack<CellEdit> SpreadsheetModel::get_cell_revert_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.revert_history;
    }
}

void SpreadsheetModel::push_cell_revert_history(std::string name, CellEdit edit)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        it->second.revert_history.push(edit);
    }
}

void SpreadsheetModel::pop_cell_revert_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.revert_history.pop();
    }
}

CellEdit SpreadsheetModel::top_cell_revert_history(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.revert_history.top();
    }
}

bool SpreadsheetModel::check_cell_revert_history_empty(std::string name)
{
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        return it->second.revert_history.empty();
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
        std::cout << "topping from undo history in top_cell_undo_history" << std::endl;
        return it->second.undo_history.top();
        std::cout << "successful top in top_cell_undo_history" << std::endl;
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



void SpreadsheetModel::add_user_to_spreadsheet(std::string name)
{
    this->users.push_back(name);
}

void SpreadsheetModel::remove_user_from_spreadsheet(std::string name)
{
    std::vector<std::string>::iterator it = std::find(this->users.begin(), this->users.end(), name);
    if (it != this->users.end()) this->users.erase(it);
}
std::vector<std::string> SpreadsheetModel::get_users()
{
    return this->users;
}

void SpreadsheetModel::read_json_ss_file()
{
    // open the input file into an in stream
    /**
     * TODO: Reading from files may be causing issues.
     * Need to find way to debug
     */ 
    std::ifstream input_file("../../data/" + this->name + ".json");

    // Read the input stream into a json object
    json ss;
    input_file >> ss;

    // Getting global undo history
    json j_global_history = ss["global_history"];

    // creating temporary global_history and cell_dictionary for storing late
    std::stack<std::string> new_global_history;
    std::unordered_map<std::string, Cell> new_cell_dictionary;

    // loop through the global history and push the cell name to the global history stack
    for (json::reverse_iterator jcell_it = j_global_history.rbegin(); jcell_it != j_global_history.rend(); ++jcell_it)
    {
        std::cout << *jcell_it << std::endl;
        new_global_history.push(*jcell_it);
    }

    // Setting global history
    this->global_history = new_global_history;

    // Store the cells into another json object
    json j_cells = ss["spreadsheet"];

    // Loop through all of the cells
    for (json::iterator el = j_cells.begin(); el != j_cells.end(); el++)
    // for (auto &el : j_cells.items())
    {
        // Store each cell in a json object
        json cell = el.value();

        // Creating parts of the cell to be filled
        std::stack<CellEdit> new_cell_revert_history;
        std::stack<CellEdit> new_cell_undo_history;
        std::vector<std::string> new_cell_direct_dependents;
        std::string new_cell_current_contents;
        std::string new_cell_type;
        std::string new_cell_name;

        // set the new parts of the cell according to the object
        new_cell_name = el.key();
        new_cell_current_contents = cell["contents"];
        new_cell_type = cell["type"];

        // creating a new json array for cell dependents
        json j_dependents = cell["dependents"];

        // Going through a cells dependents and pushing to the new stack
        for(std::string dep : j_dependents)
        {
            new_cell_direct_dependents.push_back(dep);
        }

        // Making core cell object
        Cell new_cell(new_cell_name, new_cell_current_contents, new_cell_direct_dependents, new_cell_type);

        // Going through a cell's Revert personal history
        json cell_history = cell["cell_history"];
        for (json::reverse_iterator jcell_it = cell_history.rbegin(); jcell_it != cell_history.rend(); ++jcell_it)
        {
            // Making a temp cell edit for saving late
            CellEdit edit;

            // storing the current cell edit into a json object
            json cell_edit = *jcell_it;

            // setting the new edits members from json object
            edit.contents = cell_edit["contents"];
            edit.name = cell_edit["name"];
            edit.type = cell_edit["type"];

            // creating temp vector for dependents
            std::vector<std::string> dependents;

            // storing the edit's dependents into temp json object
            json j_dependents = cell_edit["dependents"];

            // Going through a cell's Revert personal history's dependents
            for(std::string dep : j_dependents)
            {
                // pushing to temp vector for cell edit. 
                dependents.push_back(dep);
            }
            // setting the dependents for the temp edit
            edit.direct_dependents = dependents;
            
            // pushing edit to revert history
            new_cell_revert_history.push(edit);
        }

        // Saving revert history
        new_cell.revert_history = new_cell_revert_history;

        /**
         * Going through the json objects cell history,
         * making a new edit, and applying that edit to spreadsheet model
         * cell history. This code is the same for revert above
         */ 

        json undo_history = cell["undo_history"];
        std::cout << undo_history.type_name() << std::endl;
        for (json::reverse_iterator jcell_it = undo_history.rbegin(); jcell_it != undo_history.rend(); ++jcell_it)
        {
            // Making a cell edit to save
            CellEdit edit;
            json cell_edit = *jcell_it;
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

    input_file.close();
}

void SpreadsheetModel::write_json_ss_file()
{
    // TODO: We need to check the way we write and read from files
    // As of now, this code just simply removes the .json file.
    // Needs to check if it's there first, before removal.

    std::remove(("../../data" + this->get_name() + ".json").c_str());
    std::cout << "Writing spreadsheet " << this->get_name() << " to json file" << std::endl;
    // create temp json objects
    json ss;
    json cells;
    json fields;

    // if the cell dictionary is empty, create empty json object
    if (cell_dictionary.begin() == cell_dictionary.end())
    {
        cells = json({});
    }
    // else create the json object to save
    else
    {
        // for reach cell
        for (std::pair<const std::string, Cell> cell : cell_dictionary)
        {
            // get the data from the cell
            std::string name = cell.second.get_name();
            std::string contents = cell.second.get_contents();
            std::string type = cell.second.get_type();
            std::vector<std::string> dependents = cell.second.get_direct_dependents();
            std::stack<CellEdit> cell_history = cell.second.revert_history;
            std::stack<CellEdit> undo_history = cell.second.undo_history;

            // setting some fields on the json object
            fields["contents"] = contents;
            fields["type"] = type;
            fields["dependents"] = dependents;


            // push to both the undo and revert histories as long as they aren't 
            // empty. 
            json j_cell_history;
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

            // set the histories in the json object
            fields["undo_history"] = j_undo_history;
            fields["cell_history"] = j_cell_history;

            cells[name] = fields;
        }
    }

    ss["spreadsheet"] = cells;

    // getting global history, and setting it to json object. 
    std::stack<std::string> global_history = this->get_global_history();
    json j_global_history;
    while (global_history.empty() != true)
    {
        j_global_history.push_back(global_history.top());
        global_history.pop();
    }

    ss["global_history"] = j_global_history;

    //TODO: Need to work on writing and readin from files
    // This particualr code bit seems to work, but worth looking into.
    // Need to learn how to debug
    std::ofstream write_file;
    write_file.open("../../data/" + this->name + ".json");
    write_file << ss;    
    write_file.close();
    
}

void SpreadsheetModel::write_ss_file_if_needed()
{
    //TODO: This function may not be needed. 
    // It's possible that we will save the spreadsheets.txt file
    // as the models are created, and not destoryed. 
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

void SpreadsheetModel::create_new_json_file()
{
    //TODO: This function may need to change. 
    // As of now, we create a new json object and append to spreadsheets.txt 
    // on object creation, but we may just do it on server startup and shutdown. 
    std::ofstream write_file;
    write_file.open("../../data/spreadsheets.txt", std::ios_base::out | std::ios_base::app);
    write_file << this->get_name() << std::endl;
    write_file.close();

    std::ofstream write_file_j;
    write_file_j.open(("../../data/" + this->name + ".json").c_str(), std::ios_base::out);
    write_file_j.close();

}

std::string SpreadsheetModel::get_name()
{
    return name;
}

bool SpreadsheetModel::circular_dependency_check(std::string name, std::vector<std::string>& dependents)
{
    std::set<std::string> names{name};
    std::vector<std::string> old_dependents;
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(name);
    if (it != cell_dictionary.end())
    {
        old_dependents = this->get_cell_direct_dependents(name);
    }
    this->set_cell_direct_dependents(name, dependents);
    bool circular_dependency = circular_dependency_check(names, dependents);
    if (circular_dependency)
    {
        this->set_cell_direct_dependents(name, old_dependents);
        return true;
    }
    else
    {
        return false;
    }
    
}

bool SpreadsheetModel::circular_dependency_check(std::set<std::string> names, std::vector<std::string> &dependents)
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
        std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(n);
        if (it == cell_dictionary.end())
        {
            return false;
        }
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
    std::unordered_map<std::string, Cell>::iterator it = cell_dictionary.find(cell_name);
    if (it == cell_dictionary.end())
    {
        Cell cell(cell_name, type);
        std::pair<std::string, Cell> insert_cell(cell_name, cell);
        cell_dictionary.insert(insert_cell);
    }
    // check for circular dependency, this will set the cell dependents if valid. 
    bool circular_dependency = circular_dependency_check(cell_name, dependents);
    // if there is one, throw exception
    if (circular_dependency)
    {
        throw CircularException(name);
    }
    // if there isn't
    else
    {
        // set cell contents and type, and push to stacks
        this->set_cell_contents_and_type(cell_name, contents, type);
        CellEdit edit;
        edit.name = cell_name;
        edit.contents = contents;
        edit.direct_dependents = dependents;
        edit.type = type;
        this->global_history.push(edit.name);
        this->push_cell_revert_history(cell_name, edit);
        this->push_cell_undo_history(cell_name, edit);
        
    }
    
}

void SpreadsheetModel::do_undo()
{
    // if the global history is empty, don't do anything
    if (!this->global_history.empty())
    {
        std::cout << "in undo global history is not empty" << std::endl;
        // get the name of the last edited cell
        std::string name = this->global_history.top();

        // remove that name from the stack
        this->global_history.pop();

        // remove from the cells undo history
        this->pop_cell_undo_history(name);
        std::cout << "popped the undo history at " << name <<  std::endl;
        // create an edit object to push onto stacks later
        CellEdit edit;

        // if the undo history is empty at this point, we have effectively 
        // hit the beginning of history, so set the edit to an empty edit. 
        if (this->check_cell_undo_history_empty(name))
        {
            edit.name = name;
            edit.contents = "";
            std::vector<std::string> dep;
            edit.direct_dependents = dep;
            edit.type = "string";
        }
        // if it's not empty, get the latest edit from the stack
        else
        {
            std::cout << "about to top the history from cell history" << std::endl;
            edit = this->top_cell_undo_history(edit.name);
            std::cout << "got the edit from the cell undo history at " << edit.name << std::endl;
        }
        std::cout << "setting the contents, dependents, and type" << std::endl;
        this->set_cell_direct_dependents(edit.name, edit.direct_dependents);
        this->set_cell_contents_and_type(edit.name, edit.contents, edit.type);            
        this->push_cell_revert_history(edit.name, edit);
    }
}

void SpreadsheetModel::do_revert(std::string name)
{
    // temp edit object
    CellEdit edit;
    // if revert history is  empty, set edit to empty object
    if (this->check_cell_revert_history_empty(name))
    {
        // if the cell history is empty, set the cell contents and dependents, and don't
        // check for circular dependency
        edit.name = name;
        edit.contents = "";
        std::vector<std::string> dep;
        edit.direct_dependents = dep;
        edit.type = "string";

        std::cout << "setting cell contents" << std::endl;
        this->set_cell_direct_dependents(edit.name, edit.direct_dependents);
        this->set_cell_contents_and_type(edit.name, edit.contents, edit.type);
        this->global_history.push(name);
        this->push_cell_undo_history(edit.name, edit);
    }
    // if revert history is not empty
    else 
    {
        // remove the last edit
        this->pop_cell_revert_history(name);

        // check if it's empty again. If it is, we have gone to the start
        // set edit to empty edit
        if (this->check_cell_revert_history_empty(name))
        {
            edit.name = name;
            edit.contents = "";
            std::vector<std::string> dep;
            edit.direct_dependents = dep;
            edit.type = "string";
        }
        // if not, get the edit from the stack
        else
        {
            edit = this->top_cell_revert_history(name);
        }
        // check for circular dependency, throw exception if needed, or make edit. 
        std::cout << "setting cell contents in revert" << std::endl;
        bool circular_dependency = circular_dependency_check(edit.name, edit.direct_dependents);
        if (circular_dependency)
        {
            this->push_cell_revert_history(edit.name, edit);
            std::cout << "Circular dependecy at " << edit.name << std::endl;
            throw CircularException(edit.name);
        }
        else
        {
            this->set_cell_contents_and_type(edit.name, edit.contents, edit.type);
            this->global_history.push(edit.name);
            this->push_cell_undo_history(edit.name, edit);
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
