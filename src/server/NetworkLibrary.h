/**
 * This is a network library used for the spreadsheet project
 * It should be a standalone library and only concern itself with
 * the transfer of the data back and forth between this server
 * and the client. It makes use of the boost::asio library
 * Most of the code is copied from this tutorial, so far
 * 
 * 
 * http://think-async.com/Asio/boost_asio_1_12_2/doc/html/boost_asio/tutorial/tutdaytime3/src.html
 * Author: Richard Timpson
 * Date: 4/2/5/2019
*/

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "chat_server_client.h"

using namespace boost::asio::ip;

/****************************************
 * chat_server_client class
 * **************************************/



// Server class 
    // executable
        // should create and start a server object that listens for client connections
        // when a client connects, create a new ClientConnection and add it to the list of ClientConnections
        // once a client has connected, tell it to listen for login string. 
        // use the network_controller to parse the string correcltly, and send back the correct edit.
        // the network_controller will take in the ClientConnection as it's paramter. 
        // the client_connections need a reference to the server, so the network_controller can tell the server 
        // to update all of the clientconnections using the network_controller. 






chat_server_client::chat_server_client(tcp::socket socket, chat_server* server)
    : socket_(std::move(socket))
{
    server_ = server;
}

void chat_server_client::do_read()
{
    std::cout << "trying to read from client" << std::endl;
    boost::asio::async_read(socket_, boost::asio::buffer(buff, 7), 
        [this](boost::system::error_code ec, std::size_t ){
            std::cout << "received  Message" << std::endl;
            if (!ec)
            {
                server_->write_to_clients(buff);
                do_read();
            }
            else 
            {
                std::cout << ec.message() << std::endl;
            }
        });
}

void chat_server_client::add_to_server()
{
    server_->add_client(shared_from_this());
    do_read();
}

// void chat_server_client::do_write()
// {
//     boost::asio::async_write(socket_, boost::asio::buffer())
// }

/****************************************
 * chat_server class
 * ***************************************/
chat_server::chat_server(boost::asio::io_context &io_context, const tcp::endpoint &endpoint)
    : acceptor_(io_context, endpoint)
{
}

void chat_server::accept_connection()
{
    // acceptor_.accept();
    // std::cout << "Accepted connection from client" << std::endl;
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            std::make_shared<chat_server_client>(std::move(socket), this)->add_to_server();
            std::cout << "Accepting connection from client" << std::endl;
        }
        else 
        {
            std::cout << ec.message() << std::endl;
        }
        accept_connection();
    });
}

void chat_server::accept_connections()
{
    accept_connection();
}

void chat_server::add_client(std::shared_ptr<chat_server_client> client)
{
    clients.insert(client);
}

void chat_server::write_to_clients(char buff[7])
{
    for (auto client: clients)
    {
        boost::asio::async_write(client->socket_, boost::asio::buffer(buff, 7), 
            [this, buff](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << std::string(buff) << std::endl;
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });
    }
}

/**************************************
 * network_library static class
 * ************************************/

void network_library::start_server(int port)
{
    // start the server, and tell it to listen for client connections.
    // if we get a new connection, start it async and store that client connection in a list of connections
    // every time the server receives a new message from the clients, send that message to the rest of the clients.

    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), port);
        tcp::socket socket(io_context);
        std::cout << "Server waiting for connection " << std::endl;

        chat_server server(io_context, endpoint);
        server.accept_connections();
        io_context.run();

    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void network_library::start_client(int port)
{
    std::cout << "htting start_client" << std::endl;
    // make a chat system
    // start the server, and tell it to listen for client connections.
    // if we get a new connection, start it async and store that client connection in a list of connections
    // every time the server receives a new message from the clients, send that message to the rest of the clients.

    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(address::from_string("127.0.0.1"), 2112);
        tcp::socket socket(io_context);
        std::cout << "client connection to server..." << std::endl;
        socket.async_connect(endpoint, [](const boost::system::error_code &ec){
            if (!ec)
            {
                std::cout << "client connection successful" << std::endl;
            }
            else 
            {
                std::cout << "error connecting" << std::endl;
            }
        });
        // std::thread t([&io_context](){   
        // });

        char line[7]="hello\n";
        char read[7];
        char waste[10];
        while(std::cin.getline(waste, 10))
        {
            std::cout << "trying to write message " << std::string(line) << std::endl;
            boost::asio::async_write(socket, boost::asio::buffer(line, 7), 
                [](boost::system::error_code ec, std::size_t bytes_transferred) {
                    std::cout << "async writing" << std::endl;
                    if (!ec)
                    {
                        std::cout << "succesfully wrote message " << std::endl;
                    }
                    else
                    {
                        std::cout << "error writing message" << std::endl;
                    }
                    
                });
            std::cout << "trying to receive message " << std::endl;
            boost::asio::async_read(socket, boost::asio::buffer(read, 7), 
            [read](boost::system::error_code ec, std::size_t ){
                std::cout << "received  Message " << read << std::endl;
                if (!ec)
                {
                    std::cout << read << std::endl;
                }
                else 
                {
                    std::cout << ec.message() << std::endl;
                }
            });
            io_context.run();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}