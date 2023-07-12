#include "network-server/server.h"
#include "network-client/client.h"
#include "game-server/game_server.h"
#include "game-client/game_client.h"



int main(int argc, char* argv[]) {

    //======== Base SERVER
    // HiddenServer server = HiddenServer("127.0.0.1", 3001, machine::server,5);
    //server.run();

    //======== GAME SERVER
    HiddenGameServer gameServer("127.0.0.1", 3001, machine::server,5);
    gameServer.run();

    //======== CLIENT
    // HiddenClient client("127.0.0.1", 3000, machine::client);
    // client.info();
    // client.connectToServer("127.0.0.1", 3001);
    // client.run();

    //======== GAME CLIENT
    // HiddenGameClient gameClient("127.0.0.1", 3000, machine::client);
    // gameClient.info();
    // gameClient.connectToServer("127.0.0.1", 3001);
    // gameClient.run();


    return 0;
}