#include "game_world.h"



HiddenGame::HiddenGame(const std::unique_ptr<HiddenNet>& net, int playerLimit) : m_network(net), m_max_players(playerLimit) {

}
void HiddenGame::run() {
    // setup
    // handling input
    update();
    sendState();

}
void HiddenGame::update() {
    //genPlayerList();
    //genGameState();
}

void HiddenGame::handleMovement(unsigned int clientId, game_movement val) {

    printf("[GAME] ~~~ Player UUID:{%d}, Movement Message Input:{%d}\n", clientId, val);
    

    // apply the movement to client state
    if(findPlayer(clientId)) {
        auto& playerState = m_gameState.at(clientId);

        if (val == game_movement::UP) {
            playerState.y -= m_playerMoveSpeed; // * m_dt;
        }
        if (val == game_movement::RIGHT) {
            playerState.x += m_playerMoveSpeed; // * m_dt;
        }
        if (val == game_movement::DOWN) {
            playerState.y += m_playerMoveSpeed; // * m_dt;
        }
        if (val == game_movement::LEFT) {
            playerState.x -= m_playerMoveSpeed; // * m_dt;
        }

    }

}

void HiddenGame::sendState() {
    // Prep a buffer to hold the data
    std::vector<ClientSideEntityState> transState;
    
    // copy into the buffer
    for (auto it : m_gameState) {
        unsigned int id = it.first;
        EntityState state = it.second;
        ClientSideEntityState clientSideState = {id, state};
        transState.push_back(clientSideState);
    }

    // send the data to every player
    for (auto it : m_players) {
        unsigned int id = it.first;
        ENetPeer* player = it.second;

        auto* body = &transState[0];
        size_t bodySize = transState.size() * sizeof(ClientSideEntityState);
        HiddenMessage<ClientSideEntityState> msg(message_type::game_state, body, bodySize, id);
        m_network->send<HiddenMessage<ClientSideEntityState>>(msg, player);
    }

}
void HiddenGame::addPlayer(const HiddenConnection& conn) {

    // In general I don't think I have encountered a single game that 
    // you can disconnect from, later rejoin and be where you left off.
    // The Exception would be MMORPGs but then there is probably a decision on what data shoudl
    // persist and what shouldn't. And upon disconnection the pieces that should persist would be
    // store in some db and mapped to  the user's account.

    if(!findPlayer(conn.getClientId()) && m_playerCount < m_max_players) { // Technically never necessary.
        
        // add the player to the playerList
        m_players.emplace(conn.getClientId(), conn.getPeer());

        // new entity state is generated for the player
        EntityState state = {0, 0, RGBA{135, 60, 190, 255}};
        m_gameState.emplace(conn.getClientId(), state);

        m_playerCount++;

        printf("[GAME] ~~~ Added Player GUID %d to game \n", conn.getClientId());
    }
    

    // send game state to client
}

void HiddenGame::removePlayer(unsigned int clientId) {
    
    // check if player in the list and remove
    if (findPlayer(clientId)) {
        m_players.erase(clientId);
        m_gameState.erase(clientId);
        m_playerCount--;

        // For now we leave the client's game state and allow them to continue from where they left off
    }

    

    printf("[GAME] ~~~ GUID Player: %d has been removed from game \n", clientId);
}

 ENetPeer* HiddenGame::findPlayer(unsigned int clientId) {

    // find player
    auto p = m_players.find(clientId);

    if (p == m_players.end()) {
        return nullptr;
    }
    return p->second;
}
void HiddenGame::genPlayerList() {
    //printf("[GAME] ~~~ generating player list\n");

    for(auto p: m_players) {
        printf("[GAME] ~~~ GUID Player: %d in game\n", p.first);
    }
}
void HiddenGame::genGameState() {
    //printf("[GAME] ~~~ generating player state\n");

    for(auto p: m_gameState) {

        auto id = p.first;
        auto state = p.second;


        printf("[GAME] ~~~ GUID Player: %d; Position (%d, %d)\n", id, state.x, state.y);
    }
}
HiddenGame::~HiddenGame() {

}