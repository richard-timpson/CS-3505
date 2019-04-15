/*
 * Functions to recieve and parse Jsons form clients.
 *
 *
 *
 *
 */


#include <string>
#include<iostream>
#include "../../libs/json.hpp"
#include "../models/spreadsheet_model.h"
#include "../models/user_model.h"
#include "network_controller.h"

using json = nlohmann::json;

Server::spreadsheet sheet;

void Network::network_controller::recieve_message(json input)
{
  if (input.value("type", "fff") == "open")
    {
      sheet.validate(input.value("username", "fff"), input.value("password", "fff"));
    }
  else if (input.value("type", "fff") == "edit")
    {
      // Call Server::spreadsheet::edit
    }
  else if (input.value("type", "fff") == "undo")
    {
      // Call Server::spreadsheet::undo
    }
  else if (input.value("type", "fff") == "revert")
    {
      // Call server::spreadsheet::revert
    }

}

json Network::network_controller::send_message(std::string input)
{
  if (input == "Error")
    {
      // Send error Json
    }
  else if (input == "Full Send")
    {
      // Send full send Json
    }
  else
    {
      // Send somesort of error because it wasn't a full send
    }
}

