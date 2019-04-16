#include <iostream>
#include <string>
#include "./Server.h"
#include "ClientConnection.h"
#include "../controllers/SpreadsheetController.h"
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
    // char message[256] ="Sending list of spreadsheets to client\n";
    std::string message = SpreadsheetController::get_list_of_spreadsheets();
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_spreadsheet_selection(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });
}

void Server::accept_spreadsheet_selection(std::shared_ptr<ClientConnection> connection)
{
    std::cout << "trying to accept spreadsheet selection " << std::endl;
    boost::asio::async_read_until(connection->socket_, buff, "\n\n", 
        [connection, this](boost::system::error_code ec, std::size_t size){
            std::cout << "async read handler called" << std::endl;
            if (!ec)
            {
<<<<<<< HEAD
                boost::asio::streambuf::const_buffers_type bufs = buff.data();
                std::string message(boost::asio::buffers_begin(bufs),
                boost::asio::buffers_begin(bufs) + size);
                std::cout << "Accepting spreadsheet selection " << message <<  std::endl;
                // call Spreadsheet::validate(json)
=======
                // get the message from the client
                buff.commit(size);
                std::istream istrm(&buff);
                std::string message;
                istrm >> message;
                std::cout << "message is " << message << std::endl;

                // std::string error_message;
                // bool valid_user = SpreadsheetController::validate_user(message, error_message);
                // if (!valid_user)
                // {
                //     // print error message
                // }

                // SpreadsheetModel* s_model;
                // bool valid_model = SpreadsheetController:validate_model(message, s_model, error_message )
                // if (!valid_model)
                // {
                //     // print error message
                // }



                // need to validate user login
>>>>>>> ddebdf4da13d79ca010fcfdc00f344a3b6e2c4d4

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


