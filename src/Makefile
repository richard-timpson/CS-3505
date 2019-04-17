############################
# Cade
############################
cade: spreadsheet_model spreadsheet_controller dependency_graph server_cade
	g++ -std=c++11  -o ../bin/executables/server  ./server/main.cpp ../bin/objects/server.o  ../bin/objects/spreadsheet_model.o ../bin/objects/spreadsheet_controller.o  ../bin/objects/dependency_graph.o -lpthread -I ../libs/boost/include -DBOOST_SYSTEM_NO_DEPRECATED

server_cade: ./server/Server.cpp ./server/Server.h ./server/ClientConnection.h
	g++ -std=c++11 -o ../bin/objects/server.o -c ./server/Server.cpp -I ../libs/boost/include

############################
# Normal
############################
server_all: ./server/Server.cpp ./server/Server.h ./server/ClientConnection.h
	g++ -std=c++11 -o ../bin/objects/server.o -c ./server/Server.cpp 

all: spreadsheet_model spreadsheet_controller dependency_graph server_all
	g++ -std=c++11  -o ../bin/executables/server  ./server/main.cpp  ../bin/objects/server.o ../bin/objects/spreadsheet_model.o ../bin/objects/spreadsheet_controller.o ../bin/objects/dependency_graph.o 

############################
# Neutral
############################
spreadsheet_model: ./models/SpreadsheetModel.cpp ./models/SpreadsheetModel.h dependency_graph cell
	g++ -std=c++11  -o ../bin/objects/spreadsheet_model.o -c ./models/SpreadsheetModel.cpp ../bin/objects/dependency_graph.o ../bin/objects/cell.o

spreadsheet_controller: ./controllers/SpreadsheetController.cpp ./controllers/SpreadsheetController.h
	g++ -std=c++11  -o ../bin/objects/spreadsheet_controller.o -c ./controllers/SpreadsheetController.cpp

dependency_graph: ./models/DependencyGraph.cpp ./models/DependencyGraph.h 
	g++ -std=c++11 -o ../bin/objects/dependency_graph.o -c ./models/DependencyGraph.cpp

cell: ./models/Cell.cpp ./models/Cell.h
	g++ -std=c++11 -o ../bin/objects/cell.o -c ./models/Cell.cpp

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
