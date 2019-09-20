//
// Created by smooth on 2019/9/20.
//

#ifndef PPEX_UDPCLIENT_H
#define PPEX_UDPCLIENT_H

#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>
#include <assert.h>

#include "../../proto/Message.h"
#include "../../pack/Endpoint.h"
#include "../../pack/EndpointManager.h"

#define PING_INTERVAL 5

#define SERVER_ADDR "192.168.0.1:9123"
#define SERVER_IP "192.168.0.1"
#define SERVER_PORT 9123

class UdpClient {
public:
    UdpClient();
    ~UdpClient();
    void start();

    int send_text(int sock,Endpoint peer,MsgType type,const char* txt);
    int send_msg(int sock,Endpoint peer,Message msg);
    void deal_msg(Endpoint sock,Message msg);
public:
    int stop = 0;
    int clientfd;
    Endpoint serverEP;
    EndpointManager endpointManager;

private:
    int send_buf(int sock,Endpoint peer,MsgType type,const char* txt, unsigned int len);

private:
};


#endif //PPEX_UDPCLIENT_H
