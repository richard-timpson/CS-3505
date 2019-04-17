############################
# Cade
############################
cade: user_model spreadsheet_model spreadsheet_controller dependency_graph network_controller server_cade
	g++ -std=c++11  -o ../bin/executables/server  ./server/main.cpp ../bin/objects/server.o ../bin/objects/user_model.o ../bin/objects/spreadsheet_model.o ../bin/objects/spreadsheet_controller.o ../bin/objects/network_controller.o  -lpthread -I ../libs/boost/include -DBOOST_SYSTEM_NO_DEPRECATED

server_cade: ./server/Server.cpp ./server/Server.h ./server/ClientConnection.h
	g++ -std=c++11 -o ../bin/objects/server.o -c ./server/Server.cpp -I ../libs/boost/include

############################
# Normal
############################
server_all: ./server/Server.cpp ./server/Server.h ./server/ClientConnection.h
	g++ -std=c++11 -o ../bin/objects/server.o -c ./server/Server.cpp 

<<<<<<< HEAD
all: user_model spreadsheet_model spreadsheet_controller dependency_graph network_controller  server_all
	g++ -std=c++11  -o ../bin/executables/server  ./server/main.cpp  ../bin/objects/server.o ../bin/objects/user_model.o ../bin/objects/spreadsheet_model.o ../bin/objects/spreadsheet_controller.o ../bin/objects/dependency_graph.o ../bin/objects/network_controller.o
=======
all: user_model spreadsheet_model spreadsheet_controller dependency_graph cell network_controller  server_all
	g++ -std=c++11  -o ../bin/executables/server  ../bin/objects/server.o ../bin/objects/user_model.o ../bin/objects/spreadsheet_model.o ../bin/objects/spreadsheet_controller.o ../bin/objects/dependency_graph.o ../bin/objects/cell.o ../bin/objects/network_controller.o
>>>>>>> SpreadsheetModel

############################
# Neutral
############################
user_model: ./models/user_model.cpp ./models/user_model.h
	g++ -std=c++11  -o ../bin/objects/user_model.o -c ./models/user_model.cpp

spreadsheet_model: ./models/SpreadsheetModel.cpp ./models/SpreadsheetModel.h
	g++ -std=c++11  -o ../bin/objects/spreadsheet_model.o -c ./models/SpreadsheetModel.cpp

spreadsheet_controller: ./controllers/SpreadsheetController.cpp ./controllers/SpreadsheetController.h
	g++ -std=c++11  -o ../bin/objects/spreadsheet_controller.o -c ./controllers/SpreadsheetController.cpp

network_controller:  ./controllers/network_controller.cpp ./controllers/network_controller.h
	g++ -std=c++11  -o ../bin/objects/network_controller.o -c  ./controllers/network_controller.cpp 

dependency_graph: ./models/dependency_graph.cpp ./models/dependency_graph.h
	g++ -std=c++11 -o ../bin/objects/dependency_graph.o -c ./models/dependency_graph.cpp

cell: ./models/cell.cpp ./models/cell.h
	g++ -std=c++11 -o ../bin/objects/cell.o -c ./models/cell.cpp

########################
# tests
########################
client_all: ./tests/client.cpp
	g++ -std=c++11 -o ../bin/tests/client ./tests/client.cpp 

client_cade: ./tests/client.cpp
	g++ -std=c++11 -o ../bin/tests/client ./tests/client.cpp -I ../libs/boost/include -lpthread

spreadsheet_controller_tests: ./tests/spreadsheet_controller_tests.cpp
	g++ -std=c++11 -o ../bin/tests/spreadsheet_controller ./tests/spreadsheet_controller_tests.cpp ../bin/objects/spreadsheet_controller.o ../bin/objects/server.o ../bin/objects/spreadsheet_model.o


######################
# Cleaning binaries
######################
clean:
	rm -rf ../bin/objects/* ../bin/executables/* ../bin/tests/*
