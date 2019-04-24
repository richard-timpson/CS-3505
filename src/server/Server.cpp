#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "./Server.h"
#include "ClientConnection.h"
#include "../models/CircularException.h"
#include "../controllers/SpreadsheetController.h"

/********************************************
 * Server class
 * ******************************************/

Server::Server(boost::asio::io_context &context, const tcp::endpoint &endpoint)
    : acceptor_(context, endpoint)
{
}


void Server::accept_clients()
{
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            std::shared_ptr<ClientConnection> connection = std::make_shared<ClientConnection>(std::move(socket), this);
            add_client_to_list(connection);
            std::cout << "Accepted connection from client" << std::endl;
            send_spreadsheet_list_to_client(connection);
        }
        else
        {
            std::cout << ec.message() << std::endl;
            accept_clients();
        }
        accept_clients();
    });
}


void Server::send_spreadsheet_list_to_client(std::shared_ptr<ClientConnection> connection)
{
    // char message[256] ="Sending list of spreadsheets to client\n";
    std::string message = SpreadsheetController::get_list_of_spreadsheets(this->get_active_spreadsheets());
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_spreadsheet_selection(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                    connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                    connection->socket_.close();
                    this->remove_client_from_list(connection);
                }
            });
}

void Server::accept_spreadsheet_selection(std::shared_ptr<ClientConnection> connection)
{
    std::cout << "trying to accept spreadsheet selection " << std::endl;
    boost::asio::async_read_until(connection->socket_, connection->buff, "\n\n", 
        [connection, this](boost::system::error_code ec, std::size_t size){
            std::cout << "async read handler called" << std::endl;
            if (!ec)
            {
                std::istream istrm(&connection->buff);
                std::string message;
                std::getline(istrm, message);
                connection->buff.consume(size);
                std::cout << "message is " << message << std::endl;
                std::string error_message;
                json json_message = json::parse(message);
                // Boolean for admin member to differentiate from client
                bool admin_member = SpreadsheetController::validate_admin(json_message, error_message);
                // If admin gets seperated from clients
                if(admin_member)
                {
                    Server::refresh_admin(connection);
                }
                // Regular clients
                else
                {
                    bool valid_user = validate_user(json_message);
                    if (!valid_user)
                    {
                        send_type_1_error(connection);
                        return;
                    }
                    UserModel user = choose_user(json_message);
                    std::shared_ptr<SpreadsheetModel> sm = choose_spreadsheet(json_message, user);
                    if (sm == nullptr)
                    {
                        send_type_1_error(connection);
                        return;
                    }
                    connection->set_name(sm->get_name());
                    connection->set_user_name(json_message["username"]);
                    send_full_spreadsheet(connection, sm);
                }
            }
            else
            {
                std::cout << "Error reading spreadsheet selection " << std::endl;
                connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                connection->socket_.close();
                this->remove_client_from_list(connection);
            }
            
        });
}


void Server::send_full_spreadsheet(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm)
{
    std::unordered_map<std::string, Cell> cell_dictionary = sm->get_cell_dictionary();
    std::string message = SpreadsheetController::full_send(cell_dictionary);
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [sm, message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_edit(connection, sm);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                    connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                    connection->socket_.close();
                    this->remove_client_from_list(connection);
                    // this->save_file_if_needed(sm);
                }
            });
}

void Server::accept_edit(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm)
{
    std::cout << "trying to accept edit" << std::endl;
    boost::asio::async_read_until(connection->socket_, connection->buff, "\n\n", 
        [connection, this, sm](boost::system::error_code ec, std::size_t size){
            std::cout << "async read handler called" << std::endl;
            if (!ec)
            {
                // get the message from the client
                // buff.commit(size);
                std::istream istrm(&connection->buff);
                std::string message;
                std::getline(istrm, message);
                // while (istrm >> std::noskipws >> message)
                istrm >> message;
                connection->buff.consume(size);
                std::cout << "message is " << message << std::endl;
                std::string error_message;
                try
                {
                    json json_message = json::parse(message);
                    std::cout << "successfully parsed message" << std::endl;
                    SpreadsheetController::handle_edit_message(json_message, sm);
                    send_full_spreadsheet_to_clients(sm);
                }
                catch (json::parse_error &e)
                {
                    std::cout << e.what() << std::endl;
                    accept_edit(connection, sm);
                }
                catch (const CircularException &e)
                {
                    std::cout << e.what() << std::endl;
                    std::string cell(e.what());
                    send_type_2_error(connection, sm, cell);
                }
                // parse the message the correct way, edit the model, write back the edit, and then read again. 
            }
            else
            {
                std::cout << "Error reading spreadsheet edit: " << ec.message() << std::endl;
                connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                connection->socket_.close();
                this->remove_client_from_list(connection);
                // this->save_file_if_needed(sm);
            }
            
        });
}

