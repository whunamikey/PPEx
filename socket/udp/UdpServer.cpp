#include "UdpServer.h"

UdpServer::UdpServer() {}

UdpServer::~UdpServer() {}

int UdpServer::start() {
    Endpoint server;
    server = server.ep_fromPair(UDP_ADDR,UDP_PORT);
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if (sock == -1){
        cout << "UDP server socket fail" << endl;
        exit(0);
    }
    int ret = bind(sock,(const struct sockaddr*)&server.endpoint, sizeof(server.endpoint));
    if (ret == -1){
        cout << "UDP server bind error result:" << ret << endl;
        exit(0);
    }
    cout << "UDP server start on " << server.ep_tostring(server) << endl;
    receive_loop(sock);
    return 1;
}

void UdpServer::receive_loop(int sock) {
    Endpoint peer;
    socklen_t  addrlen;
    char buf[RECV_BUFSIZE];
    for(;;){
        addrlen = sizeof(peer.endpoint);
        memset(&peer.endpoint,0,addrlen);
        memset(buf,0,RECV_BUFSIZE);
        int rd_size;
        rd_size = recvfrom(sock,buf,RECV_BUFSIZE,0,(struct sockaddr*)&peer.endpoint,&addrlen);
        if (rd_size == -1){
            cout << "recv from error:" << rd_size << endl;
            break;
        }else if (rd_size == 0){
            cout << "EOF from " << peer.ep_tostring(peer) << endl;
            continue;
        }
        Message msg;
        msg = msg.msg_unpack(buf,rd_size);
        if (msg.version != MSG_VERSION || msg.content == NULL){
            cout << "Invalid msg " << rd_size << " byte " << endl;
            continue;
        }
        deal_message(sock,peer,msg);
        continue;
    }
    cout << "udp recv loop stopped." << endl;
}

void UdpServer::deal_message(int sock, Endpoint peer, Message msg) {
    cout << "deal msg " << msg.length << " byte from " << peer.ep_tostring(peer) << endl;
    switch (msg.type){
        case MSG_TYPE_LOGIN:
            {
                int beforsize = peers.size();
                peers.push_back(peer);
                if (peers.size() > beforsize){
                    cout << peer.ep_tostring(peer) << " log in succ" << endl;
                    send_text(sock,peer,MSG_TYPE_REPLY,"Login succ");
                }else{
                    cout << peer.ep_tostring(peer) << " log in fail" <<endl;
                    send_text(sock,peer,MSG_TYPE_REPLY,"Login failed");
                }
            }
            break;
        case MSG_TYPE_LOGOUT:
            {
                int beforesize = peers.size();
                break;
            }
        case MSG_TYPE_LIST:
            {
                char text[SEND_BUFSIZE - MSG_HEADLEN] = {0};
                vector<Endpoint>::iterator peerIt;
                for (peerIt = peers.begin();peerIt != peers.end();peerIt ++){

                }
                break;
            }
    }

}
