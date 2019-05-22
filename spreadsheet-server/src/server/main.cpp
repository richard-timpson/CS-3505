#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Server.h"

// Server server* this_server;

void handler(int s)
{
    std::cout << "signal caught" << std::endl;
}

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

    // struct sigaction sigIntHandler;
    // sigIntHandler.sa_handler = handler;
    // sigemptyset(&sigIntHandler.sa_mask);
    // sigIntHandler.sa_flags = 0;
    // sigaction(SIGINT, &sigIntHandler, NULL);

    server.accept_clients();
    io_context.run();
    std::cout << "got past io_context run" << std::endl;
}