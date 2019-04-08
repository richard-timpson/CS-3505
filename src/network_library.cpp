/**
 * This is a network library used for the spreadsheet project
 * It should be a standalone library and only concern itself with
 * the transfer of the data back and forth between this server
 * and the client. It makes use of the boost::asio library
 * Most of the code is copied from this tutorial, so far
 * 
 * 
 * http://think-async.com/Asio/boost_asio_1_12_2/doc/html/boost_asio/tutorial/tutdaytime3/src.html
 * 
 * Author: Richard Timpson
 * Date: 4/2/5/2019
*/

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "network_library.h"

using namespace boost::asio::ip;

/****************************************
 * chat_server_client class
 * **************************************/

chat_server_client::chat_server_client(tcp::socket socket, chat_server* server)
    : socket_(std::move(socket))
{
    server_ = server;
}

void chat_server_client::do_read()
{
    boost::asio::async_read(socket_, boost::asio::buffer(buff, 256), 
        [this](boost::system::error_code ec, std::size_t ){
            if (!ec)
            {
                server_->write_to_clients();
            }
        });
}

void chat_server_client::add_to_server()
{
    server_->add_client(shared_from_this());
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
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            std::make_shared<chat_server_client>(std::move(socket), this)->add_to_server();
            std::cout << "Accepting connection from client" << std::endl;
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

void write_to_clients()
{

}

/**************************************
 * network_library static class
 * ************************************/

void network_library::start_server()
{
    // start the server, and tell it to listen for client connections.
    // if we get a new connection, start it async and store that client connection in a list of connections
    // every time the server receives a new message from the clients, send that message to the rest of the clients.

    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), 81);
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

void network_library::start_client()
{

    // make a chat system
    // start the server, and tell it to listen for client connections.
    // if we get a new connection, start it async and store that client connection in a list of connections
    // every time the server receives a new message from the clients, send that message to the rest of the clients.

    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(address::from_string("127.0.0.1"), 81);
        tcp::socket socket(io_context);
        std::cout << "client connection to server..." << std::endl;
        socket.connect(endpoint);
        std::cout << "Clicent connection successfull" << std::endl;

        // socket.async_read_some(boost::asio::buffer(network_library::buff), ReadHandler);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}