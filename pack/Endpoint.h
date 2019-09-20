//
// Created by smooth on 2019/9/20.
//

#ifndef PPEX_ENDPOINT_H
#define PPEX_ENDPOINT_H

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sockaddr_in endpoint_t;
class Endpoint {
public:
    Endpoint();
    ~Endpoint();
    int ep_equal(Endpoint src,Endpoint dst);
    char *ep_tostring(Endpoint ep);
    Endpoint ep_fromString(const char* str);
    Endpoint ep_fromPair(const char* ip, short port);

public:
    endpoint_t endpoint;
    Endpoint *next;
};


#endif //PPEX_ENDPOINT_H
