#include <iostream>

#include "socket/udp/UdpServer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    UdpServer* udpServer = new UdpServer();
    udpServer->start();
    return 0;
}