#pragma once 


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

struct ClientSideEntityState{
    unsigned int playerId;
    EntityState playerState;
};