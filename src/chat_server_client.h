#ifndef CHAT_SERVER_CLIENT
#define CHAT_SERVER_CLIENT
#include <memory>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

class chat_server;
class chat_server_client : public std::enable_shared_from_this<chat_server_client>
{
  public:
    chat_server_client(tcp::socket socket, chat_server* server);
    void do_read();
    void do_write();
    void add_to_server();
    tcp::socket socket_;
  private:
    chat_server *server_;
    char buff[256];
};

#endif