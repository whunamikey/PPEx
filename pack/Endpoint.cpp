#include "Endpoint.h"

#define INET_PORTSTRLEN 5
#define TUPLE_LEN (INET_PORTSTRLEN)

Endpoint::Endpoint() {}

Endpoint::~Endpoint() {}

int Endpoint::ep_equal(Endpoint src, Endpoint dst) {
    return (src.endpoint.sin_family == dst.endpoint.sin_family) &&
            (src.endpoint.sin_addr.s_addr == dst.endpoint.sin_addr.s_addr) &&
            (src.endpoint.sin_port == dst.endpoint.sin_port);
}

char* Endpoint::ep_tostring(Endpoint ep) {
    char tuple[21];
    snprintf(tuple,21,"%s:%d",inet_ntoa(ep.endpoint.sin_addr),ntohs(ep.endpoint.sin_port));
    return tuple;
}

Endpoint Endpoint::ep_fromString(const char *str) {
    char _tuple[21];
    char *host = NULL;
    char *port = NULL;
    sprintf(_tuple,"%s",str);
    host = strtok(_tuple,":");
    port = strtok(NULL,":");
    if (host == NULL || port == NULL){
        host = "255.255.255.255";
        port = "0";
    }
    return ep_fromPair(host,atoi(port));
}

Endpoint Endpoint::ep_fromPair(const char *ip, short port) {
    Endpoint ep;
    memset(&ep,0, sizeof(ep));
    ep.endpoint.sin_family = AF_INET;
    ep.endpoint.sin_addr.s_addr = inet_addr(ip);
    ep.endpoint.sin_port = htons(port);
    return ep;
}

