#include <iostream>
#include <string>
#include "./Server.h"
#include "ClientConnection.h"

using namespace boost::asio::ip;

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
    server.accept_clients();
    io_context.run();
}


/********************************************
 * Server class
 * ******************************************/

Server::Server(boost::asio::io_context &context, const tcp::endpoint &endpoint)
    : acceptor_(context, endpoint)
{
}

void Server::accept_clients()
{
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            std::shared_ptr<ClientConnection> connection = std::make_shared<ClientConnection>(std::move(socket), this);
            add_client_to_list(connection);
            std::cout << "Accepted connection from client" << std::endl;
            send_spreadsheet_list_to_client(connection);
        }
        else
        {
            std::cout << ec.message() << std::endl;
        }
        accept_clients();
    });
}

void Server::add_client_to_list(std::shared_ptr<ClientConnection> connection)
{
    connections.insert(connection);
}

void Server::send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection)
{
    // some vector = get_list_of_spreadsheets. 
    //std::string message = SpreadsheetController::get_list_of_spreadsheets();
    char message[256] ="Sending list of spreadsheets to client\n";
    // std::string message = "Sending list of spreadsheet to client";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message, strlen(message)), 
            [message, &connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_spreadsheet_connection(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });
}

void Server::accept_spreadsheet_connection(std::shared_ptr<ClientConnection> connection)
{
    boost::asio::streambuf buff;
    boost::asio::async_read_until(connection->socket_, buff, '\n', 
        [&buff, &connection](boost::system::error_code ec, std::size_t size){
            if (!ec)
            {
                boost::asio::streambuf::const_buffers_type bufs = buff.data();
                std::string message(boost::asio::buffers_begin(bufs),
                boost::asio::buffers_begin(bufs) + size);
                std::cout << "Accepting spreadsheet selection " << message <<  std::endl;
                // needs to validate correct string, and exit if not
                // t

            }
            else
            {
                std::cout << "Error reading spreadsheet selection " << std::endl;
            }
            
        });
}


/***************************************
 * ClientConnection class
 * *************************************/

ClientConnection::ClientConnection(tcp::socket socket, Server* server)
    : socket_(std::move(socket))
{
    server_ = server;
}


