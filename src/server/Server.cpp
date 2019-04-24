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
                
                bool admin_member = SpreadsheetController::validate_admin(json_message, error_message);
                if(admin_member)
                {
                    Server::refresh_admin(connection);
                }
                else
                {
                    bool valid_user = validate_user(json_message);
                    if (!valid_user)
                    {
                        send_type_1_error(connection);
                    }
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
    std::set<std::shared_ptr<SpreadsheetModel>> spreadsheets;
    std::string message = SpreadsheetController::get_list_of_spreadsheets(spreadsheets);
    message += "\n\n";
    message += SpreadsheetController::get_list_of_users();
    message += "\n\n";
    int temp=0;
    for (std::shared_ptr<SpreadsheetModel> ss : spreadsheets)
    {
        // if(ss->get_name()==""){
        //     continue;
        // }
        std::cout << "looping throug the spreadsheets at name " << ss->get_name() << std::endl;
        message+= "{\"type\":\"activeUser\", \"spreadsheet\":"+ss->get_name()+",\"users\":[";
        std::cout << "we have active users got em" <<std::endl;
        temp=0;
        for (std::shared_ptr<ClientConnection> connection: this->connections)
        {
            std::cout << "looping through the client connections at client " << connection->get_name() << std::endl;
            if(connection->get_name()==ss->get_name())
            {
                if(temp!=0){
                    message+=",";
                }
                temp++;
                message+="\""+connection->get_user_name()+"\"";
            }
        }
        message+="]}\n\n";
    }

    boost::asio::async_write(connection->socket_, boost::asio::buffer(message), 
            [message, connection, this](boost::system::error_code ec, std::size_t){
                if (!ec)
                {
                    std::cout << "writing message " << message << std::endl;
                    admin_parser_operations(connection);
                }
                else
                {
                    std::cout << "Error sending message " << ec.message() << std::endl;
                }
            });


}

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
        if(line != name_spreadsheet)
        {
            spreadsheet_names.insert(line);
        }
    }
    file.close();
    
    remove("../../data/spreadsheets.txt");

    std::ofstream outfile("../../data/spreadsheets.txt");

    for(std::string s : spreadsheet_names)
    {
        outfile << s << std::endl;
    }

    outfile.close();

    //SpreadsheetController::mu_lock_file_spreadsheet_txt.unlock();

   
}


void Server::admin_add_user(std::string add_user_name, std::string add_user_pass)
    {
        //SpreadsheetController::mu_lock_file_user_txt.lock();
        std::ifstream file("../../data/users.txt");
        std::string line;
        bool already_exists = false;
        while (std::getline(file, line))
        {
            std::vector<std::string> current_line = SpreadsheetController::split(line, " ");
            if(current_line.front() == add_user_name)
            {
                if(current_line.back() != add_user_pass)
                {
                    file.close();
                    admin_delete_user(add_user_name);
                    break;
                }
                else
                {
                    already_exists = true;
                    break;
                }
                
            }
        }
        if(!already_exists)
        {
            std::ofstream file;
            file.open("../../data/users.txt", std::ios_base::app);
            file << add_user_name << " " << add_user_pass <<std::endl;
            file.close();
        }
        //SpreadsheetController::mu_lock_file_user_txt.unlock();
    }
void Server::admin_delete_user(std::string del_user)
    {
        //SpreadsheetController::mu_lock_file_user_txt.lock();
        std::ifstream file("../../data/users.txt");
        std::string line;
        std::set<std::string> user_names;
        while (std::getline(file, line))
        {
            std::vector<std::string> current_line = SpreadsheetController::split(line, " ");
            if(current_line.front() != del_user)
            {
             user_names.insert(line);
            }
        }
        file.close();
    
        remove("../../data/users.txt");

        std::ofstream outfile("../../data/users.txt");

        for(std::string u : user_names)
        {
            outfile << u <<std::endl;
        }

        outfile.close();

        //SpreadsheetController::mu_lock_file_user_txt.unlock();

    }
