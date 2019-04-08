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

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "network_library.h"

using boost::asio::ip::tcp;

void network_library::start_server()
{
    // need to get the point where I can open up the server to listen for socket connections
    // and transfer data back and forth. 
    try
    {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

/***********************************************************
 * tcp_server from tutorial
 * ********************************************************/

tcp_server::tcp_server(boost::asio::io_context &io_context)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
{
    start_accept();
}

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_executor().context());

    acceptor_.async_accept(new_connection->socket(), boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error)
{
    if (!error)
    {
        new_connection->start();
    }

    start_accept();
}

/*************************************************************************
 * tcp_connection fromm tutorial
 * **********************************************************************/

tcp_connection::pointer tcp_connection::create(boost::asio::io_context &io_context)
{
    return pointer(new tcp_connection(io_context));
}

tcp::socket & tcp_connection::socket()
{
    return socket_;
}

void tcp_connection::start()
{
    message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_), boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

tcp_connection::tcp_connection(boost::asio::io_context &io_context)
    : socket_(io_context)
{
}

void tcp_connection::handle_write(const boost::system::error_code & /*error*/, size_t /*bytes_transferred*/)
{
}

