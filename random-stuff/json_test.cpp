#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

int main()
{
    json j2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {"answer", {{"everything", 42}}},
        {"list", {1, 0, 2}},
        {"object", {{"currency", "US"}, {"value", 42.99}}}};

    std::cout << j2.dump() << std::endl;
    return 0;
}
