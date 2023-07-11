#pragma once
#include "game_state.h"
#include <vector>
#include <unordered_map>
#include "../network/hidden_net_connection.h"
#include "../network/hidden_net_common.h"
#include "../network/hidden_net_message.h"
#include "../network/hidden_net.h"
#include <enet/enet.h>




class HiddenGame {
    private:

        const std::unique_ptr<HiddenNet>& m_network;

        int m_playerMoveSpeed = 80; // pixels per second
        float m_dt = 1.0f/60.0f; // time for one frame
        int m_playerCount = 0;
        std::unordered_map<unsigned int, EntityState> m_gameState;
        std::unordered_map<unsigned int, ENetPeer*> m_players; 
        unsigned int m_max_players;
        
    public: 
        HiddenGame(const std::unique_ptr<HiddenNet>& net, int playerLimit);
        void run();
        void update();
        void handleMovement(unsigned int clientId, game_movement val);

        void sendState();
        
        void addPlayer(const HiddenConnection& conn);
        void removePlayer(unsigned int clientId);
        ENetPeer* findPlayer(unsigned int clientId);


        

        void genPlayerList();
        void genGameState();
        ~HiddenGame();


};