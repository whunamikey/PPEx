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
    head = new Endpoint();
    head->next = NULL;
}

void EndpointManager::eplist_destroy(Endpoint *head) {
    if (head == NULL)
        return;
    eplist_destroy(head->next);
    head->next = NULL;
    free(head);
}

int EndpointManager::eplist_add(Endpoint ep) {
    Endpoint *cur;
    for (cur = head;cur != NULL;cur = cur->next){
        if (cur != head && ep.ep_equal(ep,*cur)){
            return 1;
        }else if (cur->next == NULL){
            cur->next = &ep;
            return 1;
        }
    }
    return 0;
}

int EndpointManager::eplist_remove(Endpoint ep) {
    Endpoint* cur;
    for (cur = head;cur != NULL && cur->next != NULL;cur = cur->next){
        if (ep.ep_equal(ep,*cur)){
            Endpoint *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
            return 1;
        }
    }
    return 0;
}

int EndpointManager::eplist_count() {
    int i =0;
    for (Endpoint* cur = head;cur != NULL;cur = cur->next){
        i++;
    }
    return i;
}

void EndpointManager::eplist_dump() {
    if (head == NULL)
        return;
    for (Endpoint* cur = head->next;cur != NULL;cur = cur->next){
        cout << cur->ep_tostring(*cur) << cur->next ? "->" : "\n";
    }
}

Endpoint* EndpointManager::getHead() {
    return head;
}