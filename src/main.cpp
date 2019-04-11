#include <iostream>
#include <string>
#include "network_controller.cpp"
#include "spreadsheet_controller.h"
#include "user_model.h"
#include "spreadsheet_model.h"
#include "network_library.h"

int main(int argc, char ** argv)
{
    int port = std::atoi(argv[2]);
    if (argv[1][0] == 's')
    {
        network_library::start_server(port);
    }
    else
    {
        network_library::start_client(port);    
    } 
    


    std::cout << "Main executable" << std::endl;
}