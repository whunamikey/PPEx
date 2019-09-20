
#ifndef PPEX_ENDPOINTMANAGER_H
#define PPEX_ENDPOINTMANAGER_H

#include <iostream>

#include "Endpoint.h"

using namespace std;

class EndpointManager {
public:
    EndpointManager();
    ~EndpointManager();
    int addEndpoint(Endpoint ep);
    int removeEndpoint(Endpoint ep);
    int getEndpointCount();
    void printEps();
    void destroyEps();
    Endpoint* getHead();
private:
    void eplist_create();
    void eplist_destroy(Endpoint* head);
    int eplist_add(Endpoint ep);
    int eplist_remove(Endpoint ep);
    int eplist_count();
    void eplist_dump();
private:
    Endpoint *head;
};


#endif //PPEX_ENDPOINTMANAGER_H
