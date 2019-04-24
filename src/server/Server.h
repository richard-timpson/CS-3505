#ifndef SERVER
#define SERVER

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <set>
#include "ClientConnection.h"
#include "../models/SpreadsheetModel.h"
#include "../../libs/json.hpp"
#include "../models/UserModel.h"

using json = nlohmann::json;

using namespace boost::asio::ip;


class Server 
{
  public:
    // Constructor
    Server();
    Server(boost::asio::io_context& context, const tcp::endpoint& endpoint);

    // networking functions
    void accept_clients();
    void refresh_admin(std::shared_ptr<ClientConnection> connection);
    void admin_parser_operations(std::shared_ptr<ClientConnection> connection);
    void admin_add_user(std::string add_user_username, std::string add_user_password);
    void admin_delete_user(std::string delete_user_username);
    void admin_add_spreadsheet(json json_message);
    void admin_delete_spreadsheet(json json_message);
    void admin_remove_spreadsheet(json json_message);
    void admin_remove_client(json json_message);
    void accept_spreadsheet_selection(std::shared_ptr<ClientConnection> connection);
    void accept_edit(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm);
    void send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection);
    void send_type_1_error(std::shared_ptr<ClientConnection> connection);
    void send_type_2_error(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm, std::string cell_name);
    void send_full_spreadsheet(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm);
    void send_full_spreadsheet_to_clients(std::shared_ptr<SpreadsheetModel> sm);


    // member functions
    void admin_controller_list(std::shared_ptr<ClientConnection> connection);
    void add_client_to_list(std::shared_ptr<ClientConnection> connection);
    void remove_client_from_list(std::shared_ptr<ClientConnection> connection);
    void remove_sm_from_list(std::shared_ptr<SpreadsheetModel> sm);
    void add_spreadsheet_to_list(std::shared_ptr<SpreadsheetModel> ss);
    /**
     * Takes the json message and returns a spreadsheet model that will 
     * point to an active spreadsheet if it exists. If no spreadsheet exists
     * it will return a new empty spreadsheet model.
     */ 
    std::shared_ptr<SpreadsheetModel> choose_spreadsheet(json &json_message, UserModel user);
    /**
     * If we have a valid user, will check if the user exists in the current list
     * If it does, it will return that user, if it doesn't, it will create a new one,
     * and return that
     */ 
    UserModel choose_user(json & message);

    bool check_if_spreadsheet_in_list(json message, std::shared_ptr<SpreadsheetModel> &sm);
    void save_file_if_needed(std::shared_ptr<SpreadsheetModel> sm);
    /**
     * Checks if username exsits, but password doesn't match. 
     */ 
    bool validate_user(json json_message);
    void remove_user_from_list(UserModel user);
    void shutdown();
    void close_all_connections();
    void load_data();
    void save_data();
    


    // getters/setters
    std::set<std::shared_ptr<SpreadsheetModel>> get_active_spreadsheets();

    /**
     * This function will load all of the necessary data on 
     * the server startup. It will load the users from user.txt into an active users list,
     * and it will load the spreadsheets from spreadsheets.txt and associated json files into
     * an active spreadsheets list. 
     */ 
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<ClientConnection>> connections;
    //std::set<std::shared_ptr<ClientConnection>> admin_connections;
    boost::asio::streambuf buff;
    std::set<std::shared_ptr<SpreadsheetModel>> spreadsheets;
    std::vector<UserModel> users;
};

#endif