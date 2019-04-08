#include <iostream>
#include "network_controller.cpp"
#include "spreadsheet_controller.h"
#include "user_model.h"
#include "spreadsheet_model.h"
#include "network_library.h"

int main(int argc, char ** argv)
{
    if (argv[1][0] == 's')
        network_library::start_server();
    else 
        network_library::start_client();    
    
    std::cout << "Main executable" << std::endl;
}