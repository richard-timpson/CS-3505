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
    std::list <std::string> saved_users;
    std::list<std::string>::iterator it = saved_users.begin();


    int index;
    int it_index;

    for (it = saved_users.begin; it != saved_users.end(); it++)
    {

    }
    for(index = 0; index < saved_users.size(); index++)
    {
        if(alpha != beta)
        {

        }
    }
 
}