void Server::send_full_spreadsheet_to_clients(std::shared_ptr<SpreadsheetModel> sm)
{
    std::unordered_map<std::string, Cell> cell_dictionary = sm->get_cell_dictionary();
    std::string message = SpreadsheetController::full_send(cell_dictionary);
    message += "\n\n";
    for (std::shared_ptr<ClientConnection> connection: this->connections)
    {
        if (connection->get_name() == sm->get_name())
        {
            boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
                    [sm, message, connection, this](boost::system::error_code ec, std::size_t){
                        if (!ec)
                        {
                            std::cout << "writing message " << message << std::endl;
                            accept_edit(connection, sm);
                        }
                        else
                        {
                            std::cout << "Error sending message " << ec.message() << std::endl;
                            connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                            connection->socket_.close();
                            this->remove_client_from_list(connection);
                        }
                    });
        }
    }
}

void Server::send_type_1_error(std::shared_ptr<ClientConnection> connection)
{
    std::string message = SpreadsheetController::create_type_1_error();
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_spreadsheet_selection(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                    connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                    connection->socket_.close();
                    this->remove_client_from_list(connection);
                }
            });
}

void Server::send_type_2_error(std::shared_ptr<ClientConnection> connection, std::shared_ptr<SpreadsheetModel> sm, std::string cell_name)
{
    std::string message = SpreadsheetController::create_type_2_error(cell_name);
    message += "\n\n";
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, sm, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    accept_edit(connection, sm);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                    connection->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                    connection->socket_.close();
                    this->remove_client_from_list(connection);
                    // this->save_file_if_needed(sm);
                }
            });
}
void Server::refresh_admin(std::shared_ptr<ClientConnection> connection)
{

    std::string message = SpreadsheetController::get_list_of_spreadsheets(spreadsheets);
    message += "\n\n";
    //Get the list of users and add to message
    message += SpreadsheetController::get_list_of_users(this->users);
    message += "\n\n";
    json activeSpreadsheet;
    activeSpreadsheet["type"] = "activeSpreadsheets";
    activeSpreadsheet["activeSpreadsheet"] = "ClearBoy";
    message+= activeSpreadsheet.dump();
    //Get active Spreadsheets(if any)
   // int temp=0;
    for (std::shared_ptr<SpreadsheetModel> ss : spreadsheets)
    {
        if(ss->get_users().empty())
        {
            continue;
        }
        json users_json;
        users_json["type"] = "activeUser";
        users_json["spreadsheet"] == ss->get_name();
        users_json["users"] = {};

        for (std::shared_ptr<ClientConnection> connection: this->connections)
        {
            if(connection->get_name() == ss->get_name())
            {
                users_json["users"].push_back(connection->get_user_name());
            }

        }
        message+= users_json.dump();
    }
    //Send message to client
    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    //Debug statment for proper message sent
                    std::cout << "writing message to admin: " << message << std::endl;
                    admin_parser_operations(connection);//Continue loop
                }
                else
                {
                    //Debug to show what error occured
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });


}

/**
 * This method adds a user to the txt file. If the user already exists, remove them and 
 * readd them under the same name and given password
 * 
 * Parameters:string add_user_name, string add_user_pass
 * */
void Server::admin_add_user(std::string add_user_name, std::string add_user_pass)
    { 
        bool user_exists = false;
        
        for(UserModel now : this->users)
        {
            if(now.name == add_user_name){
            
               now.password = add_user_pass;
               break;
            }
        }


        
    }

/**
 * This Method goes through the list of users and tries to delete the specified username
 * 
 * Parameters: String User to Delete
 * Returns: Nothing
 * */
void Server::admin_delete_user(std::string del_user)
    {
       for(UserModel now : users)
       {
           if(now.get_name()==del_user)
           {
               users.erase(now);
               break;
           }
       }

       for(std::shared_ptr<ClientConnection> now: connections)
        {
            if(now->get_user_name() == del_user)
            {
                now->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                now->socket_.close();
                connections.erase(now);
                break;
            }
        }


    }
/**
 * This function searches the current list of 
 * spreadsheets and if the specified spreadsheet 
 * doesn't exist then adds new spreadsheet. 
 * 
 * parameters: json string (with spreadsheet name)
 * return: void (nothing)
 */
void Server::admin_add_spreadsheet(json json_message)
{
    std::string spreadsheetName=json_message["name"];
    for(std::shared_ptr<SpreadsheetModel> now: spreadsheets)
    {
        if(now->get_name()==spreadsheetName)
        {
            return;
        }
    }
    std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>(spreadsheetName, false);
    this->spreadsheets.insert(sm);

}

