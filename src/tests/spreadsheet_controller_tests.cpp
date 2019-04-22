#include "../controllers/SpreadsheetController.h"
#include "../server/Server.h"
#include <string>
#include <iostream>
#include "../../libs/json.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>

using namespace boost::asio::ip;
using json = nlohmann::json;


void print_success_or_failure(bool success);
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();

void testSpreadsheetSelection();

void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();
void test16();
void test17();
void test18();
void test19();


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    testSpreadsheetSelection();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();

}

void test1()
{
    // std::cout << "Test 1: Getting list of spreadsheets" << std::endl;
    // std::string sheets = SpreadsheetController::get_list_of_spreadsheets();
    // std::cout << "\t" << sheets << std::endl;
    // std::cout << "Test 1 finished " << std::endl;
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
    message["username"] = "test";
    message["password"] = "test";
    message["type"] = "open";
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    bool valid = server.check_if_spreadsheet_in_list(message, sm);
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
    std::cout << "Test 6: check spreadsheet list with non-empty spreadsheet" << std::endl;
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
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    std::shared_ptr<SpreadsheetModel> new_sm = std::make_shared<SpreadsheetModel>("test1", true);

    server.add_spreadsheet_to_list(sm);
    bool in_sheet = server.check_if_spreadsheet_in_list(message, new_sm);
    if (in_sheet)
    {
        std::cout << "\tTest 6 passed!" << std::endl;
    }
    else
    {
        std::cout << "\tTest 6 failed!" << std::endl;
    }
}

void test7()
{
    // std::cout << "Test 7: choose spreadsheet that's not in active or txt file" << std::endl;
    // int port = 2112;
    // boost::asio::io_context io_context;
    // tcp::endpoint endpoint(tcp::v4(), port);
    // Server server(io_context, endpoint);
    // json message;
    // message["name"] = "test";
    // message["username"] = "test";
    // message["password"] = "test";
    // message["type"] = "open";

    // // make a copy of spreadsheets.txt
    // std::rename("../../data/spreadsheets.txt", "../../data/spreadsheets_temp.txt");

    // // make an empty spreadsheets.txt file
    // std::ofstream write_file;
    // write_file.open("../../data/spreadsheets.txt");
    // write_file << "";
    // write_file.close();

    // // choose the spreadsheet
    // std::shared_ptr<SpreadsheetModel> sm = server.choose_spreadsheet(message);

    // // delete the spreadsheets.txt with no entries, and replace it with temp
    // std::remove("../../data/spreadsheets.txt");
    // std::rename("../../data/spreadsheets_temp.txt", "../../data/spreadsheets.txt");

    // bool success;
    // if (sm->get_name() != "test")
    // {
    //     success = false;
    // }
    // else 
    // {
    //     success = false;
    // }
    // print_success_or_failure(success);

    // std::cout << "Test 7 finished" << std::endl;
}

void test8()
{
    std::cout << "Test 8: choose spreadsheet that's in active list" << std::endl;
    int port = 2112;
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), port);
    Server server(io_context, endpoint);
    json message;
    message["name"] = "test";
    message["username"] = "test";
    message["password"] = "test";
    message["type"] = "open";

    std::shared_ptr<SpreadsheetModel> test_sm = std::make_shared<SpreadsheetModel>("test", true);
    server.add_spreadsheet_to_list(test_sm);

    std::shared_ptr<SpreadsheetModel> sm = server.choose_spreadsheet(message);

    std::cout << "\tTest 8 finished" << std::endl;
}

void test9()
{
    std::cout << "Test 9: choose spreadsheet that's not in active but in text file" << std::endl;
    int port = 2112;
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), port);
    Server server(io_context, endpoint);
    json message;
    message["name"] = "test";
    message["username"] = "test";
    message["password"] = "test";
    message["type"] = "open";

    // write test to the file and close file stream
    std::ofstream write_file;
    write_file.open("../../data/spreadsheets.txt", std::ios::app);
    write_file << std::endl << "test" << std::endl;
    write_file.close();

    // choose the spreadsheet
    std::shared_ptr<SpreadsheetModel> sm = server.choose_spreadsheet(message);

    // open up write file stream
    write_file.open("../../data/spreadsheets_temp.txt", std::ios::app);

    // open up read file stream 
    std::ifstream read_file;
    read_file.open("../../data/spreadsheets.txt");
    std::string line;
    while (std::getline(read_file,line ))
    {
        if (line != "test")
        {
            write_file << line << std::endl;
        }
    }

    write_file.close();
    read_file.close();
    std::remove("../../data/spreadsheets.txt");
    std::rename("../../data/spreadsheets_temp.txt", "../../data/spreadsheets.txt");

    std::cout << "\tTest 9 finished" << std::endl;

}

void testSpreadsheetSelection()
{
    test7();
    test8();
    test9();
}


/**
 * Test full send
 */
void test10()
{
    SpreadsheetModel alpha("SM", true);
    std::cout << "Test 10: Test for correct full send string" << std::endl;
    std::vector<std::string> a1_dependents;
    std::vector<std::string> a2_dependents{"A1"};
    std::vector<std::string> a3_dependents{"A2"};
    std::vector<std::string> a4_dependents{"A3"};
    std::vector<std::string> a5_dependents{"A4"};
    alpha.set_cell_contents("A1", "5", a1_dependents, "int" );
    alpha.set_cell_contents("A2", "A1 + 5", a2_dependents, "string" );
    alpha.set_cell_contents("A3", "A2 + 5", a3_dependents, "string" );
    alpha.set_cell_contents("A4", "A3 + 5", a4_dependents, "string" );
    alpha.set_cell_contents("A5", "A4 + 5", a5_dependents, "string" );
    alpha.set_cell_contents("A6", "2.00012341234", a5_dependents, "double" );


    std::unordered_map<std::string, Cell> cell_dictionary = alpha.get_cell_dictionary();
    std::cout << "\t" << SpreadsheetController::full_send(cell_dictionary) << std::endl;

    std::cout << "Test 10 finished" << std::endl;

}

