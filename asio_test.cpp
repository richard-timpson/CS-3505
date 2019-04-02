#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#include <iostream>
#include <asio.hpp>

void print(const asio::error_code& /*e*/)
{
  std::cout << "Hello, world!" << std::endl;
}

int main()
{
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.async_wait(&print);

    io.run();

    return 0;
}