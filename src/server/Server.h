#ifndef SERVER
#define SERVER

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <set>
#include "ClientConnection.h"

//hey
class Server 
{
  public:
//     static std::set<ClientConnections> connections;
    Server(boost::asio::io_context& context, const tcp::endpoint& endpoint);
    void accept_clients();
    void add_client_to_list(std::shared_ptr<ClientConnection> connection);
    void send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection);
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<ClientConnection>> connections;
};

#endif