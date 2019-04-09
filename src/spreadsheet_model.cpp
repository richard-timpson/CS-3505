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
#include "json.hpp"
#include "spreadsheet_model.h"
#include "user_model.h"

bool Server::spreadsheet::validate(std::string alpha, std::string beta)
{
    std::list <std::string> saved_users_list;
    std::list<std::string>::iterator it;


    int index;
    int it_index;

    // Looping through the list of saved users, and checking if the input
    // is an already made user.
    for (it = saved_users_list.begin; it != saved_users_list.end(); it++)
    { 
      // Check if it is the same username.
      if (alpha == *it.get_username())
	{
	  // Check if the password matches, if yes send speadsheet, if not send error.
	  if (beta == it.get_password())
	    {
	      // Send spreadsheet
	    }
	  else
	    {
	      // Send back error
	    }
	  
	}

    }
    //if user does not exist, make new user and save to list.
    
 
}
