#include "server.h"
#include "../network/hidden_net_common.h"
#include <string>


HiddenServer::HiddenServer(const char* ip, int port, machine host_machine, const int maxClients) {
    m_MAX_CLIENTS = maxClients;
    m_client_id = 1000;
    m_connectedClients = 0;

    m_ip = ip;
    m_port = port;
    m_host_machine = host_machine;
    m_network = std::make_unique<HiddenNet>(ip, port, host_machine);
    m_server_host = m_network->initialize();

}

void HiddenServer::run() {
    m_network->listNetDetails();
    m_isServerRunning = true;
    while (m_isServerRunning) {
        handleEvent();
        //info();
        listClients();
    }
}

void HiddenServer::handleEvent() {
    ENetEvent event;
    while(enet_host_service (m_server_host, &event, 1000) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT: 
                onConnection(event);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                onDisconnection(event);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                onMessage(event);
                enet_packet_destroy (event.packet);
                break;

            case ENET_EVENT_TYPE_NONE:
                break;

        }
    }
}


void HiddenServer::onConnection(ENetEvent& event) {

     
    // Add the connection
    int id = addConnection(event.peer);


    if (id) { 

        // Send the client a welcome message!
        const char* msgBody = "Connection accepted. Welcome to HiddenWorldServer.";
        size_t msgBodySize = (strlen(msgBody)+1) * sizeof(char);
        HiddenMessage<const char> msg(message_type::plain_text, msgBody, msgBodySize, id);
        sendMessage<HiddenMessage<const char>>(msg, event.peer);
    }
    

    // game_movement msgBody[2] = {game_movement::UP, game_movement::LEFT};
    // size_t msgBodySize = sizeof(msgBody);
    // HiddenMessage<game_movement> msg(message_type::movement,  msgBody, msgBodySize, *uniqueClientID);
    // sendMessage<HiddenMessage<game_movement>>(msg, event.peer);


    // State msgBody[2] = { State{0.1f, 0.5f}, State{1.1f, 0.5f} };
    // size_t msgBodySize = sizeof(msgBody);
    // HiddenMessage<State> msg(message_type::game_state, msgBody, msgBodySize, *uniqueClientID);
    // sendMessage< HiddenMessage<State> >(msg, event.peer);


}

void HiddenServer::onDisconnection(ENetEvent& event) {
    
    int clientId = *((int*)event.peer->data);
    printf("[Event] ~~~ Client GUID: %d has Disconnected \n", clientId);
    removeConnection(clientId, event.peer);

}

void HiddenServer::onMessage(ENetEvent &event) {
    printf("[SERVER] ~~~ Message Received\n");
}

int HiddenServer::addConnection(ENetPeer* peer) {

    // Disconnect client if server limit reached
    if(m_connectedClients >= m_MAX_CLIENTS) {
        printf("[SERVER] ~~~ Client limit reached\n");
        enet_peer_disconnect_now(peer, 0);
        return -1;
    }

    printf("[Event] ~~~ Preparing Client Connection \n");

    // get a GUID
    int* uniqueClientID = new int(m_client_id);
    m_client_id++;
    m_connectedClients++;
   
    // STore the GUID on the peer object
    peer->data = uniqueClientID;

    // Store the connection
    HiddenConnection connection(*uniqueClientID, peer);
    m_clients.emplace(*uniqueClientID, connection);

    printf("[SERVER] ~~~ Client Connected. # of Clients : %d\n", m_connectedClients);

    return *uniqueClientID;
}

void HiddenServer::removeConnection(unsigned int clientId, ENetPeer* peer) {
     //check to see if client exists
    if (findClient(clientId) == NULL) {
        return;
    }

    // remove client from list
    m_clients.erase(clientId);
    m_connectedClients--;

    // free the memory
    delete ((int*)peer->data);

    // cleanup the peer data
    m_network->destroyPeer(peer);

    printf("[SERVER] ~~~ # of Clients : %d\n", m_connectedClients);
}

HiddenConnection* HiddenServer::findClient(unsigned int id) {
    auto p = m_clients.find(id);

    if (p == m_clients.end()) {
        return NULL;
    }

    auto connection = p->second;
    
    return (&connection);

}
bool HiddenServer::isClientedConnected(unsigned int id) {

    // find the client
    auto connection_pointer = findClient(id);
    if (connection_pointer == NULL) {
        return false;
    }

    return true;
}

void HiddenServer::info() {
    printf("[SERVER] ~~~ Client Max: %d, Available Client ID: %d, # of Connected Clients: %d \n", m_MAX_CLIENTS, m_client_id, m_connectedClients);
}

void HiddenServer::listClients() {
    for (auto client : m_clients) {
        auto connection = client.second;
        auto clientId = connection.client_id;
        //auto peer = connection.peer;

        printf("Client [%d]\n", clientId);
    }
}
HiddenServer::~HiddenServer() {
    
}