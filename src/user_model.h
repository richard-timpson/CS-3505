/*
 * The user model class is for dealing with the login and
 * user part of the connection process. This class will verify,
 * create, and save user logins when they attempt to open a sheet.
 *
 *
 *
 *
 *
 */


#ifndef USERMODEL_H
#define USERMODEL_H

#include <string>
#include "../libs/json.hpp"

namespace Server
{

  class user
  {
  public:

    user(nlohmann::json input);
    std::string get_username();
    std::string get_password();
    ~user();

  private:

    std::string username;
    std::string password;
  };
}


#endif
