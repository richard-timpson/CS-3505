#include "../models/SpreadsheetModel.h"
#include <string>
#include <iostream>
#include "../models/CircularException.h"

void print_success_or_failure(bool success);
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test9_1();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();
void test16();

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test9_1();
    test10();
    test11();
}

/**
 * Test new cell with no dependents
 */
void test1()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 1: New Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "Reach", dependents, "string");
    std::cout << "Test 1: Past set" << std::endl;
    std::string contents = alpha.get_cell_contents("C3");
    std::cout << "Test 1: Past get" << std::endl;
    bool success = (contents == "Reach");
    print_success_or_failure(success);
    std::cout << "Test 1 finished " << std::endl << std::endl;

}

/**
 * Test new cell with two dependents
 */
void test2()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 2: New Cell with two dependents" << std::endl;
    std::vector<std::string> dependents;
    dependents.push_back("A1");
    dependents.push_back("A2");
    alpha.set_cell_contents("B6", "Reach", dependents, "string");

    std::vector<std::string> vector_dep =alpha.get_cell_direct_dependents("B6");
    std::vector<std::string>::iterator dependents_ = vector_dep.begin();
    bool success1 = *dependents_ == "A1";
    dependents_++;
    bool success2 = *dependents_ == "A2";
    bool success3 = alpha.get_cell_contents("B6") == "Reach";
    if (success1 && success2 && success3) print_success_or_failure(true);
    else print_success_or_failure(false);
    std::cout << "Test 2 finished " << std::endl << std::endl;
}


/**
 * Test set_cell_contents on exsiting cell with no dependents
 */
void test3()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 3: Existing Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("A7", "Reach", dependents, "string");
    alpha.set_cell_contents("A7", "Fargo", dependents, "string");
    
    bool success = alpha.get_cell_contents("A7") == "Fargo";
    print_success_or_failure(success);

    std::cout << "Test 3 finished " << std::endl << std::endl;

}


/**
 * test set_cell_contents on existing cell with two dependents
 */
void test4()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 4: Existing Cell with two dependents" << std::endl;
    std::vector<std::string> a9_dependents;
    std::vector<std::string> a8_dependents;
    alpha.set_cell_contents("A9", "A9 test", a9_dependents, "string" );
    alpha.set_cell_contents("A8", "A8 test", a8_dependents, "string" );
    std::vector<std::string> dependents;
    dependents.push_back("A9");
    dependents.push_back("A8");
    alpha.set_cell_contents("A7", "A7 test", dependents, "string");
    std::vector<std::string> a1_dependents;
    std::vector<std::string> a2_dependents;
    alpha.set_cell_contents("A1", "A1 test", a1_dependents, "string" );
    alpha.set_cell_contents("A2", "A2 test", a2_dependents, "string" );
    std::vector<std::string> new_dependents;
    new_dependents.push_back("A1");
    new_dependents.push_back("A2");
    alpha.set_cell_contents("A7", "Fargo", new_dependents, "string");

    std::vector<std::string> vector_dep = alpha.get_cell_direct_dependents("A7");
    std::vector<std::string>::iterator dependents_ = vector_dep.begin();

    std::cout << alpha.get_cell_direct_dependents("A7").front()<< std::endl;
    std::cout << *dependents_ << std::endl;
    bool success1 = *dependents_ == "A1";
    dependents_++;
    std::cout << *dependents_ << std::endl;
    bool success2 = *dependents_ == "A2";
    bool success3 = alpha.get_cell_contents("A7") == "Fargo";
    if (success1 && success2 && success3) print_success_or_failure(true);
    else print_success_or_failure(false);

    std::cout << "Test 4 finished " << std::endl << std::endl;

}

/**
 * Testing for circular dependency check on set_cell_contents
 */
void test5()
{
    // a1

    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 5: Test for circular dependency check" << std::endl;
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

    std::vector<std::string> new_a1_dependents{"A4"};
    bool success;
    try
    {
        alpha.set_cell_contents("A1", "=A4+1", new_a1_dependents, "string");
        success = false;
    }
    catch(const CircularException& e)
    {
        success = true;
        // std::cerr << e.what() << '\n';
    }
    print_success_or_failure(success);
    std::cout << "Test 5 Finished " << std::endl << std::endl;

}




/**
 * Test if the type is saved correctly, INT
 */
void test6()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 6: type is saved correctly, INT" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "5", dependents, "int");
    std::string type = alpha.get_cell_type("C3");
    bool success = (type == "int");
    print_success_or_failure(success);
    std::cout << "Test 6 finished " << std::endl << std::endl;

}

