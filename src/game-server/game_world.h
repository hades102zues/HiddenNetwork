#pragma once
#include "game_state.h"
#include <vector>
#include <unordered_map>
#include "../network/hidden_net_connection.h"
#include "../network/hidden_net_common.h"
#include <enet/enet.h>




class HiddenGame {
    private:
        std::unordered_map<unsigned int, EntityState> m_gameState;
        std::unordered_map<unsigned int, ENetPeer*> m_players; 
        unsigned int m_max_players;
        int playerCount = 0;
    public: 
        HiddenGame(int playerLimit);
        void update();
        void addPlayer(const HiddenConnection& conn);
        void removePlayer(unsigned int clientId);
        ENetPeer* findPlayer(unsigned int clientId);
        // handleInput(HiddenMsg);
        // update();
        // sendState();

        void genPlayerList();
        void genGameState();
        ~HiddenGame();


};