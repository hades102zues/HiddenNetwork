#pragma once
#include "hidden_net_common.h"

/*
    Using a pointer to reference the body may not become viable for later implementations.
    So eventually we may need to straight up copy the data into the message. 
*/
template <typename T>
struct HiddenMessage {
    message_type type;
    size_t bodySize; // size or the body in bytes.
    T* body; // must be a pointer to an array. anything else will result in some bad behaviour
    unsigned int clientID;


    HiddenMessage(message_type msgType, T* msgBody, size_t msgBodySize, unsigned int clientId) {
       type = msgType;
       body = msgBody;
       bodySize = msgBodySize;
       this->clientID = clientId;

    };

    
    ~HiddenMessage() = default;
};