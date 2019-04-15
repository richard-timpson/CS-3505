#ifndef NETWORK_LIBRARY_H
#define NETWORK_LIBRARY_H

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "chat_server_client.h"

using boost::asio::ip::tcp;

class network_library
{
  public:
    static void start_server(std::string address, int port);
    static void start_client(std::string address, int port);
};

class chat_server
{
  public:
    chat_server(boost::asio::io_context& context, const tcp::endpoint& endpoint);
    void accept_connection();
    void accept_connections();
    void write_to_clients(char buff[256]);
    void add_client(std::shared_ptr<chat_server_client> client);
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<chat_server_client>> clients;
};


#endif