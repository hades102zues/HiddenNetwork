#include "game_server.h"

HiddenGameServer::HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients) 
: HiddenServer(ip, port, host_machine, maxClients) {
    m_game = std::make_unique<HiddenGame>(2);
};


void HiddenGameServer::run () {
    m_network->listNetDetails();
    m_isServerRunning = true;

    while (m_isServerRunning) {

        // Server Events: Connections, Disconnections. For Game Messages to game object??
        handleEvent();

        // Have a function on seperate thread that handles updating the game objects???
        m_game->update();


        // send game state to game players
    }
}

void HiddenGameServer::onConnection(ENetEvent& event) {
    // Add the connection
    int id = addConnection(event.peer);


    if (id) { 

        // Send the client a welcome message!
        const char* msgBody = "Connection accepted. Welcome to HiddenWorldServer.";
        size_t msgBodySize = (strlen(msgBody)+1) * sizeof(char);
        HiddenMessage<const char> msg(message_type::plain_text, msgBody, msgBodySize, id);
        sendMessage<HiddenMessage<const char>>(msg, event.peer);
    

        // add player to the game
        m_game->addPlayer(m_clients.at(id));


        printf("[Game Server] added player to game \n");

    }


}
void HiddenGameServer::onDisconnection(ENetEvent& event){

    
    int clientId = *((int*)event.peer->data);
    printf("[Event] ~~~ Client GUID: %d has Disconnected \n", clientId);

    // remove client from game
    m_game->removePlayer(clientId);

    // remove client from server collection
    removeConnection(clientId, event.peer);


}

void HiddenGameServer::onMessage(ENetEvent& event) {}



