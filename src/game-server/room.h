#pragma once
#include <unordered_map>
#include <vector>
#include "game_state.h"




class HiddenRoom {
    private:
        // unsigned int m_room_id;
        unsigned int m_max_num_players;
        std::unordered_map<unsigned int, bool> m_players; // std::pair{clientId, true}
        std::vector<EntityState> m_game_state;



    public:
        HiddenRoom(): m_max_num_players(2){}
        HiddenRoom(unsigned int numPlayers): m_max_num_players(numPlayers) {};
        void addPlayer(unsigned int clientId);
        void removePlayer(unsigned int clientId);
        ~HiddenRoom(){};
};