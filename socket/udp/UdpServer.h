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
#include <vector>

#include "../../pack/Endpoint.h"
#include "../../proto/Message.h"

using namespace std;

#define UDP_ADDR "0.0.0.0"
#define UDP_PORT 9123


class UdpServer {
public:
    UdpServer();
    ~UdpServer();
    int start();
    int send_text(int sock,Endpoint peer,MsgType type,const char* txt);
private:
    void receive_loop(int sock);
    void deal_message(int sock,Endpoint peer,Message msg);
    int send_buf(int sock,Endpoint peer,MsgType type,const char* txt, unsigned int len);
    int send_msg(int sock,Endpoint peer,Message msg);
private:
    vector<Endpoint> peers;
};


#endif //PPEX_UDPSERVER_H
