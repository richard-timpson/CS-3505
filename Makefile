socket: socket_test.cpp
	g++ -std=c++11 -o socket socket_test.cpp

socket_client: socket_client_test.cpp
	g++ -std=c++11 -o socket_client socket_client_test.cpp

new_test: new_test.cpp
	g++ -std=c++11 -o new_test new_test.cpp

asio_test: asio_test.cpp
	g++ -std=c++11 -I asio-1.12.2/include/ -lpthread -o asio_test asio_test.cpp
