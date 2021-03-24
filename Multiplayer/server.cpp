#include "server.hh"

#include <iostream>
#include <thread>
#include <memory>
#include <utility>

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
  clients.reserve(2);
  clients_id.reserve(2);

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

  while (clients.size() < 2) {
    connfd = accept(sock, (struct sockaddr *) &client, &client_len);
    if (!connfd) {
      std::cout << "Couldn't accept new connection" << std::endl;
      exit(1);
    }

    retrieveClient(connfd);
    std::cout << clients.back()->getName() << " joined !" << std::endl;

    //std::thread sConn(&server::serve, this, connfd);
    //sConn.detach();
  }

  serve();
}

void server::retrieveClient(int connfd) {
  ssize_t re;
  char name[256];
  char favColor[5];

  // Retrieve the name
  re = read(connfd, name, 256);
  if (re == -1) {
    std::cout << "Cannot read from client" << std::endl;
    exit(1);
  }
  std::string n(name);

  // Retrieve the color
  re = read(connfd, favColor, 5);
  if (re == -1) {
    std::cout << "Cannot read from client" << std::endl;
    exit(1);
  }
  std::string fC(favColor);
  char fC1 = fC.at(0);
  if (clients.size()) {
    if (!fC.compare(clients.at(0).getColF())) {
      fC = "Red";
      fC1 = 'R';
    }
  }
  std::pair<std::string, char> c(fC, fC1);

  std::unique_ptr<Player> pl(new Player(n, c));
  clients.emplace_back(std::move(pl)); // std::move = &
  clients_id.emplace_back(connfd);
}

void server::serve() {
  std::string message("Players: " + clients.at(0)->getName() + ", " + clients.at(1)->getName());
  unsigned short int len = message.size();

  for (auto &client : clients_id)
    write(client, message.c_str(), len);

  for (unsigned short int i = 0; i < clients_id.size(); ++i) {
    if (!i) {
      message = "1";
      len = message.size();
      write(clients_id.at(0), message.c_str(), len);
    } else {
      message = "0";
      len = message.size();
      write(clients_id.at(0), message.c_str(), len);
    }
  }
}

void server::closeServer() {
  close(sock);
}

void server::setBoard(std::unique_ptr<getData> b) {
  board = std::move(b);
}
