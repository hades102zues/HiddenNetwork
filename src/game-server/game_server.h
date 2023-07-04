#pragma once

#include "../network-server/server.h"
#include "room.h"

class HiddenGameServer : public HiddenServer {
    private:
        HiddenRoom m_game_room;
};