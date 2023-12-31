#pragma once

#include <enet/enet.h>
#include <vector>
#include "../game-server/game_state.h"

enum class machine : unsigned int {
    server,
    client
};

enum class game_movement : unsigned int {
    UP=1001,
    DOWN,
    RIGHT,
    LEFT
};

enum class message_type : unsigned int {
    movement = 9001,
    plain_text,
    game_state,
    connection_approved
};

