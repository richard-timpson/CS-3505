// Here




#include "UserModel.h"
#include <string>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

Server::user::user(json input)
{
  this->username = input.value("user", "joke");
  std::cout << "username: " << this->username << std::endl;

  this->password = input.value("password", "kase");
  std::cout << "password: " << this->password << std::endl;
}
Server::user::~user()
{
  this->username = "";
  this->password = "";
}
