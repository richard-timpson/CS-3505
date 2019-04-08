#include <string>
#include <vector>
#include <memory>
#include <set>
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

class chat_server
{
  public:
    chat_server(const chat_server & server);
    chat_server(boost::asio::io_context& context, const tcp::endpoint& endpoint);
    void accept_connection();
    void accept_connections();
    void write_to_clients();
    void add_client(std::shared_ptr<chat_server_client> client);
  private:
    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<chat_server_client>> clients;
};

class chat_server_client : public std::enable_shared_from_this<chat_server_client>
{
  public:
    chat_server_client(tcp::socket socket, chat_server* server);
    void do_read();
    void do_write();
    void add_to_server();
  private:
    tcp::socket socket_;
    chat_server *server_;
    char buff[256];
};