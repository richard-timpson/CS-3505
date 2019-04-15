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

        // char line[7]="hello\n";
        // char read[7];
        // char waste[10];
        // while(std::cin.getline(waste, 10))
        // {
        //     std::cout << "trying to write message " << std::string(line) << std::endl;
        //     boost::asio::async_write(socket, boost::asio::buffer(line, 7), 
        //         [](boost::system::error_code ec, std::size_t bytes_transferred) {
        //             std::cout << "async writing" << std::endl;
        //             if (!ec)
        //             {
        //                 std::cout << "succesfully wrote message " << std::endl;
        //             }
        //             else
        //             {
        //                 std::cout << "error writing message" << std::endl;
        //             }
                    
        //         });
        //     std::cout << "trying to receive message " << std::endl;
        //     boost::asio::async_read(socket, boost::asio::buffer(read, 7), 
        //     [read](boost::system::error_code ec, std::size_t ){
        //         std::cout << "received  Message " << read << std::endl;
        //         if (!ec)
        //         {
        //             std::cout << read << std::endl;
        //         }
        //         else 
        //         {
        //             std::cout << ec.message() << std::endl;
        //         }
        //     });
        //     io_context.run();
        // }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}