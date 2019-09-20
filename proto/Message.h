#ifndef STUNPROTOCOL_MESSAGE_H
#define STUNPROTOCOL_MESSAGE_H

#include <stdint.h>
#include <iostream>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

#define MSG_VLEN 2
#define MSG_TYPELEN 2
#define MSG_BODYLEN 4
#define MSG_HEADLEN 8
/* a message is a UDP datagram with following structure:
   -----16bits--+---16bits--+-----32bits----------+---len*8bits---+
   --  0x01   + msg type  + msg length(exclude) + message body  +
   -------------+-----------+---------------------+---------------+
*/

enum _MessageType {
    MTYPE_LOGIN = 0,
    MTYPE_LOGOUT,
    MTYPE_LIST,
    MTYPE_PUNCH,
    MTYPE_PING,
    MTYPE_PONG,
    MTYPE_REPLY,
    MTYPE_TEXT,
    MTYPE_END
};

class Message {
public:
    Message();
    ~Message();
    int msg_pack(Message msg,char* buf, unsigned int bufsize);
    Message msg_unpack(const char* buf, unsigned int bufsize);
private:
    uint16_t version;
    uint16_t type;
    uint32_t length;
    const char* content;
};


#endif //STUNPROTOCOL_MESSAGE_H
