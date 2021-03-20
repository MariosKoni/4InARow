#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <memory>

class server {
private:
  static server *instance;
  int sock;
  unsigned short int port;
  int connfd;
  socklen_t client_len;
  struct sockaddr_in serverAddr, client;

  server(); // Because singleton

public:
  static server* getInstance();
  void init(unsigned short int);
  void waitConn();
  void serve(int);
  void sendMsg();
  void recvMsg();
  ~server();
};
