#include "UdpClient.h"

UdpClient::UdpClient() {}
UdpClient::~UdpClient() {
    close(clientfd);
}

void* keepalive_loop(UdpClient* client){
    cout << "client keepalive loop start" << endl;
    Message ping;
    ping.version = MSG_VERSION;
    ping.type = MSG_TYPE_PING;
    ping.length = 0;
    ping.content = NULL;
    unsigned int i =0;
    while(!client->stop){
        if (i++ < PING_INTERVAL){
            sleep(1);
            continue;
        }
        i=0;
        client->send_msg(client->clientfd,client->serverEP,ping);
        Endpoint* head = client->endpointManager.getHead();
        for (Endpoint* ep = head;ep != NULL;ep = ep->next){
            client->send_msg(client->clientfd,*ep,ping);
        }
    }
    return NULL;
}


void* receive_loop(UdpClient* client){
    Endpoint peer;
    socklen_t addrlen;
    char buf[RECV_BUFSIZE];
    int nfds;
    fd_set readfds;
    struct timeval timeout;

    nfds = client->clientfd+1;
    while(!client->stop){
        FD_ZERO(&readfds);
        FD_SET(client->clientfd,&readfds);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        int ret = select(nfds,&readfds,NULL,NULL,&timeout);
        if (ret == 0){
            continue;
        }else if (ret == -1){
            cout << "error in select " << endl;
            continue;
        }
        assert(FD_ISSET(client->clientfd,&readfds));
        addrlen = sizeof(peer.endpoint);
        memset(&peer.endpoint,0,addrlen);
        memset(buf,0,RECV_BUFSIZE);
        int rd_size = recvfrom(client->clientfd,buf,RECV_BUFSIZE,0,(struct sockaddr *)&peer.endpoint,&addrlen);
        if (rd_size == -1){
            cout << "recvfrom error" << endl;
            continue;
        }else if (rd_size == 0){
            cout << "EOF from " << peer.ep_tostring(peer) << endl;
            continue;
        }
        Message msg;
        msg = msg.msg_unpack(buf,rd_size);
        if (msg.version != MSG_VERSION || msg.content == NULL){
            cout << "invalid msg " << rd_size << " byte " <<endl;
            continue;
        }
        client->deal_msg(peer,msg);
    }
    return NULL;
}

void UdpClient::start() {
    serverEP = serverEP.ep_fromString();
    clientfd = socket(AF_INET,SOCK_DGRAM,0);
    if (clientfd == -1){
        cout << "client socket failed" << endl;
        exit(0);
    }
    thread keepalive(keepalive_loop,this);
    thread recloop(receive_loop,this);
    keepalive.join();
    recloop.join();
}


int UdpClient::send_text(int sock, Endpoint peer, MsgType type, const char *txt) {
    unsigned int len = txt == NULL ? 0 : strlen(txt);
    return send_buf(sock,peer,type,txt,len);
}

int UdpClient::send_buf(int sock, Endpoint peer, MsgType type, const char *txt, unsigned int len) {
    Message m;
    m.version = MSG_VERSION;
    m.type = type;
    m.length = len;
    m.content = txt;
    return send_msg(sock,peer,m);
}

int UdpClient::send_msg(int sock, Endpoint peer, Message msg) {
    char buf[SEND_BUFSIZE] = {0};
    int size = msg.msg_pack(msg,buf,SEND_BUFSIZE);
    return sendto(sock,buf,size,MSG_DONTWAIT,(struct sockaddr *)&peer.endpoint,sizeof(peer.endpoint));
}

void UdpClient::deal_msg(Endpoint sock, Message msg) {
    cout << "recv " << msg.length << " bytes from " << sock.ep_tostring(sock) << endl;
    //from server
    if (sock.ep_equal(sock,serverEP)){
        switch (msg.type){
            case MSG_TYPE_PONG:{
                cout << "recv pong msg from server";
                break;
            }
        }
    }
    //from peer
    switch (msg.type){
        case MSG_TYPE_TEXT:
            cout << "text from " << sock.ep_tostring(sock) << " say:" << msg.content <<endl;
            break;
        case MSG_TYPE_REPLY:
            cout << "reply from " << sock.ep_tostring(sock) << " say:" << msg.content << endl;
            break;
        case MSG_TYPE_PONG:
            cout << "pong from " << sock.ep_tostring(sock) << endl;
            break;
        case MSG_TYPE_PUNCH:
            send_text(clientfd,sock,MSG_TYPE_TEXT,"I SEE YOU");
            break;
        case MSG_TYPE_PING:
            send_text(clientfd,sock,MSG_TYPE_PONG,"");
            break;
    }
}