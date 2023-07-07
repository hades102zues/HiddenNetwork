#include "game_server.h"

HiddenGameServer::HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients) 
: HiddenServer(ip, port, host_machine, maxClients) {};


void HiddenGameServer::run () {}
void HiddenGameServer::handleEvent() {}
void HiddenGameServer::onConnection(ENetEvent& event) {}
void HiddenGameServer::onDisconnection(ENetEvent& event){}
void HiddenGameServer::onMessage(ENetEvent& event) {}



