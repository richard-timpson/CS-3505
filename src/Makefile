cade: user_model spreadsheet_model spreadsheet_controller network_controller network_library main.cpp
	g++ -std=c++11  -o ../bin/main  main.cpp ../bin/user_model.o ../bin/spreadsheet_model.o ../bin/spreadsheet_controller.o ../bin/network_controller.o ../bin/network_library.o -lpthread -I ../libs/boost/include

all: user_model spreadsheet_model spreadsheet_controller network_controller dependency_graph network_library main.cpp
	g++ -std=c++11  -o ../bin/main  main.cpp ../bin/user_model.o ../bin/spreadsheet_model.o ../bin/spreadsheet_controller.o ../bin/network_controller.o ../bin/network_library.o ../bin/dependency_graph.o

user_model: user_model.cpp user_model.h
	g++ -std=c++11  -o ../bin/user_model.o -c user_model.cpp

spreadsheet_model: spreadsheet_model.cpp spreadsheet_model.h
	g++ -std=c++11  -o ../bin/spreadsheet_model.o -c spreadsheet_model.cpp

spreadsheet_controller: spreadsheet_controller.cpp spreadsheet_controller.h
	g++ -std=c++11  -o ../bin/spreadsheet_controller.o -c spreadsheet_controller.cpp

network_controller: network_library network_controller.cpp network_controller.h
	g++ -std=c++11  -o ../bin/network_controller.o -c  network_controller.cpp 

network_library: network_library.cpp network_library.h chat_server_client.h
	g++ -std=c++11 -o ../bin/network_library.o -c  network_library.cpp

dependency_graph: dependency_graph.cpp dependency_graph.h
	g++ -std=c++11 -o ../bin/dependency_graph.o -c dependency_graph.cpp





#asio_test: asio_test.cpp
#	g++ -std=c++11 -I ../libs/asio-1.12.2/include/ -lpthread -o asio_test asio_test.cpp

#socket: socket_test.cpp
#	g++ -std=c++11 -o socket socket_test.cpp

#socket_client: socket_client_test.cpp
#	g++ -std=c++11 -o socket_client socket_client_test.cpp

#new_test: new_test.cpp
#	g++ -std=c++11 -o new_test new_test.cpp


