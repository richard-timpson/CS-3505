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
    void send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection);
    void accept_spreadsheet_selection(std::shared_ptr<ClientConnection> connection);
    void send_type_1_error(std::shared_ptr<ClientConnection> connection);

    // member functions
    void add_client_to_list(std::shared_ptr<ClientConnection> connection);
    void add_spreadsheet_to_list(std::shared_ptr<SpreadsheetModel> ss);
    bool check_if_spreadsheet_in_list(json message);


    // getters/setters
    std::vector<std::shared_ptr<SpreadsheetModel>> get_active_spreadsheets();
    
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<ClientConnection>> connections;
    boost::asio::streambuf buff;
    std::vector<std::shared_ptr<SpreadsheetModel>> spreadsheets;
};

#endif