/**
 * This function checks if the spreadsheet is 
 * contained in storage and then if the spreadsheet 
 * is there it will send it to a helper function to 
 * delete it and if the spreadsheet isn't there it
 *  won't do anything becuase there is nothing to delete.
 */
void Server::admin_delete_spreadsheet(json json_message)
    {
        std::string name_spreadsheet;
    name_spreadsheet = json_message["name"];
    bool exists=false;
    std::shared_ptr<SpreadsheetModel> toRemove;
    
    for (std::shared_ptr<SpreadsheetModel> sm : spreadsheets)
    {
        if(sm->get_name() == name_spreadsheet)
        {
            
            toRemove = sm;
            exists = true;
            break;
        }
    }

    if(exists)
    {
        std::set<std::shared_ptr<UserModel>> toLoop= toRemove->get_users();
        std::set<std::shared_ptr<ClientConnection>> toDelete;
            for(std::shared_ptr<UserModel>  name: toLoop)
            {
                for(std::shared_ptr<ClientConnection> now: connections)
                {
                    if(now->get_user_name() == name->get_name())
                    {
                        toDelete.insert(now);
                    }
                }

            }
            for(std::shared_ptr<ClientConnection> now: toDelete)
            {
                now->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                now->socket_.close();
                connections.erase(now);
            }
        spreadsheets.erase(toRemove);
    }
    }

/**
 * This function shuts down the server
 * and closes all spreadsheets and 
 * disconnects all clients
 */    
void Server::admin_off()
    {

        connections.clear();
       // SpreadsheetController::mu_lock_user_list.lock();
       // SpreadsheetController::mu_lock_spreadsheet_list.lock();
       // SpreadsheetController::mu_lock_file_user_txt.lock();
       // SpreadsheetController::mu_lock_file_spreadsheet_txt.lock();
        exit(0);
    }

/**
 *  This is a parser that the admin will be used 
 * to execute the operations of adding/deleting of 
 * users and spreadsheets while also having a master 
 * command of off which will turn of a server.
 * param = shared_ptr<ClientConnection> connection
 * return = void
 */
void Server::admin_parser_operations(std::shared_ptr<ClientConnection> connection)
   {
       // Using the boost library, we reading in the sent message from the buffer.
       boost::asio::async_read_until(connection->socket_, connection->buff, "\n\n", 
        [connection, this](boost::system::error_code ec, std::size_t size){
            //Debug statement making sure the correct handler is called
            std::cout << "async read handler called" << std::endl;
                // get the message from the client
                std::istream istrm(&connection->buff);
                // generating string for message
                std::string message;
                // getting the message into the string
                std::getline(istrm, message);
                //remove used message
                connection->buff.consume(size);
                // confirming that it is a message from admin (Debug help)
                std::cout << "admin message is " << message << std::endl;
                // message for any error run into
                std::string error_message;
                // making sure the message isn't blank
                if(message != "")
                {
                    // parsing the message into JSON object
                     json json_message = json::parse(message);
                     // Open spreadsheet command is being executed
                    // if(json_message.value("type", " ") != "open")
                    //     {
                    //         refresh_admin(connection);
                    //     }
                        // Add user command is being executed
                    if (json_message["Operation"]== "AU")
                        {
                            admin_add_user(json_message["name"], json_message["password"]);
                            refresh_admin(connection);
                        }
                        // Delete user command is being executed
                    else if (json_message["Operation"]=="DU")
                        {
                            admin_delete_user(json_message["name"]);
                            refresh_admin(connection);
                        }
                        // Add spreadsheet is being executed
                    else if (json_message["Operation"]=="AS")
                        {
                            admin_add_spreadsheet(json_message);
                            refresh_admin(connection);
                        }
                        // Delete spreadsheet is being executed
                    else if (json_message["Operation"]=="DS")
                        {
                            admin_delete_spreadsheet(json_message);
                            refresh_admin(connection);
                        }
                        // OFF command is being executed
                    else if (json_message["Operation"]=="OFF")
                        {
                            admin_off();
                            refresh_admin(connection);
                        }
                    else
                        {
                            //operation doesn't exist
                            refresh_admin(connection);
                        }
                }
                // No proper command was given so refreshed
                else
                {
                    std::cout<< "This is not a proper message admin: " << message <<std::endl;
                    refresh_admin(connection);
                }
            
        });
   }


