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

void HiddenClient::onMessage(ENetEvent& event) {
    printf("[CLIENT] ~~~ Message from server received.\n");
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
        printf("[Server] ~~~ Client UUID:{%d}, %s\n", clientId, plainText);
    }

    if (type == message_type::connection_approved) {

        // parse the body
        int length = bodySize / sizeof(char);
        char plainText[length];
        memcpy(plainText, index, bodySize);
        printf("[Server] ~~~ Client UUID:{%d}, %s\n", clientId, plainText);

        // store the client's GUID
        m_GUID = clientId;

        // store the server's connection
        m_server =  event.peer;
    }

    if (type == message_type::game_state) {

        int length = bodySize / sizeof(State);
        State states[length]; 

        memcpy(states, index, bodySize);


        for (auto state : states) {
            printf("X: %f, Y: %f \n", state.x, state.y);
        }

    }
    

}


void HiddenClient::onConnection(ENetEvent& event) {
    printf("[CLIENT] ~~~ Connection to Server Established.\n");
}

void HiddenClient::onDisconnection(ENetEvent& event) {
    printf("[CLIENT DISCONNECTED FROM SERVER]\n");
    m_GUID = 0;
    m_server = nullptr;
}

void HiddenClient::sendTestMessage() {
    game_movement msgBody[1] = {game_movement::UP};
    size_t msgBodySize = sizeof(msgBody);
    HiddenMessage<game_movement> msg(message_type::movement,  msgBody, msgBodySize, m_GUID);
    sendMessage<HiddenMessage<game_movement>>(msg, m_server);
}

void HiddenClient::info() {
    m_network->listNetDetails();
}

HiddenClient::~HiddenClient() {
}