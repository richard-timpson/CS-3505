#include <iostream>
#include <string>
#include "./Server.h"
#include "ClientConnection.h"


main(int argc, char **argv)
{
  std::shared_ptr<ClientConnection> connection;
  
  std::cout << Server::send_spreadsheet_list_to_client(connection) << std::endl;
}
