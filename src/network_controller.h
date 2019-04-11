

#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H


#include <string>
#include<iostream>
#include "../libs/json.hpp"
using json = nlohmann::json;

namespace Network
{
   class network_controller
   {
      private:

      public:
      void recieve_message(json input);
      json send_message(std::string input);


};
}





#endif