void Server::admin_add_spreadsheet(json json_message)
    {
        std::string no_use_spread;
        std::cout<<json_message<<std::endl;
        std::ifstream file("../../data/spreadsheets.txt");
        std::string line;
        bool already_exists = false;
        while (std::getline(file, line))
            {
                if(line == json_message["name"]){
                    std::cout << already_exists <<std::endl;
                    already_exists=true;
                }
                    std::cout << already_exists <<std::endl;
            }
        file.close();
        if(!already_exists)
            {
                std::ofstream file;
                std::cout <<"Was not found"<<std::endl;
                std::cout << already_exists <<std::endl;
                file.open("../../data/spreadsheets.txt", std::ios_base::app);
                std::string name = json_message["name"];
                file << name <<std::endl;
                file.close();
            }
        
    }
void Server::admin_delete_spreadsheet(json json_message)
    {
        std::string no_use_spread;
        
        bool is_in_storage = SpreadsheetController::check_if_spreadsheet_in_storage(json_message, no_use_spread);
        if (is_in_storage)
        {
            admin_remove_spreadsheet(json_message);
        }
        else
        {
            // do nothing because it doesn't exist 
        }
    }
void Server::admin_off()
    {

        connections.clear();
       // SpreadsheetController::mu_lock_user_list.lock();
       // SpreadsheetController::mu_lock_spreadsheet_list.lock();
       // SpreadsheetController::mu_lock_file_user_txt.lock();
       // SpreadsheetController::mu_lock_file_spreadsheet_txt.lock();
        exit(0);
    }

void Server::admin_parser_operations(std::shared_ptr<ClientConnection> connection)
   {
       boost::asio::async_read_until(connection->socket_, connection->buff, "\n\n", 
        [connection, this](boost::system::error_code ec, std::size_t size){
            std::cout << "async read handler called" << std::endl;
                // get the message from the client
  //              buff.commit(size);
                std::istream istrm(&connection->buff);
                std::string message;
                std::getline(istrm, message);
                // istrm >> std::noskipws >> message;
                connection->buff.consume(size);
                std::cout << "admin message is " << message << std::endl;
                std::string error_message;
                if(message != "")
                {
                     json json_message = json::parse(message);
                    if(json_message.value("type", " ") != "open")
                        {
                            refresh_admin(connection);
                        }
                    if (json_message["Operation"]== "AU")
                        {
                            admin_add_user(json_message["name"], json_message["password"]);
                            refresh_admin(connection);
                        }
                    else if (json_message["Operation"]=="DU")
                        {
                            admin_delete_user(json_message["name"]);
                            refresh_admin(connection);
                        }
                    else if (json_message["Operation"]=="AS")
                        {
                            admin_add_spreadsheet(json_message);
                            refresh_admin(connection);
                        }
                    else if (json_message["Operation"]=="DS")
                        {
                            admin_delete_spreadsheet(json_message);
                            refresh_admin(connection);
                        }
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
                else
                {
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

void Server::save_data()
{
    // if the file does not exist, there is an issue
    if (boost::filesystem::exists("../../data/users.txt"))
    {
        // remove the users file, and then create it again
        std::remove("../../data/users.txt");
        std::ofstream write_file;
        write_file.open("../../data/users.txt");

        // loop through all of the users, and write them to the file
        for (UserModel user : this->users)
        {
            std::string user_string = user.get_name() + " " + user.get_password();
            write_file << user_string << std::endl;
        }
        write_file.close();

        // remove from the spreadsheet file, and create again
        std::remove("../../data/spreadsheets.txt");
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
    if (!SpreadsheetController::validate_login_message(message)) return false;
    if (message.value("type", " ") != "open")
    {
        return false;
    }
    // get the name and password from json message
    std::string name = message.value("username", " ");
    std::string password = message.value("password", " ");
    bool found = false;
    // loop through all the users and check if the name and password match. 
    for (UserModel user : this->users)
    {
        if (name == user.get_name() && password != user.get_password())
        {
            return false;
        }
        else if (name == user.get_name() && password == user.get_password())
        {
            found = true;
            break;
        }
    }
    // if we haven't found a user, add one to the list
    if (!found)
    {
        UserModel user(name, password);
        this->users.insert(user);
    }
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


