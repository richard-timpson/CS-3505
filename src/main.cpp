#include <iostream>
#include <string>
#include "network_controller.cpp"
#include "spreadsheet_controller.h"
#include "user_model.h"
#include "spreadsheet_model.h"
#include "network_library.h"

int main(int argc, char ** argv)
{
    std::string address(argv[2]);
    std::cout << "hitting before conversion" << std::endl;
    std::cout << address << argv[3] << std::endl;
    int port = std::atoi(argv[3]);
    std::cout << "going past conversion " << std::endl;
    if (argv[1][0] == 's')
    {
        network_library::start_server(address, port);
    }
    else
    {
        std::cout << "starting client" << std::endl;
        network_library::start_client(address, port);    
    } 
    


    std::cout << "Main executable" << std::endl;
}