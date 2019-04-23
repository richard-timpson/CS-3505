/*
 * The main class used to represent the state of the spreadsheet. 
 * Holds a global history which is used for the undo command, 
 * and also holds a dictionary that maps cell names to Cell objects
 * to represent the state of each individual edited cell. 
 *
 */

#ifndef SPREADSHEETMODEL_H
#define SPREADSHEETMODEL_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include "Cell.h"
#include "CellEdit.h"
#include "UserModel.h"

class SpreadsheetModel
{
  public:

    /**************
     * Contstructor
     * ************/

    /*
     * Main contstructor for SpreadsheetModel. 
     * Takes in an input_name which is set when the model is created. 
     * Also takes a bool specifying a this model is a new spreadsheet. 
     * If new_ss is true, the contrusctor will not load the model from 
     * existing json file
     */
    SpreadsheetModel(std::string filepath, bool new_ss);

    /******
     * Name
     * ****/

    // set the name for spreadsheet
    void set_name(std::string name);
    //get the name for spreadsheet
    std::string get_name();

    /****************
     * Global History
     * **************/

    // Returns a copy (not a reference) of the global history of spreadsheet
    std::stack<std::string> get_global_history();

    /*************************
     * Cell contents, and type
     * ***********************/

    /**
     * Updates the cell dictionary to either create a cell in the cell dictionary
     * or update an existing cell. –
     * name: Specifies the name to update/create –
     * contents: The new contents for the cell –
     * dependents: A list of cell names that specifies this cells dependents –
     * type: The type of the cell –
     */ 
    void set_cell_contents(std::string name, std::string contents, std::vector<std::string> &dependents, std::string type);
    /**
     *  Uses the cell dictionary to return the contents of a certain cell
     */
    std::string get_cell_contents(std::string name);
    /**
     *  Uses the cell dictionary to return the type of a certain cell
     */ 
    std::string get_cell_type(std::string name);

    /******************
     * Personal history
     * ***************/

    /** Returns a copy of the stack stored at a cells history –
     * name{string}: The name of the cells revert history stack to return
     */ 
    std::stack<CellEdit> get_cell_revert_history(std::string name);
    /** Pushes to a cell history in the cell_dictionary –
     * name{string}: The name of cell to update –
     * input{CellEdit}: The CellEdit to store at the revert history –
     */ 
    void push_cell_revert_history(std::string name, CellEdit input);
    /** Pops (removes) from the cell's revert history –
     * name{string}: The name of the cell's history to pop –
     */ 
    void pop_cell_revert_history(std::string name);
    /** Checks if the cell revert history is empty –
     * name{string}: The name of the cell's revert history to check
     */
    bool check_cell_revert_history_empty(std::string name);
    /**
     * returns the top of the stack of the cell revert history –
     * name{string}: The name of the cell's revert history to top –
     * returns: The CellEdit object stored in the revert history –
     */
    CellEdit top_cell_revert_history(std::string name);
    
    /**************
     * Undo history
     * ************/

    /** Returns a copy of the stack stored at a cells history –
     * name{string}: The name of the cells undo history stack to return
     */ 
    std::stack<CellEdit> get_cell_undo_history(std::string name);
    /** Pushes to a cell undo history in the cell_dictionary –
     * name{string}: The name of cell to update –
     * input{CellEdit}: The CellEdit to store at the undo history –
     */ 
    void push_cell_undo_history(std::string name, CellEdit input);
    /** Pops (removes) from the cell's undo history –
     * name{string}: The name of the cell's undo history to pop –
     */ 
    void pop_cell_undo_history(std::string name);
    /** Checks if the cell revert history is empty –
     * name{string}: The name of the cell's undo history to check
     */
    bool check_cell_undo_history_empty(std::string name);
    /**
     * returns the top of the stack of the cell undo history –
     * name{string}: The name of the cell's undo history to top –
     * returns: The CellEdit object stored in the undo history –
     */
    CellEdit top_cell_undo_history(std::string name);

    /****************************************
     * Direct dependents, and cell dictionary
     * **************************************/

    /**
     * Returns the direct dependents stored at a cell –
     * name{string}: The name of the cell to return the dependents of
     */ 
    std::vector<std::string> get_cell_direct_dependents(std::string name);
    /**
     * The main storage of the spreadsheet
     */ 
    std::unordered_map<std::string, Cell> get_cell_dictionary();

    /*******************
     * Storage Functions
     * *****************/

    /**
     * Loads the spreadsheet file from it's associated .json file, using the name property to find the right file
     */ 
    void read_json_ss_file();
    /**
     * Writes to .json file the spreadsheet is associated with, using the name property to build the right file
     */ 
    void write_json_ss_file();
    /**
     * Writes the name of the spreadsheet to spreadsheets.txt if needed (if it hasn't already been written)
     */ 
    void write_ss_file_if_needed();
    /** 
     * TODO: Document this function
     */ 
    void create_new_json_file();

    /***************
     * Edit commands
     * *************/

    /**
     * Performs a standard edit on the entire spreadsheet
     * name: Specifies the name to update/create –
     * contents: The new contents for the cell –
     * dependents: A list of cell names that specifies this cells dependents –
     * type: The type of the cell –
     */ 
    void do_edit(std::string cell_name, std::string contents, std::vector<std::string> &dependents, std::string type);
    /**
     * Performs a standard undo function on the entire spreadsheet
     */ 
    void do_undo();
    /**
     * Performs a standard revert function on the entire spreadsheet –
     * name{string}: The name of the cell we need to revert
     */ 
    void do_revert(std::string name);


    /***************************
     * Circular dependency check
     * *************************/


    /**
     * An overload of circular_dependecy check. 
     * Converts the name passed in to a singleton set, and calls
     * circular_dependency_check with that set
     */ 
    bool circular_dependency_check(std::string name);
    /**
     * Uses a dfs to check all of the dependents of each cell in the specified set
     * to check for a circular dependency. –
     * returns: Boolean value specifiying if circular dependency is there
     */ 
    bool circular_dependency_check(std::set<std::string> names);

  private:
    // used in dfs for circular dependency check
    bool visit(std::string &start, std::string &name, std::set<std::string> & visited, std::vector<std::string> & changed);

    // useless?
    bool edit_made;

    // the main data structure for the spreadsheet
    std::unordered_map<std::string, Cell> cell_dictionary;

    std::set<UserModel> users;

    // the stack that represents the order of which cells have been edited. 
    std::stack<std::string> global_history;

    // the name of the spreadsheet.
    std::string name;
};

#endif
