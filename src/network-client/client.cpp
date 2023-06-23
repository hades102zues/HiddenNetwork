#include "client.h"


HiddenClient::HiddenClient(const char* ip, int port, machine host_machine) {
    m_ip = ip;
    m_port = port;
    m_host_machine = host_machine;
    m_network = std::make_unique<HiddenNet>(ip, port, host_machine);
    m_client_host = m_network->initialize();
}

void HiddenClient::connectToServer(const char* remoteIp, int remotePort) {
    m_network->connect(remoteIp, remotePort);
}

void HiddenClient::handleEvent() {
    ENetEvent event;
    while(enet_host_service (m_client_host, &event, 1000) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT: 
                printf("[Server Connected]\n");
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("[Server Disconneted]\n");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf("[Server Message Received]\n");
                onMessage(event);
                enet_packet_destroy (event.packet);
                break;
            case ENET_EVENT_TYPE_NONE:
                break;

        }
    }
}

void HiddenClient::onMessage(ENetEvent& event) {

    // get the packet
    const auto& packetData = event.packet -> data;

    // unpack the client's server id
    unsigned int clientId;
    memcpy(&clientId, packetData, sizeof(unsigned int));

    // unpack the message type
    message_type type;
    memcpy(&type, packetData + sizeof(clientId), sizeof(message_type));

    // based on the message type, create the correct object to hold the data
    if (type == message_type::movement) {
        game_movement movement;
        memcpy(&movement, packetData + sizeof(clientId) + sizeof(type), sizeof(game_movement));
        printf("[Client] ~~~ UUID:{%d}, Message Type:{%d}, Movement Input:{%d}\n", clientId, type, movement);

        // Call handler
    }
    

}

void HiddenClient::info() {
    m_network->listNetDetails();
}

HiddenClient::~HiddenClient() {
}