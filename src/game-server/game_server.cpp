#include "game_server.h"

HiddenGameServer::HiddenGameServer(const char* ip, int port, machine host_machine, const int maxClients) 
: HiddenServer(ip, port, host_machine, maxClients) {
    m_game = std::make_unique<HiddenGame>(m_network, 2);
};


void HiddenGameServer::run () {
    m_network->listNetDetails();
    m_isServerRunning = true;

    while (m_isServerRunning) {

        // Server Events: Connections, Disconnections, Messages. Specifically forward game input to game object
        handleEvent();

        // Have a function on seperate thread that handles updating the game objects???
        m_game->run();


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
        HiddenMessage<const char> msg(message_type::connection_approved, msgBody, msgBodySize, id);
        sendMessage<HiddenMessage<const char>>(msg, event.peer);
    

        // add player to the game
        m_game->addPlayer(m_clients.at(id));

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

void HiddenGameServer::onMessage(ENetEvent& event) {

    // get the packet's data
    const auto packetData = event.packet -> data;

    // store the address of the start of the data array
    enet_uint8* index = packetData;

    // unpack the client's server id
    unsigned int clientId;
    memcpy(&clientId, index, sizeof(clientId));
    index += sizeof(clientId);

    // unpack the message type
    message_type type;
    memcpy(&type, index, sizeof(type));
    index += sizeof(type);

    // unpack the bodySize
    size_t bodySize;
    memcpy(&bodySize, index, sizeof(bodySize));
    index += sizeof(bodySize);


    // based on the message type, create the correct object to hold the data

    if (type == message_type::plain_text) {

        int length = bodySize / sizeof(char);
        char plainText[length];
        memcpy(plainText, index, bodySize);
        printf("[GAME SERVER] ~~~ Client UUID:{%d} echoed: %s\n", clientId, plainText);
    }

    if (type == message_type::movement) {

        // create a local array to hold the body
        int length = bodySize / sizeof(game_movement);
        game_movement movements[length]; 


        memcpy(movements, index, bodySize);

        m_game->handleMovement(clientId, movements[0]);

    }

}



