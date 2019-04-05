#include <asio.hpp>

using asio::ip::tcp;

class network_library
{
  public:
    static void start_server();
};
class tcp_connection
    : public std::enable_shared_from_this<tcp_connection>
{
  public:
    typedef std::shared_ptr<tcp_connection> pointer;
    static pointer create(asio::io_context &io_context);
    tcp::socket &socket();
    void start();

  private:
    tcp_connection(asio::io_context &io_context);
    void handle_write(const asio::error_code & /*error*/, size_t /*bytes_transferred*/);

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
  public:
    tcp_server(asio::io_context &io_context);
  private:
    void handle_accept(tcp_connection::pointer new_connection, const asio::error_code &error);
    void start_accept();

    tcp::acceptor acceptor_;
};

