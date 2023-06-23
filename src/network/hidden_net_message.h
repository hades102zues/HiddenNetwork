#pragma once
#include "hidden_net_common.h"


template <typename T>
struct HiddenMessage {
    message_type type;
    T data;
    unsigned int designatedClientID;


    HiddenMessage(
        message_type msgType, 
        T msgData, 
        unsigned int clientId
    ): type(msgType), data(msgData), designatedClientID(clientId) {};

    
    ~HiddenMessage() = default;
};