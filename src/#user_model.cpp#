// Here




#include "user_model.h"
#include <string>
#include <iostream>
#include "../libs/json.hpp"
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

std::string Server::user::get_username()
{
  return this->username;
}

std::string Server::user::get_password()
{
  return this->password;
}
