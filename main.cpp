#include <iostream>

#include "socket/udp/UdpServer.h"
#include "socket/udp/UdpClient.h"

using namespace std;

void startServer();
void startClient();

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}

void startServer(){
    cout << "start server" << endl;
    UdpServer* udpServer = new UdpServer();
    udpServer->start();
}

void startClient(){
    cout << "start client" << endl;
    UdpClient* udpClient =new  UdpClient();
    udpClient->start();
}

