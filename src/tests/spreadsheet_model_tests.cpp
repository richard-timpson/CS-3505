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
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
}

/**
 * Test new cell with no dependents
 */
void test1()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 1: New Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "Reach", dependents);
    std::string contents = alpha.get_cell_contents("C3");
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
    alpha.set_cell_contents("B6", "Reach", dependents);

    std::vector<std::string>::iterator dependents_ = alpha.get_direct_dependents("B6").begin();
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
    alpha.set_cell_contents("A7", "Reach", dependents);
    alpha.set_cell_contents("A7", "Fargo", dependents);
    
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
    alpha.set_cell_contents("A9", "A9 test", a9_dependents );
    alpha.set_cell_contents("A8", "A8 test", a8_dependents );
    std::vector<std::string> dependents;
    dependents.push_back("A9");
    dependents.push_back("A8");
    alpha.set_cell_contents("A7", "Reach", dependents);
    std::vector<std::string> a1_dependents;
    std::vector<std::string> a2_dependents;
    alpha.set_cell_contents("A1", "A1 test", a1_dependents );
    alpha.set_cell_contents("A2", "A2 test", a2_dependents );
    std::vector<std::string> new_dependents;
    new_dependents.push_back("A1");
    new_dependents.push_back("A2");
    alpha.set_cell_contents("A7", "Fargo", new_dependents);

    std::vector<std::string>::iterator dependents_ = alpha.get_direct_dependents("A7").begin();
    bool success1 = *dependents_ == "A1";
    dependents_++;
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
    alpha.set_cell_contents("A1", "5", a1_dependents );
    alpha.set_cell_contents("A2", "A1 + 5", a2_dependents );
    alpha.set_cell_contents("A3", "A2 + 5", a3_dependents );
    alpha.set_cell_contents("A4", "A3 + 5", a4_dependents );
    alpha.set_cell_contents("A5", "A4 + 5", a5_dependents );

    std::vector<std::string> new_a1_dependents{"A4"};
    bool success;
    try
    {
        alpha.set_cell_contents("A1", "A4", new_a1_dependents);
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