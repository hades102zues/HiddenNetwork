#pragma once
#include <vector>


struct RGBA{
    int r;
    int g;
    int b;
    int a;
};
struct EntityState {
    int x;
    int y;
    RGBA color;
};


class HiddenRoom {
    private:
        unsigned int m_room_id;
        std::vector<unsigned int> m_players;
        std::vector<EntityState> m_game_state;
        unsigned int m_max_num_players;



    public:
        HiddenRoom(){};
        ~HiddenRoom(){};
};