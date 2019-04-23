#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Server.h"



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Please provide the port number" << std::endl;
        return -1;
    }
    int port = std::atoi(argv[1]);
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), port);
    Server server(io_context, endpoint);
    server.load_data();
    server.accept_clients();
    io_context.run();
}