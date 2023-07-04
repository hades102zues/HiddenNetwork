#include "game_server.h"

HiddenGameServer::HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients) 
: HiddenServer(ip, port, host_machine, maxClients) {};