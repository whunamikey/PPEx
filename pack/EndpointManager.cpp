#include "EndpointManager.h"

EndpointManager::EndpointManager() {
    eplist_create();
}

EndpointManager::~EndpointManager() {}

int EndpointManager::addEndpoint(Endpoint ep) {
    return eplist_add(ep);
}

int EndpointManager::removeEndpoint(Endpoint ep) {
    return eplist_remove(ep);
}

int EndpointManager::getEndpointCount() {
    return eplist_count();
}

void EndpointManager::printEps() {
    eplist_dump();
}

void EndpointManager::destroyEps() {
    eplist_destroy(head);
}

void EndpointManager::eplist_create() {
    head = static_cast<eplist *>(malloc(sizeof(eplist)));
    head->next = NULL;
}

void EndpointManager::eplist_destroy(eplist *head) {
    if (head == NULL)
        return;
    eplist_destroy(head->next);
    head->next = NULL;
    free(head);
}

int EndpointManager::eplist_add(Endpoint ep) {
    eplist *cur;
    for (cur = head;cur != NULL;cur = cur->next){
        if (cur != head && ep.ep_equal(ep,cur->endpoint)){
            return 1;
        }else if (cur->next == NULL){
            eplist *newep = static_cast<eplist*>(malloc(sizeof(eplist)));
            newep->endpoint = ep;
            newep->next = NULL;
            cur->next = newep;
            return 1;
        }
    }
    return 0;
}

int EndpointManager::eplist_remove(Endpoint ep) {
    eplist* cur;
    for (cur = head;cur != NULL && cur->next != NULL;cur = cur->next){
        if (ep.ep_equal(ep,cur->next->endpoint)){
            eplist *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
            return 1;
        }
    }
    return 0;
}

int EndpointManager::eplist_count() {
    int i =0;
    for (eplist* cur = head;cur != NULL;cur = cur->next){
        i++;
    }
    return i;
}

void EndpointManager::eplist_dump() {
    if (head == NULL)
        return;
    for (eplist* cur = head->next;cur != NULL;cur = cur->next){
        cout << cur->endpoint.ep_tostring(cur->endpoint) << cur->next ? "->" : "\n";
    }
}