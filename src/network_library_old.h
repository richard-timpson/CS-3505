#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class network_library
{
  public:
    static void start_server();
    static void start_client();
};

class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
{
  public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context &io_context);
    tcp::socket &socket();
    void start();

  private:
    tcp_connection(boost::asio::io_context &io_context);
    void handle_write(const boost::system::error_code & error, size_t size);

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
  public:
    tcp_server(boost::asio::io_context &io_context);
  private:
    void start_accept();
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code &error);
    tcp::acceptor acceptor_;
};