#pragma once
#include "game_state.h"
#include <vector>
#include <unordered_map>
#include "../network/hidden_net_connection.h"
#include "../network/hidden_net_common.h"
#include <enet/enet.h>




class HiddenGame {
    private:
        int m_playerMoveSpeed = 80; // pixels per second
        float m_dt = 1.0f/60.0f; // time for one frame

        int m_playerCount = 0;
        std::unordered_map<unsigned int, EntityState> m_gameState;
        std::unordered_map<unsigned int, ENetPeer*> m_players; 
        unsigned int m_max_players;
        
    public: 
        HiddenGame(int playerLimit);
        void update();
        void handleMovement(unsigned int clientId, game_movement val);

        void addPlayer(const HiddenConnection& conn);
        void removePlayer(unsigned int clientId);
        ENetPeer* findPlayer(unsigned int clientId);


        // sendState();

        void genPlayerList();
        void genGameState();
        ~HiddenGame();


};