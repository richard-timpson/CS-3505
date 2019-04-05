#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include <iostream>
#include "network_library.h"
#include <asio.hpp>

using asio::ip::tcp;

/* Our networking library */
void network_library::start_server()
{
    try
    {
        asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/*****************************
 * tcp_server from tutorial
 * **************************/
tcp_server::tcp_server(asio::io_context &io_context)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
{
    start_accept();
}

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_executor().context());

    acceptor_.async_accept( new_connection->socket(), std::bind(&tcp_server::handle_accept, this, new_connection, std::placeholders::_1));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const asio::error_code &error)
{
    if (!error)
    {
        new_connection->start();
    }

    start_accept();
}


/***************************************
 * tcp_connection from tutorial
 * ************************************/
tcp_connection::tcp_connection(asio::io_context &io_context)
    : socket_(io_context)
{
}

tcp_connection::pointer tcp_connection::create(asio::io_context &io_context)
{
    return pointer(new tcp_connection(io_context));
}

tcp::socket & tcp_connection::socket()
{
    return socket_;
}

void tcp_connection::start()
{
    message_ = "this is a test string";
    asio::async_write( socket_, asio::buffer(message_), std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_1));
}


void tcp_connection:: handle_write(const std::error_code & /*error*/, size_t /*bytes_transferred*/)
{
}
