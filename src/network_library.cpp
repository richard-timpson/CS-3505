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
#include "chat_server_client.h"

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
    std::cout << "trying to read from client" << std::endl;
    boost::asio::async_read(socket_, boost::asio::buffer(buff, 256), 
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

void chat_server::write_to_clients(char buff[256])
{
    for (auto client: clients)
    {
        boost::asio::async_write(client->socket_, boost::asio::buffer(buff, 256), 
            [this, buff](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message" << std::string(buff) << std::endl;
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

void network_library::start_server(std::string address, int port)
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

void network_library::start_client(std::string address, int port)
{
    std::cout << "htting start_client" << std::endl;
    // make a chat system
    // start the server, and tell it to listen for client connections.
    // if we get a new connection, start it async and store that client connection in a list of connections
    // every time the server receives a new message from the clients, send that message to the rest of the clients.

    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(address::from_string("155.98.111.121"), 2112);
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
            io_context.run();
        // });

        char line[4];
        while(std::cin.getline(line, 4))
        {
            std::cout << "trying to write message " << std::string(line) << std::endl;
            // boost::asio::post(io_context, [&socket, line](){
            //     std::cout << "posting" << std::endl;
                boost::asio::async_write(socket, boost::asio::buffer(line, 4), 
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
            // });
        }
        // t.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}