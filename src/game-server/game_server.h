#pragma once

#include "../network-server/server.h"
#include "game_state.h"

// #include "room.h"

class HiddenGameServer : public HiddenServer {
    private:
        std::vector<EntityState> m_gameState;

    public:
        HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients);
        ~HiddenGameServer() = default;
        void run() override;
        void handleEvent() override;
        void onConnection(ENetEvent& event) override;
        void onDisconnection(ENetEvent& event) override;
        void onMessage(ENetEvent& event);

};  
