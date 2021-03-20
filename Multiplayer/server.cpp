#include "server.hh"

#include <iostream>
#include <thread>
#include <memory>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

server::server() {}

server* server::getInstance() {
  if (!instance)
    instance = new server;

  return instance;
}

void server::init(unsigned short int p) {
  this->port = p;

  std::cout << "Initializing server" << std::endl;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (!sock) {
    std::cout << "Failed to create socket" << std::endl;
    exit(1);
  }

  bzero(&serverAddr, sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(port);

  if (bind(sock, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cout << "Could not bind" << std::endl;
    exit(1);
  }
  std::cout << "Binded socket" << std::endl;
}

void server::waitConn() {
  listen(sock, 2);
  client_len = sizeof(client);
  
  while (true) {
    std::cout << "Waiting for player" << std::endl;
    connfd = accept(sock, (struct sockaddr *) &client, &client_len);
    if (!connfd) {
      std::cout << "Couldn't accept new connection" << std::endl;
      exit(1);
    }

    std::thread sConn(&server::serve, this, connfd);
    sConn.detach();
  }
}

void server::serve(int connfd) {
  //int n = read(connfd, )
  std::cout << "Serving" << std::endl;
}

server::~server() {
  close(sock);
}