/**
 * Test full send
 */
void test11()
{
    SpreadsheetModel alpha("SM", true);
    std::cout << "Test 11: Test for correct full send string on new spreadsheet creation" << std::endl;
    std::unordered_map<std::string, Cell> cell_dictionary = alpha.get_cell_dictionary();
    std::cout << "\t" << SpreadsheetController::full_send(cell_dictionary) << std::endl;

    std::cout << "Test 11 finished" << std::endl;

}

/**
 * Test making a normal string edit
 */
void test12()
{
    std::cout << "Test 12: Test for correct string to be printed on normal edit" << std::endl;
    std::vector<std::string> dependencies{"A1", "B3"};
    json message;
    json j_vec(dependencies);
    message["type"] = "edit";
    message["cell"] = "A2";
    message["value"] = "=2*A1+1+B3";
    message["dependencies"] = j_vec;

    std::cout << "\t Hitting handle edit message" << std::endl;
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    bool valid = SpreadsheetController::handle_edit_message(message, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
    }
    else
    {
        std::unordered_map<std::string, Cell> cells = sm->get_cell_dictionary();
        std::cout << "\t" << SpreadsheetController::full_send(cells) << std::endl;
        print_success_or_failure(valid);
    }
}


/**
 * Test an integer edit
 */
void test13()
{
    std::cout << "Test 13: Test for correct int to be printed on normal edit" << std::endl;
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    std::vector<std::string> dependencies;
    json message;
    json j_vec(dependencies);
    message["type"] = "edit";
    message["cell"] = "A2";
    message["value"] = 5;
    message["dependencies"] = j_vec;
    bool valid = SpreadsheetController::handle_edit_message(message, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
    }
    std::unordered_map<std::string, Cell> cells = sm->get_cell_dictionary();
    std::cout << "\t" << SpreadsheetController::full_send(cells) << std::endl;
    print_success_or_failure(valid);
    std::cout << "Test 13 finished " << std::endl <<std::endl;
}


/**
 * Test an integer edit
 */
void test14()
{
    std::cout << "Test 14: Test for correct double to be printed on normal edit" << std::endl;
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    std::vector<std::string> dependencies;
    json message;
    json j_vec(dependencies);
    message["type"] = "edit";
    message["cell"] = "A2";
    message["value"] = 5.12345;
    message["dependencies"] = j_vec;
    bool valid = SpreadsheetController::handle_edit_message(message, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
    }
    std::unordered_map<std::string, Cell> cells = sm->get_cell_dictionary();
    std::cout << "\t" << SpreadsheetController::full_send(cells) << std::endl;
    print_success_or_failure(valid);
    std::cout << "Test 14 finished " << std::endl <<std::endl;

}


/**
 * Test global stack working for one edit on cell
 */
void test15()
{
    std::cout << "Test 15: Test for correct values to be pushed and popped of global stack" << std::endl;
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>("test", true);
    std::vector<std::string> dependencies;
    json message;
    json j_vec(dependencies);
    message["type"] = "edit";
    message["cell"] = "A2";
    message["value"] = 5.12345;
    message["dependencies"] = j_vec;
    bool valid = SpreadsheetController::handle_edit_message(message, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
    }

    json message1;
    std::vector<std::string> dependencies1{"A2"};
    json j_vec1(dependencies1);
    message1["type"] = "edit";
    message1["cell"] = "A3";
    message1["value"] = "=A2+1";
    message1["dependencies"] = j_vec1;
    valid = SpreadsheetController::handle_edit_message(message1, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
        return;
    }

    json message2;
    std::vector<std::string> dependencies2{"A3"};
    json j_vec2(dependencies2);
    message2["type"] = "edit";
    message2["cell"] = "A4";
    message2["value"] = "=A3+1";
    message2["dependencies"] = j_vec2;
    valid = SpreadsheetController::handle_edit_message(message2, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
        return;
    }

    json message3;
    std::vector<std::string> dependencies3{"A2"};
    json j_vec3(dependencies3);
    message3["type"] = "undo";
    valid = SpreadsheetController::handle_edit_message(message3, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
        return;
    }
    std::unordered_map<std::string, Cell> cells = sm->get_cell_dictionary();
    std::cout << "\t" << SpreadsheetController::full_send(cells) << std::endl;

    std::cout << "calling handle edit" << std::endl;
    valid = SpreadsheetController::handle_edit_message(message3, sm);
    if (!valid)
    {
        print_success_or_failure(valid);
        return;
    }
    std::cout << "called handle edit" << std::endl;
    std::unordered_map<std::string, Cell> cells1 = sm->get_cell_dictionary();
    std::cout << "calling full send" << std::endl;
    std::cout << "\t" << SpreadsheetController::full_send(cells1) << std::endl;
    print_success_or_failure(valid);
    std::cout << "Test 15 finished " << std::endl <<std::endl;   
}



void print_success_or_failure(bool success)
{
    if (success)
    {
        std::cout << "\t Test Succeeded!" << std::endl;
    }
    else
    {
        std::cout << "\t Test Failed!" << std::endl;
    }
}