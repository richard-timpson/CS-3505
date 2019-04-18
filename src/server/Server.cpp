#include <iostream>
#include <string>
#include "./Server.h"
#include "ClientConnection.h"
#include "../controllers/SpreadsheetController.h"


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
                // get the message from the client
                buff.commit(size);
                std::istream istrm(&buff);
                std::string message;
                istrm >> message;
                std::cout << "message is " << message << std::endl;
                std::string error_message;
                json json_message = json::parse(message);
                bool valid_user = SpreadsheetController::validate_user(json_message, error_message);
                if (!valid_user)
                {
                    Server::send_type_1_error(connection);
                }
                std::shared_ptr<SpreadsheetModel> sm = choose_spreadsheet(json_message);
                send_full_spreadsheet(connection, sm);
            }
            else
            {
                std::cout << "Error reading spreadsheet selection " << std::endl;
            }
            
        });
}

void Server::send_full_spreadsheet(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm)
{
    std::unordered_map<std::string, Cell> cell_dictionary = sm->get_cell_dictionary();
    std::string message = SpreadsheetController::full_send(cell_dictionary);
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    // accept_edit(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });
}

void Server::send_type_1_error(std::shared_ptr<ClientConnection> connection)
{
    std::string message = SpreadsheetController::create_type_1_error();
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

bool Server::check_if_spreadsheet_in_list(json message, std::shared_ptr<SpreadsheetModel> sm)
{
    if (!SpreadsheetController::validate_login_message(message)) return false;
    bool found;
    for (std::shared_ptr<SpreadsheetModel> ss : this->spreadsheets)
    {
        if (message.value("name", "-1") == ss->get_name())
        {
            sm = ss;
            return true;
        }
    }
    return false;
}


void Server::add_client_to_list(std::shared_ptr<ClientConnection> connection)
{
    connections.insert(connection);
}

void Server::add_spreadsheet_to_list(std::shared_ptr<SpreadsheetModel> ss)
{
    spreadsheets.push_back(ss);
}

std::shared_ptr<SpreadsheetModel> Server::choose_spreadsheet(json & json_message)
{
    std::shared_ptr<SpreadsheetModel> sm(nullptr);
    std::string spreadsheet_name = json_message.value("name", "-1");
    bool is_in_list = check_if_spreadsheet_in_list(json_message, sm);
    if (!is_in_list)
    {
        std::string spreadsheet;
        bool is_in_storage = SpreadsheetController::check_if_spreadsheet_in_storage(json_message, spreadsheet);
        if (!is_in_storage)
        {
            // make new spreadsheet
            std::cout << "creating new spreadsheet" << std::endl;
            sm = std::make_shared<SpreadsheetModel>(spreadsheet_name, true);
            this->add_spreadsheet_to_list(sm);
            return sm;
        }
        else
        {
            std::cout << "loading spreadsheet from json file" << std::endl;
            sm = std::make_shared<SpreadsheetModel>(spreadsheet_name, false);
            return sm;
            // load the model from storage 
        }
    }
    else 
    {
        std::cout << "loading spreadsheet from active list" << std::endl;
        return sm;
    }
}

std::vector<std::shared_ptr<SpreadsheetModel>> Server::get_active_spreadsheets()
{
    return spreadsheets;
}

/***************************************
 * ClientConnection class
 * *************************************/

ClientConnection::ClientConnection(tcp::socket socket, Server* server)
    : socket_(std::move(socket))
{
    server_ = server;
}


