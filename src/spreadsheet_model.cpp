/*
 * The spreadsheet model class is for dealing with seeing the users on
 * the spreadsheet part of the connection process. This class will verify,
 * and validate user logins when they attempt to open a spreadsheet and 
 *  are on the spreadsheet.
 *
 */

#include <string>
#include<iterator>
#include<list>
#include<iostream>
#include "../libs/json.hpp"
#include "spreadsheet_model.h"
#include "user_model.h"
#include "network_controller.h"

bool Server::spreadsheet::validate(std::string input_username, std::string input_password)
{
    std::list <user> saved_users_list;
    std::list<user>::iterator it;


    int index;
    int it_index;
    Network::network_controller net_control;

    // Looping through the list of saved users, and checking if the input
    // is an already made user.
    for (it = saved_users_list.begin(); it != saved_users_list.end(); ++it)
    { 
      // Check if it is the same username.
      if (input_username == it->get_username())
	  {
	    // Check if the password matches, if yes send speadsheet, if not send error.
	    if (input_password == it->get_password())
	      {
		net_control.send_message("Full Send");
	      }
	    else
	      {
		net_control.send_message("Error");
	      }
	  
	    }

    }
    //if user does not exist, make new user and save to list.
    return true;
 
}
