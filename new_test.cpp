#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "json.hpp" 

int main(int argc, char * argv[])
{
  // checking for port number provided
  if (argc < 2)
  {
    std::cout << "Error, no port provided" << std::endl;
    return -1;
  }
  // creating a socket file descriptor
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    std::cout << "Error opening socket" << std::endl;
    return -1;
  }
  // creating the socket address stucture for the server and client sockets.
  struct sockaddr_in serv_address, client_address;

  // setting the socket buffer to 0's
  bzero((char*) $serv_addr, sizeof(serv_address));

  // getting the port number passed in as an argument
  int port_number = atoi(argv[1]);
  
  // setting the correct fields for the socket file descriptor
  serv_address.sin_family = AF_INET;
  serv_address.sin_port = htons(port_number);
  serv_address.sin_addr.s_addr = INADDR_ANY;

  //
  if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_addr)) < 0)
  {
    std::cout << "Error in socket binding" << std::endl;
    return -1;
  }
  // process runs async, I think.
  listen(sockfd, 5);

  // getting the size of the client address 
  int client_length = sizeof(client_address);

  // accepting a connection into the client address using the sockfd. 
  // this is a blocking statement and will wait until the connection is successful. 
  int new_socket_fd = accept(sockfd, (struct sockaddr *) &cli_addr, &client_length);
  if (new_socket_fd < 0)
  {
    std::cout << "Error on accept" << endl;
  }

  // the buffer to read in data from the client, 0'ing it out to begin with
  char buffer[256];
  bzero(buffer, 256);
  
  // reading bytes from the new socket file descriptor into the allocated buffer
  // this code with block until data has been read. 
  // happens after a write on the client side. 
  int n = read(newsockfd, buffer, 255);
  if (n < 0)
  {
    std::cout << "Error reading from socket" << std::endl;
    return -1;
  }

  // outputting the message we received
  std::cout << "Here is the message" << buffer << std::endl;
  
  // writing back to the user letting them know we got the message
  n = write(newsockfd, "I got the message");

  return 0;

  


}
