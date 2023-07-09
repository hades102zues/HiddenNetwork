#include "game_server.h"

HiddenGameServer::HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients) 
: HiddenServer(ip, port, host_machine, maxClients) {};


void HiddenGameServer::run () {
    while (m_isServerRunning) {

        // Connections, Disconnections, Applying messages to Game
        handleEvent();

        // simulate the game

        // send game state to game players
    }
}
void HiddenGameServer::handleEvent() {}
void HiddenGameServer::onConnection(ENetEvent& event) {}
void HiddenGameServer::onDisconnection(ENetEvent& event){}
void HiddenGameServer::onMessage(ENetEvent& event) {}



