#pragma once

#include "../network-server/server.h"
#include "game_world.h"

#include <unordered_map>


// #include "room.h"

class HiddenGameServer : public HiddenServer {
    private:
        // vector of games, maybe

        std::unique_ptr<HiddenGame> m_game;
        

    public:
        HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients);
        ~HiddenGameServer() = default;
        void run() override;
        void onConnection(ENetEvent& event) override;
        void onDisconnection(ENetEvent& event) override;
        void onMessage(ENetEvent& event) override;

};  
