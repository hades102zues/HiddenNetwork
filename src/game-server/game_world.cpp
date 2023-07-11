#include "game_world.h"


HiddenGame::HiddenGame(int playerLimit) : m_max_players(playerLimit) {

}

void HiddenGame::update() {
    genPlayerList();
    genGameState();
}

void HiddenGame::addPlayer(const HiddenConnection& conn) {

    // Technically this doesn't make sense because a reconnected client gets a new GUID
    if(!findPlayer(conn.getClientId())) {
        
        // add the player to the playerList
        m_players.emplace(conn.getClientId(), conn.getPeer());

        // new entity state is generated for the player
        EntityState state = {0, 0, RGBA{135, 60, 190, 255}};
        m_gameState.emplace(conn.getClientId(), state);
    }
    

    // send game state to client
}

void HiddenGame::removePlayer(unsigned int clientId) {
    
    // check if player in the list and remove
    if (findPlayer(clientId)) {
        m_players.erase(clientId);
        m_gameState.erase(clientId);

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