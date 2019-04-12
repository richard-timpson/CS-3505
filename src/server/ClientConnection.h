#ifndef CHAT_SERVER_CLIENT
#define CHAT_SERVER_CLIENT
#include <memory>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

class Server;
class ClientConnection : public std::enable_shared_from_this<ClientConnection>
{
  public:
    ClientConnection(tcp::socket socket, Server* server);
    void do_read();
    void do_write();
    void add_to_server();
    tcp::socket socket_;
    char buff[256];
  private:
    Server *server_;
};

#endif