/**
 * Test if the type is saved correctly, Double
 */
void test7()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 7: type is saved correctly, DOUBLE" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "4.39", dependents, "double");
    std::string type = alpha.get_cell_type("C3");
    bool success = (type == "double");
    print_success_or_failure(success);
    std::cout << "Test 7 finished " << std::endl << std::endl;

}

/**
 * Test if the type is saved correctly, String
 */
void test8()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 8: type is saved correctly, STRING" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "=A1+5", dependents, "string");
    std::string type = alpha.get_cell_type("C3");
    bool success = (type == "string");
    print_success_or_failure(success);
    std::cout << "Test 8 finished " << std::endl << std::endl;

}

/**
 *  Test if the spreadsheet is written correctly.
 */
void test9()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 9: spreadsheet is saved correctly" << std::endl;
    std::vector<std::string> dependents;
    std::vector<std::string> dependents1{"A1"};
    std::vector<std::string> dependents2{"A2"};
    std::vector<std::string> dependents3{"A3"};
    alpha.do_edit("A1", "=5", dependents, "string");
    alpha.do_edit("A2", "=10", dependents, "string");
    alpha.do_edit("A3", "=15", dependents, "string");
    std::cout << "Got past making vectors   ";
    alpha.do_edit("C3", "=A1+1", dependents1, "string");
    std::cout << "Got past making A1   ";
    alpha.do_edit("C3", "=A2+2", dependents2, "string");
    std::cout << "Got past making A2   ";
    alpha.do_edit("C3", "=A3+3", dependents3, "string");

    alpha.write_json_ss_file();

    std::cout << "Test 9 finished " << std::endl << std::endl;

}

/**
 *  Test if the spreadsheet is written correctly.
 */
void test9_1()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 9_1: spreadsheet is loaded correctly" << std::endl;

    std::vector<std::string> dependents;
    std::vector<std::string> dependents1{"A1"};

    std::cout << "Got past making vectors   ";
    alpha.do_edit("C3", "=A1+1", dependents1, "string");
    alpha.do_edit("C8", "=A1+1", dependents1, "string");

    alpha.write_json_ss_file();
    alpha.open_json_ss_file();

    std::string c3_contents = alpha.get_cell_contents("C3");
    std::string c8_contents = alpha.get_cell_contents("C8");
    std::cout << "c3 contents " << c3_contents << std::endl;
    std::cout << "c8 contents " << c8_contents << std::endl;

    bool success = c3_contents == "=A1+1" && c8_contents == "=A1+1";
    print_success_or_failure(success);

    std::cout << "Test 9_1 finished " << std::endl << std::endl;

}

/**
 * Test if personal history is working
 */
void test10()
{
    std::cout << "Test 10: personal history " << std::endl << std::endl;
    SpreadsheetModel alpha("Alpha", true);
    std::vector<std::string>dependents;
    alpha.do_edit("A1", "5", dependents, "int");
    alpha.do_edit("A1", "10", dependents, "int");
    alpha.do_edit("A1", "20", dependents, "int");
    CellEdit edit = alpha.top_cell_personal_history("A1");
    bool success = edit.contents == "20";
    print_success_or_failure(success);
    alpha.pop_cell_personal_history("A1");
    edit = alpha.top_cell_personal_history("A1");
    success = edit.contents == "10";
    print_success_or_failure(success);
    std::cout << "Test 10 finished " << std::endl << std::endl;

}

/**
 * Test if personal history dependents is working
 */
void test11()
{
    /*std::cout << "Test 11: personal history dependents" << std::endl << std::endl;
    SpreadsheetModel alpha("Alpha", true);
    std::vector<std::string>dependents;
    //dependents.push_back("C1");
    alpha.do_edit("A1", "5 + C1", dependents, "int");
    //dependents.pop_back();
    //dependents.push_back("C2");
    alpha.do_edit("A1", "10 + C2", dependents, "int");
    //dependents.pop_back();
    //dependents.push_back("C2");
    alpha.do_edit("A1", "20 + C3", dependents, "int");
    CellEdit edit = alpha.top_cell_personal_history("A1");
    bool success = edit.direct_dependents.size() == 1;
    print_success_or_failure(success);
    alpha.pop_cell_personal_history("A1");
    edit = alpha.top_cell_personal_history("A1");
    success = edit.direct_dependents.size() == 1;
    print_success_or_failure(success);
    std::cout << "Test 11 finished " << std::endl << std::endl;
    */

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