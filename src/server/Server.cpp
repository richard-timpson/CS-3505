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
                    std::shared_ptr<SpreadsheetModel> sm = choose_spreadsheet(json_message);
                    connection->set_name(sm->get_name());
                    connection->set_user_name(json_message["username"]);
                    send_full_spreadsheet(
                        connection, sm);
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
                    this->save_file_if_needed(sm);
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
                this->save_file_if_needed(sm);
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
                    this->save_file_if_needed(sm);
                }
            });
}
void Server::refresh_admin(std::shared_ptr<ClientConnection> connection)
{
    //Get the list of spreadsheets and add to message
    std::set<std::shared_ptr<SpreadsheetModel>> spreadsheets;
    std::string message = SpreadsheetController::get_list_of_spreadsheets(spreadsheets);
    message += "\n\n";
    //Get the list of users and add to message
    message += SpreadsheetController::get_list_of_users();
    message += "\n\n";
    //Get active Spreadsheets(if any)
    int temp=0;
    for (std::shared_ptr<SpreadsheetModel> ss : spreadsheets)
    {
        //Debug comments to make sure loop is entered
        std::cout << "looping throug the spreadsheets at name " << ss->get_name() << std::endl;
        message+= "{\"type\":\"activeUser\", \"spreadsheet\":"+ss->get_name()+",\"users\":[";
        std::cout << "we have active users got em" <<std::endl;
        temp=0;
        //send active users to a spreadsheet
        for (std::shared_ptr<ClientConnection> connection: this->connections)
        {
            //Debug to make sure loop is entered
            std::cout << "looping through the client connections at client " << connection->get_name() << std::endl;
            //If the client uses the spreadsheet, add them to message
            if(connection->get_name()==ss->get_name())
            {
                //Only add commas after the first client found
                if(temp!=0){
                    message+=",";
                }
                temp++;
                message+="\""+connection->get_user_name()+"\"";
            }
        }
        message+="]}\n\n";//Split the messages by two newlines
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
 * This is called to remove a spreadsheet from the list of spreadsheets
 * 
 * Parameters: Json message
 * Return: None
 */
void Server::admin_remove_spreadsheet(json json_message)
{

    std::string name_spreadsheet;
    name_spreadsheet = json_message["name"];
   // SpreadsheetController::mu_lock_file_spreadsheet_txt.lock();
    std::ifstream file("../../data/spreadsheets.txt");
    std::string line;
    std::set<std::string> spreadsheet_names;
    while (std::getline(file, line))
    {
        //If spreadsheet is found: skip it. Otherwise: insert into set
        if(line != name_spreadsheet)
        {
            spreadsheet_names.insert(line);
        }
    }
    //close the file and delete it
    file.close();
    remove("../../data/spreadsheets.txt");
    //recreate the file fresh and add all spreadsheets from the set
    std::ofstream outfile("../../data/spreadsheets.txt");
    for(std::string s : spreadsheet_names)
    {
        outfile << s << std::endl;
    }
    //close the file
    outfile.close();

    //SpreadsheetController::mu_lock_file_spreadsheet_txt.unlock();//Possible unlock for the future

   
}

/**
 * This method adds a user to the txt file. If the user already exists, remove them and 
 * readd them under the same name and given password
 * 
 * Parameters:string add_user_name, string add_user_pass
 * */
void Server::admin_add_user(std::string add_user_name, std::string add_user_pass)
    {
        //SpreadsheetController::mu_lock_file_user_txt.lock();//Possible lock for the future
        //Get and read over file for the user
        std::ifstream file("../../data/users.txt");//******************************TODO: This might change on the server, Check periodically
        std::string line;
        bool already_exists = false;
        while (std::getline(file, line))
        {
            //Split line by comma as username and password shouldn't use commas
            std::vector<std::string> current_line = SpreadsheetController::split(line, ",");
            if(current_line.front() == add_user_name)//If we have found the user
            {
                if(current_line.back() != add_user_pass)//and if the passwords don't match
                {
                    //close the file and delete the user, then jump to next if statment
                    file.close();
                    admin_delete_user(add_user_name);
                    break;
                }
                else
                {
                    //If both are the same, Change already_exists and go to next if
                    already_exists = true;
                    break;
                }
                
            }
        }
        //If the user/password already exists, just return
        if(!already_exists)
        {
            std::ofstream file;
            file.open("../../data/users.txt", std::ios_base::app);//******************************TODO: This might change on the server, Check periodically
            file << add_user_name << "," << add_user_pass <<std::endl;
            file.close();
        }
        //SpreadsheetController::mu_lock_file_user_txt.unlock();//Possible unlock for future use
    }

/**
 * This Method goes through the list of users and tries to delete the specified username
 * 
 * Parameters: String User to Delete
 * Returns: Nothing
 * */
void Server::admin_delete_user(std::string del_user)
    {
        //SpreadsheetController::mu_lock_file_user_txt.lock();//Lock for possible future use
        std::ifstream file("../../data/users.txt");//******************************TODO: This might change on the server, Check periodically
        // changing to iterating through user's list to determine deletion.
        std::string line;
        std::set<std::string> user_names;
        while (std::getline(file, line))
        {
            // split user name from the password with a comma
            std::vector<std::string> current_line = SpreadsheetController::split(line, ",");
            // not the user you are looking for continue otherwise add to set of users
            if(current_line.front() != del_user)
            {
             user_names.insert(line);
            }
        }
        // closes file 
        file.close(); 
        // removes the file
        remove("../../data/users.txt");//******************************TODO: This might change on the server, Check periodically
        // remakes the file
        std::ofstream outfile("../../data/users.txt");//******************************TODO: This might change on the server, Check periodically
        // rewriting the users to the file
        for(std::string u : user_names)
        {
            outfile << u <<std::endl;
        }
        // closes the file
        outfile.close();

        //SpreadsheetController::mu_lock_file_user_txt.unlock();

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
        // checking json message debug
        std::cout<<json_message<<std::endl;
        // reading to file spreadsheet.txt
        std::ifstream file("../../data/spreadsheets.txt");//******************************TODO: This might change on the server, Check periodically
        // created for iterating through the lines of spreadsheets.txt
        std::string line;
        bool already_exists = false;
        while (std::getline(file, line))
            {
                 //If it already exists breaks out of loop.
                if(line == json_message["name"]){
                    std::cout << already_exists <<std::endl;
                    already_exists=true;
                    break;
                }
            }
         // the file is closed
         file.close();
         // If it already exists add it to the list.
        if(!already_exists)
            {
                std::ofstream file;
                std::cout <<"Was not found"<<std::endl;
                std::cout << already_exists <<std::endl;
                file.open("../../data/spreadsheets.txt", std::ios_base::app);//******************************TODO: This might change on the server, Check periodically
                std::string name = json_message["name"];
                file << name <<std::endl;
                file.close();
            }
        
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
        // 
        std::string no_use_spread;
        // checks to see if the spreadsheet is contatined in storage
        bool is_in_storage = SpreadsheetController::check_if_spreadsheet_in_storage(json_message, no_use_spread);
        // if it does exists
        if (is_in_storage)
        {
            // The helper method to remove the spreadsheet will remove it.
            admin_remove_spreadsheet(json_message);
        }
        else
        {
            // do nothing because it doesn't exist 
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
    std::ifstream file("../../data/users.txt");
    std::string line;
    int count = 0;

    while (std::getline(file, line))
    {
        std::string name;
        std::string password;
        std::vector<std::string> info = SpreadsheetController::split(line, " ");
        std::vector<std::string>::iterator it = info.begin();
        name = *it;
        it++;
        password = *it;
        UserModel user(name, password);
        users.insert(user);
    }
    file.close();

    // get all of the users from users.txt and load them into users. 
    std::ifstream file("../../data/spreadsheets.txt");
    std::string name;
    std::set<std::string> spreadsheet_names;
    int count = 0;

    while (std::getline(file, name))
    {
        spreadsheet_names.insert(name);
    }
    file.close();

    for (std::string name : spreadsheet_names)
    {
        std::shared_ptr<SpreadsheetModel> sm = std::make_shared<SpreadsheetModel>(name, false);
        this->spreadsheets.insert(sm);
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

void Server::save_file_if_needed(std::shared_ptr<SpreadsheetModel> sm)
{
    std::unordered_map<std::string, Cell> cell_dictionary = sm->get_cell_dictionary();
    for (std::shared_ptr<ClientConnection> connection: this->connections)
    {
        if (connection->get_name() == sm->get_name())
        {
            return;
        }
    }
    sm->write_json_ss_file();
    sm->write_ss_file_if_needed();
    this->remove_sm_from_list(sm);
}

std::shared_ptr<SpreadsheetModel> Server::choose_spreadsheet(json & json_message)
{
    std::shared_ptr<SpreadsheetModel> sm(nullptr);
    std::string spreadsheet_name = json_message.value("name", "-1");
    bool is_in_list = check_if_spreadsheet_in_list(json_message, sm);
    if (!is_in_list)
    {
        std::string spreadsheet;
        bool is_in_storage = SpreadsheetController::check_if_spreadsheet_in_storage(json_message, spreadsheet);
        if (!is_in_storage)
        {
            // make new spreadsheet
            std::cout << "creating new spreadsheet" << std::endl;
            sm = std::make_shared<SpreadsheetModel>(spreadsheet_name, true);
            this->add_spreadsheet_to_list(sm);
            return sm;
        }
        else
        {
            std::cout << "loading spreadsheet from json file" << std::endl;
            sm = std::make_shared<SpreadsheetModel>(spreadsheet_name, false);
            return sm;
            // load the model from storage 
        }
    }
    else 
    {
        std::cout << "loading spreadsheet from active list" << std::endl;
        return sm;
    }
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


