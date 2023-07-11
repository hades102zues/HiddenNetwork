#pragma once

#include "hidden_net_common.h"


struct HiddenConnection {
        unsigned int client_id;
        ENetPeer* peer;

        
        HiddenConnection(unsigned int id, ENetPeer* peer_machine) : client_id(id), peer(peer_machine) {}
        // HiddenConnection(const HiddenConnection& other) {
        //         client_id = other.client_id;
        //         peer = other.peer;
        // }
        unsigned int getClientId() const {return client_id;}
        ENetPeer* getPeer() const {return peer;}
        
        ~HiddenConnection(){}
};