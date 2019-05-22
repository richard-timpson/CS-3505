#ifndef CHAT_SERVER_CLIENT
#define CHAT_SERVER_CLIENT
#include <memory>
#include <boost/asio.hpp>

using namespace boost::asio::ip;
// git stuff
class Server;
class ClientConnection : public std::enable_shared_from_this<ClientConnection>
{
  public:
    ClientConnection(tcp::socket socket, Server* server);
    void do_read();
    void do_write();
    void add_to_server();
    void set_name(std::string name)
    {
        this->spreadsheet_name = name;
    }
    void set_user_name(std::string name)
    {
        this->user_name = name;
    }
    std::string get_name()
    {
        return this->spreadsheet_name;
    }
    std::string get_user_name()
    {
        return this->user_name;
    }
    tcp::socket socket_;
    boost::asio::streambuf buff;
  private:
    Server *server_;
    std::string spreadsheet_name;
    std::string user_name;
};

#endif