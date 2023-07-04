#pragma once

#include "../network-server/server.h"
#include "room.h"

class HiddenGameServer : public HiddenServer {
    private:
        HiddenRoom m_game_room;
        // max number of game rooms
    public:
        HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients);
        ~HiddenGameServer() = default;
};  
