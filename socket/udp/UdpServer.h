#ifndef PPEX_UDPSERVER_H
#define PPEX_UDPSERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class UdpServer {
public:
    UdpServer();
    ~UdpServer();
    int start();
private:
};


#endif //PPEX_UDPSERVER_H
