#pragma once
#include "hidden_net_common.h"


template <typename T>
struct HiddenMessage {
    message_type type;
    size_t bodySize; // size or the body in bytes.
    T* body;
    unsigned int clientID;


    HiddenMessage(message_type msgType, T* msgBody, size_t msgBodySize, unsigned int clientId) {
       type = msgType;
       body = msgBody;
       bodySize = msgBodySize;
       this->clientID = clientId;

    };

    
    ~HiddenMessage() = default;
};