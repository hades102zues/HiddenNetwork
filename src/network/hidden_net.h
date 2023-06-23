#pragma once
#include "hidden_net_common.h"
#include "hidden_net_connection.h"
#include "hidden_net_message.h"
#include <string>

class HiddenNet {

    private:
        const char* m_ip;
        int m_port;
        machine m_host_machine;
        ENetAddress m_address;
        ENetHost* m_host;

    public:
        HiddenNet(const char* ip, int port, machine host_machine);
        ENetHost* initialize();
        ENetPeer* connect(const char* remoteIp, int remotePort);
        void send(std::string msg, ENetPeer* peer);
        // void send(HiddenMessage msg, ENetPeer* peer);

        template <typename T>
        void send(T msg, ENetPeer* peer) {
            if (peer == NULL) {
                return;
            }

            //Get the size of the message data in bytes
            std::size_t bufferSize =  sizeof(msg.type) + sizeof(msg.data) + sizeof(msg.designatedClientID);

            // create and zero a byte array that can accommodate the data.
            uint8_t byteArray[bufferSize];
            memset(byteArray, 0,  bufferSize);

            //load data into byteArray; byteArray << client's server id << message type << data 
            memcpy(byteArray, &msg.designatedClientID, sizeof(msg.designatedClientID));
            memcpy(byteArray + sizeof(msg.designatedClientID), &msg.type, sizeof(msg.type));
            memcpy(byteArray + sizeof(msg.designatedClientID) + sizeof(msg.type), &msg.data, sizeof(msg.data));

            // pass buffer to packet
            ENetPacket* packet = enet_packet_create(byteArray, bufferSize, ENET_PACKET_FLAG_RELIABLE);

            // Buffer the packet to be sent to remote
            enet_peer_send(peer, 0, packet);

            // Tell host_service to handle outstanding requests
            enet_host_flush(m_host);

        }
        void destroyPeer(ENetPeer* peer);
        void listNetDetails();
        ~HiddenNet();

};