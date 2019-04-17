#include "../controllers/SpreadsheetController.h"
#include "../server/Server.h"
#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include <boost/asio.hpp>

using namespace boost::asio::ip;
using json = nlohmann::json;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}

void test1()
{
    std::cout << "Test 1: Getting list of spreadsheets" << std::endl;
    std::string sheets = SpreadsheetController::get_list_of_spreadsheets();
    std::cout << "\t" << sheets << std::endl;
    std::cout << "Test 1 finished " << std::endl;

}
void test2()
{
    std::cout << "Test 2: Getting current user" << std::endl;
    json message;
    message["type"] = "open";
    message["username"] = "hello";
    message["password"] = "hi";
    std::string error_message;
    bool is_valid = SpreadsheetController::validate_user(message, error_message);
    std::cout << "Test 2 finished " << std::endl;

}
void test3()
{
    std::cout << "Test 3: creating new user" << std::endl;
    json message;
    message["type"] = "open";
    message["username"] = "hey";
    message["password"] = "hey";
    std::string error_message;
    bool is_valid2 = SpreadsheetController::validate_user(message, error_message);
    std::cout << "Test 3 finished " << std::endl;

}
void test4()
{
    std::cout << "Test 4: invalid string type on user validation" << std::endl;
    json message;
    message["random"] = "open";
    std::string error_message;
    bool is_valid3 = SpreadsheetController::validate_user(message, error_message);
    if (is_valid3)
    {
        std::cout << "Test failed " << std::endl;
    }
    else 
    {
        std::cout << "Test succedded " << std::endl;
    }
    std::cout << "Test 4 finished " << std::endl;
}

void test5()
{
    std::cout << "Test 5: check spreadhseet list with empty spreadsheet" << std::endl;
    int port = 2112;
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), port);
    Server server(io_context, endpoint);
    json message;
    message["name"] = "test";
    bool valid = server.check_if_spreadsheet_in_list(message);
    if (valid)
    {
        std::cout << "\tTest 5 failed!" << std::endl;
    }
    else
    {
        std::cout << "\tTest 5 passed!" << std::endl;
    }
    
}

void test6()
{
    std::cout << "Test 6: check spreadhseet list with non-empty spreadsheet" << std::endl;
    int port = 2112;
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), port);
    Server server(io_context, endpoint);
    json message;
    message["name"] = "test";
    message["username"] = "test";
    message["password"] = "test";
    message["type"] = "open";
    // std::shared_ptr<ClientConnection> connection = std::make_shared<ClientConnection>(std::move(socket), this);
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>();
    sm->set_name("test");
    server.add_spreadsheet_to_list(sm);
    bool in_sheet = server.check_if_spreadsheet_in_list(message);
    if (in_sheet)
    {
        std::cout << "\tTest 6 passed!" << std::endl;
    }
    else
    {
        std::cout << "\tTest 6 failed!" << std::endl;
    }
    
}