#ifndef USERMODEL_H
#define USERMODEL_H

#include <string>
class UserModel
{
  public:
    UserModel(std::string name, std::string password);

    void set_name(std::string name);
    std::string get_name();

    void set_password(std::string password);
    std::string get_password();
  private:
    std::string name;
    std::string password;
};

#endif