#include "Message.h"


Message::Message() {}

Message::~Message() {}

int Message::msg_pack(Message msg, char *buf, unsigned int bufsize) {
    if (bufsize < MSG_HEADLEN + msg.length){
        cout << "buf too small"<< endl;
        return 0;
    }
    uint16_t version = htons(msg.version);
    uint16_t type = htons(msg.type);
    uint32_t length = htonl(msg.length);
    int index = 0;
    memcpy(buf+index,&version,MSG_VLEN);
    index += MSG_VLEN;
    memcpy(buf+index,&type,MSG_TYPELEN);
    index += MSG_TYPELEN;
    memcpy(buf+index,&length,MSG_BODYLEN);
    index += MSG_BODYLEN;
    memcpy(buf+index,msg.content,msg.length);
    index += msg.length;
    return index;
}

Message Message::msg_unpack(const char *buf, unsigned int bufsize) {
    Message m;
    memset(&m,0, sizeof(m));
    if (bufsize < MSG_HEADLEN){
        cout << "overflow." << endl;
        return m;
    }
    int index = 0;
    m.version = ntohs(*(uint16_t *)(buf + index));
    index += sizeof(uint16_t);
    m.type = ntohs(*(uint16_t *)(buf+index));
    index += sizeof(uint16_t);
    m.length = ntohl(*(uint32_t *)(buf + index));
    if (index + m.length > bufsize){
        cout << "larger than receiver content" << endl;
        m.length = bufsize - index;
    }
    m.content = buf + index;
    return m;
}
