#include "UdpServer.h"

UdpServer::UdpServer() {}

UdpServer::~UdpServer() {}

int UdpServer::start() {
    int s = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr addr_serv;
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(PORT_SERV);


}
