#include "game_client.h"

HiddenGameClient::HiddenGameClient(const char* ip, int port, machine host_machine): HiddenClient(ip, port, host_machine) {

}

void HiddenGameClient::run() {
    while (!m_terminate) {
        handleEvent();
    }
}

void HiddenGameClient::onMessage(ENetEvent& event) {
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
        printf("[SERVER] ~~~ Client UUID:{%d}, %s\n", clientId, plainText);
    }

    if (type == message_type::connection_approved) {


        // parse the body
        int length = bodySize / sizeof(char);
        char plainText[length];
        memcpy(plainText, index, bodySize);
        printf("[SERVER] ~~~ Client UUID:{%d}, %s\n", clientId, plainText);

        // store the client's GUID
        m_GUID = clientId;

        // store the server's connection
        m_server =  event.peer;

    }

    if (type == message_type::game_state) {

        int length = bodySize / sizeof(ClientSideEntityState);
        ClientSideEntityState states[length]; 

        memcpy(states, index, bodySize);

        printf("[CLIENT] ~~~ Game State received from server: \n");
        for (auto state : states) {

            auto playerId = state.playerId;
            auto x = state.playerState.x;
            auto y = state.playerState.y;
            auto color = state.playerState.color;
            printf(" GUID %d => (%d,%d) : {%d, %d, %d, %d}\n",playerId, x, y, color.r, color.g, color.b, color.a);
        }

    }
}
