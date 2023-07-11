#include "network-server/server.h"
#include "network-client/client.h"
#include "game-server/game_server.h"



int main(int argc, char* argv[]) {

    //======== Base SERVER
    // HiddenServer server = HiddenServer("127.0.0.1", 3001, machine::server,5);
    //server.run();

    //======== GAME SERVER
    HiddenGameServer server("127.0.0.1", 3001, machine::server,5);
    server.run();

    //======== CLIENT
    // HiddenClient client("127.0.0.1", 3000, machine::client);
    // client.info();
    // client.connectToServer("127.0.0.1", 3001);
    // client.run();


    return 0;
}