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
#define MSG_VERSION 1
/* a message is a UDP datagram with following structure:
   -----16bits--+---16bits--+-----32bits----------+---len*8bits---+
   --  0x01   + msg type  + msg length(exclude) + message body  +
   -------------+-----------+---------------------+---------------+
*/
enum _MessageType {
    MSG_TYPE_LOGIN = 0,
    MSG_TYPE_LOGOUT,
    MSG_TYPE_LIST,
    MSG_TYPE_PUNCH,
    MSG_TYPE_PING,
    MSG_TYPE_PONG,
    MSG_TYPE_REPLY,
    MSG_TYPE_TEXT,
    MSG_TYPE_END
};
typedef  enum _MessageType MsgType;

class Message {
public:
    Message();
    ~Message();
    int msg_pack(Message msg,char* buf, unsigned int bufsize);
    Message msg_unpack(const char* buf, unsigned int bufsize);

public:
    uint16_t version;
    uint16_t type;
    uint32_t length;
    const char* content;
};


#endif //STUNPROTOCOL_MESSAGE_H
