spreadsheet_controller: spreadsheet_controller.cpp spreadsheet_controller.h
	g++ -std=c++11  -o ../bin/spreadsheet_controller.o spreadsheet_controller.cpp

network_controller: ../bin/network_library.o network_controller.cpp network_controller.h
	g++ -std=c++11  -o ../bin/network_controller.o -c  network_controller.cpp ../bin/network_library.o

network_library: network_library.cpp network_library.h
	g++ -std=c++11 -I ../libs/asio-1.12.2/include/ -lpthread -o ../bin/network_library.o -c  network_library.cpp





#asio_test: asio_test.cpp
#	g++ -std=c++11 -I ../libs/asio-1.12.2/include/ -lpthread -o asio_test asio_test.cpp

#socket: socket_test.cpp
#	g++ -std=c++11 -o socket socket_test.cpp

#socket_client: socket_client_test.cpp
#	g++ -std=c++11 -o socket_client socket_client_test.cpp

#new_test: new_test.cpp
#	g++ -std=c++11 -o new_test new_test.cpp


