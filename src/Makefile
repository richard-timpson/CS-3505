cade: user_model spreadsheet_model spreadsheet_controller network_controller network_library ./server/server.cpp
	g++ -std=c++11  -o ../bin/main  server.cpp ../bin/user_model.o ../bin/spreadsheet_model.o ../bin/spreadsheet_controller.o ../bin/network_controller.o ../bin/network_library.o -lpthread -I ../libs/boost/include

all: user_model spreadsheet_model spreadsheet_controller  server
	g++ -std=c++11  -o ../bin/server  ../bin/server.o ../bin/user_model.o ../bin/spreadsheet_model.o ../bin/spreadsheet_controller.o ../bin/network_controller.o

client: ./test_client/client.cpp
	g++ -std=c++11 -o ../bin/client ./test_client/client.cpp

user_model: ./models/user_model.cpp ./models/user_model.h
	g++ -std=c++11  -o ../bin/user_model.o -c ./models/user_model.cpp

spreadsheet_model: ./models/spreadsheet_model.cpp ./models/spreadsheet_model.h
	g++ -std=c++11  -o ../bin/spreadsheet_model.o -c ./models/spreadsheet_model.cpp

spreadsheet_controller: ./controllers/spreadsheet_controller.cpp ./controllers/spreadsheet_controller.h
	g++ -std=c++11  -o ../bin/spreadsheet_controller.o -c ./controllers/spreadsheet_controller.cpp

network_controller: ./server/network_library ./controllers/network_controller.cpp ./controllers/network_controller.h
	g++ -std=c++11  -o ../bin/network_controller.o -c  ./controllers/network_controller.cpp 

server: ./server/Server.cpp ./server/Server.h ./server/ClientConnection.h
	g++ -std=c++11 -o ../bin/server.o -c ./server/server.cpp


