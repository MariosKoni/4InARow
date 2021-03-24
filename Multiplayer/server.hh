#pragma once

#include "../Data/getData.hh"
#include "../Player/Player.hh"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <memory>
#include <vector>

class server {
private:
  static server *instance;
  int sock;
  unsigned short int port;
  int connfd;
  socklen_t client_len;
  struct sockaddr_in serverAddr, client;

  server(); // Because singleton

  std::vector<std::unique_ptr<Player>> clients;
  std::vector<int> clients_id;
  std::unique_ptr<getData> board;

public:
  static server* getInstance();
  void init(unsigned short int);
  std::string getServerIP();
  void waitConn();
  void retrieveClient(int);
  void serve();
  void sendMsg();
  void recvMsg();
  void closeServer();
  void setBoard(std::unique_ptr<getData>);
};
