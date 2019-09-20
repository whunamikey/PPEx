
#ifndef PPEX_ENDPOINTMANAGER_H
#define PPEX_ENDPOINTMANAGER_H

#include <iostream>

#include "Endpoint.h"

using namespace std;

struct _EnpointList{
    Endpoint endpoint;
    _EnpointList *next;
};
typedef _EnpointList eplist;

class EndpointManager {
public:
    EndpointManager();
    ~EndpointManager();
    int addEndpoint(Endpoint ep);
    int removeEndpoint(Endpoint ep);
    int getEndpointCount();
    void printEps();
    void destroyEps();

private:
    void eplist_create();
    void eplist_destroy(eplist* head);
    int eplist_add(Endpoint ep);
    int eplist_remove(Endpoint ep);
    int eplist_count();
    void eplist_dump();
private:
    eplist *head;
};


#endif //PPEX_ENDPOINTMANAGER_H
