#include<iostream>
#include<string>
#include<memory>
#include<boost/asio.hpp>

using namespace boost::asio::ip;


int main (int argc, char** argv)
{
    try
    {
        int port = atoi(argv[1]);
        std::string address(argv[2]);
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(address::from_string("127.0.0.1"), 2112);
        // tcp::endpoint endpoint(address::from_string(address), 2112);
        tcp::socket socket(io_context);
        std::cout << "client connection to server..." << std::endl;
        socket.async_connect(endpoint, [](const boost::system::error_code &ec){
            if (!ec)
            {
                std::cout << "client connection successful" << std::endl;
            }
            else 
            {
                std::cout << "error connecting" << std::endl;
            }
        });
        // std::thread t([&io_context](){   
        // });
        
        char read[256];
        boost::asio::streambuf buff;
        boost::asio::async_read_until(socket, buff, '\n',
                    [&buff](boost::system::error_code ec, std::size_t size ){
                        boost::asio::streambuf::const_buffers_type bufs = buff.data();
                        std::string message(boost::asio::buffers_begin(bufs),
                        boost::asio::buffers_begin(bufs) + size);
                        std::cout << "received  Message " << message << std::endl;
                        if (!ec)
                        {
                            std::cout << message << std::endl;
                        }
                        else 
                        {
                            std::cout << ec.message() << std::endl;
                        }
                    });
        io_context.run();
        while(true);

    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}