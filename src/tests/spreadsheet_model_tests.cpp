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
    alpha.set_cell_contents("halo", "Reach", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("halo") << std::endl;
    std::cout << "Test 1 finished " << std::endl;

}

void test2()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 1: New Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("halo", "Reach", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("halo") << std::endl;
    std::cout << "Test 1 finished " << std::endl;

}

void test3()
{
    SpreadsheetModel alpha("Alpha", true);
    std::cout << "Test 1: New Cell with no dependents" << std::endl;
    std::vector<std::string> dependents;
    alpha.set_cell_contents("halo", "Reach", dependents);
    

    std::cout << "\t" << alpha.get_cell_contents("halo") << std::endl;
    std::cout << "Test 1 finished " << std::endl;

}
