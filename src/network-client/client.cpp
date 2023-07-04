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

    //enet_uint8* index = 0;

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


    if (type == message_type::movement) {

        // create a local array to hold the body
        int length = bodySize / sizeof(game_movement);
        game_movement movements[length]; 


        memcpy(movements, index, bodySize);
        index += bodySize;


        for (auto movement : movements) {
            printf("[Client] ~~~ UUID:{%d}, Message Type:{%d}, Movement Input:{%d}\n", clientId, type, movement);
        }

    }

    if (type == message_type::game_state) {

        int length = bodySize / sizeof(State);
        State states[length]; 

        memcpy(states, index, bodySize);
        index += bodySize;

        for (auto state : states) {
            printf("X: %f, Y: %f \n", state.x, state.y);
        }

    }
    

}

void HiddenClient::info() {
    m_network->listNetDetails();
}

HiddenClient::~HiddenClient() {
}