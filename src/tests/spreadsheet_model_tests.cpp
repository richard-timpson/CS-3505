//HI



#include "../models/SpreadsheetModel.h"
#include <string>
#include <iostream>


void test1();
void test2();
void test3();

int main()
{
    

    test1();
    test2();
    test3();
}

void test1()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 1: New Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("C3", "Reach", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("halo") << std::endl;
    std::cout << "Test 1 finished " << std::endl;

}

void test2()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 2: New Cell with two dependents" << std::endl;
    std::vector<std::string> dependents;
    dependents.push_back("A1");
    dependents.push_back("A2");
    alpha.set_cell_contents("B6", "Reach", dependents);
    

    std::cout << "\t" << "Contents:  " << alpha.get_cell_contents("B6") << std::endl;
    std::cout << "Test 2 finished " << std::endl;

}

void test3()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 3: Existing Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("A7", "Reach", dependents);
    alpha.set_cell_contents("A7", "Fargo", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("A7") << std::endl;
    std::cout << "Test 3 finished " << std::endl;

}

void test4()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 4: Existing Cell with two dependents" << std::endl;
    std::vector<std::string> dependents;
    dependents.push_back("A9");
    dependents.push_back("A8");
    alpha.set_cell_contents("A7", "Reach", dependents);
    dependents.push_back("A1");
    dependents.push_back("A2");
    alpha.set_cell_contents("A7", "Fargo", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("A7") << std::endl;
    std::cout << "Test 4 finished " << std::endl;

}
