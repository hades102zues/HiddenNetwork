#include "network-server/server.h"
#include "network-client/client.h"



int main(int argc, char* argv[]) {

    //======== SERVER
    HiddenServer server = HiddenServer("127.0.0.1", 3001, machine::server,5);
    server.run();

    //======== CLIENT
    // HiddenClient client = HiddenClient("127.0.0.1", 3000, machine::client);
    // client.info();
    // client.connectToServer("127.0.0.1", 3001);
    // client.handleEvent();


    return 0;
}