#ifndef SERVER
#define SERVER

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <set>
#include "ClientConnection.h"
#include "../models/SpreadsheetModel.h"
#include "../../libs/json.hpp"

using json = nlohmann::json;

using namespace boost::asio::ip;


class Server 
{
  public:
    // Constructor
    Server(boost::asio::io_context& context, const tcp::endpoint& endpoint);

    // networking functions
    void accept_clients();
    void refresh_admin(std::shared_ptr<ClientConnection> connection);
    void admin_parser_operations(std::shared_ptr<ClientConnection> connection);
    void accept_spreadsheet_selection(std::shared_ptr<ClientConnection> connection);
    void accept_edit(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm);
    void send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection);
    void send_type_1_error(std::shared_ptr<ClientConnection> connection);
    void send_type_2_error(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm);
    void send_full_spreadsheet(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm);

    // member functions
    void admin_controller_list(std::shared_ptr<ClientConnection> connection);
    void add_client_to_list(std::shared_ptr<ClientConnection> connection);
    void add_spreadsheet_to_list(std::shared_ptr<SpreadsheetModel> ss);
    std::shared_ptr<SpreadsheetModel> choose_spreadsheet(json &json_message);
    bool check_if_spreadsheet_in_list(json message, std::shared_ptr<SpreadsheetModel> sm);


    // getters/setters
    std::vector<std::shared_ptr<SpreadsheetModel>> get_active_spreadsheets();
    
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<ClientConnection>> connections;
    std::set<std::shared_ptr<ClientConnection>> admin_connections;
    boost::asio::streambuf buff;
    std::vector<std::shared_ptr<SpreadsheetModel>> spreadsheets;
};

#endif