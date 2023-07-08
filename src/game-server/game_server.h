#pragma once

#include "../network-server/server.h"
#include "game_state.h"
#include <unordered_map>

// #include "room.h"

class HiddenGameServer : public HiddenServer {
    private:
        std::vector<EntityState> m_gameState;
        std::unordered_map<unsigned int, bool> m_players; 
        unsigned int m_max_players;

    public:
        HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients);
        ~HiddenGameServer() = default;
        void run() override;
        void handleEvent() override;
        void onConnection(ENetEvent& event) override;
        void onDisconnection(ENetEvent& event) override;
        void onMessage(ENetEvent& event);

};  