void Server::load_data()
{
    // get all of the users from users.txt and load them into users. 
    std::ifstream user_file("../../data/users.txt");
    std::string line;

    while (std::getline(user_file, line))
    {
        std::string name;
        std::string password;
        std::vector<std::string> info = SpreadsheetController::split(line, " ");
        std::vector<std::string>::iterator it = info.begin();
        name = *it;
        it++;
        password = *it;
        UserModel user;
        user.name = name;
        user.password = password;
        users.push_back(user);
    }
    user_file.close();

    // get all of the users from users.txt and load them into users. 
    std::ifstream spreadsheet_file("../../data/spreadsheets.txt");
    std::string name;
    std::set<std::string> spreadsheet_names;

    while (std::getline(spreadsheet_file, name))
    {
        spreadsheet_names.insert(name);
    }
    spreadsheet_file.close();

    for (std::string name : spreadsheet_names)
    {
        std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>(name, false);
        this->spreadsheets.insert(sm);
    }
}

void Server::save_data()
{
    // if the file does not exist, there is an issue
    // if (boost::filesystem::exists("../../data/users.txt"))
    {
        // remove the users file, and then create it again
        // std::remove("../../data/users.txt");
        std::ofstream write_file;
        write_file.open("../../data/users.txt");

        // loop through all of the users, and write them to the file
        for (UserModel user : this->users)
        {
            std::string user_string = user.name + " " + user.password;
            write_file << user_string << std::endl;
        }
        write_file.close();

        // remove from the spreadsheet file, and create again
        // std::remove("../../data/spreadsheets.txt");
        write_file.open("../../data/spreadsheets.txt");
        for (std::shared_ptr<SpreadsheetModel> sm : this->spreadsheets)
        {
            std::string name = sm->get_name();
            sm->write_json_ss_file();
            write_file << name << std::endl;
        }
        write_file.close();
    }
}

bool Server::check_if_spreadsheet_in_list(json message, std::shared_ptr<SpreadsheetModel> &sm)
{
    if (!SpreadsheetController::validate_login_message(message)) return false;
    bool found;
    for (std::shared_ptr<SpreadsheetModel> ss : this->spreadsheets)
    {
        if (message["name"] == ss->get_name())
        {
            sm = ss;
            return true;
        }
    }
    return false;
}

bool Server::validate_user(json message)
{
    // get the name and password from json message
    std::string name = message.value("username", " ");
    std::string password = message.value("password", " ");
    bool found = false;
    // loop through all the users and check if the name and password match. 
    // for (std::set<UserModel>::iterator user = this->users.begin(); user != users.end(); user++)
    for (UserModel user : this->users)
    {
        if (name == user.name && password != user.password)
        {
            return false;
        }
    }
    return true;
}

UserModel Server::choose_user(json & message)
{
    // get the name and password from json message
    std::string name = message.value("username", " ");
    std::string password = message.value("password", " ");
    bool found;
    for (UserModel user : this->users)
    {
        if (name == user.name && password == user.password)
        {
            found = true;
            return user;
        }
    }
    // if we haven't found a user, add one to the list
    if (!found)
    {
        UserModel user;
        user.name = name;
        user.password = password;
        this->users.push_back(user);
        return user;
    }
}


std::shared_ptr<SpreadsheetModel> Server::choose_spreadsheet(json & json_message, UserModel user)
{
    // initialize null spreadsheet
    std::shared_ptr<SpreadsheetModel> sm(nullptr);
    // if the message is invalid, return the null pointer
    if (!SpreadsheetController::validate_login_message(json_message)) return sm;
    // loop through list of spreadsheet, and check if the spreadsheet selection already exists
    for (std::shared_ptr<SpreadsheetModel> ss : this->spreadsheets)
    {
        // if it does, return that spreadsheet
        if (json_message["name"] == ss->get_name())
        {
            sm = ss;
            sm->add_user_to_spreadsheet(user.name);
            return sm;
        }
    }
    // if it doesn't, make new sheet, and return that. 
    std::string spreadsheet_name = json_message.value("name", "-1");
    sm = std::make_shared<SpreadsheetModel>(spreadsheet_name, true);
    this->add_spreadsheet_to_list(sm);
    sm->add_user_to_spreadsheet(user.name);
    return sm;
}
void Server::add_client_to_list(std::shared_ptr<ClientConnection> connection)
{
    connections.insert(connection);
}

void Server::remove_client_from_list(std::shared_ptr<ClientConnection> connection)
{
    connections.erase(connection);
}

void Server::remove_sm_from_list(std::shared_ptr<SpreadsheetModel> sm)
{
    spreadsheets.erase(sm);
}

void Server::add_spreadsheet_to_list(std::shared_ptr<SpreadsheetModel> ss)
{
    spreadsheets.insert(ss);
}


std::set<std::shared_ptr<SpreadsheetModel>> Server::get_active_spreadsheets()
{
    return spreadsheets;
}

/***************************************
 * ClientConnection class
 * *************************************/

ClientConnection::ClientConnection(tcp::socket socket, Server* server)
    : socket_(std::move(socket))
{
    server_ = server;
}


