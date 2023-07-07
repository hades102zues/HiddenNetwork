#include "hidden_net.h"
#include <stdio.h>
#include <cstring>



HiddenNet::HiddenNet(const char* ip, int port, machine host_machine) {
    m_ip = ip;
    m_port = port;
    m_host_machine = host_machine;
}
ENetHost* HiddenNet::initialize() {

    if (enet_initialize () != 0)
    {
        printf ("[Failed] ~~~ Error occurred while initializing ENet.\n");
        exit(EXIT_FAILURE);
    }
    
    const char* host_machine = m_host_machine == machine::server ? "server" : "client";

    printf("[Initializing] ~~~ %s network\n", host_machine);

    enet_address_set_host(&m_address, m_ip);
    m_address.port = m_port;
    m_host = enet_host_create(&m_address, 32, 2, 0, 0);

    
    if (m_host == NULL) {
        printf("[Failed] ~~~ To create Enet Host: %s \n", host_machine);
        exit(EXIT_FAILURE);
    }
    printf("[Succeeded] ~~~ Created Enet Host: %s \n", host_machine);
    return m_host;

}

// Connect to a remote Peer
ENetPeer* HiddenNet::connect(const char* remoteIp = "127.0.0.1", int remotePort = 3001) {
    ENetAddress remoteAddress;
    ENetEvent event;
    ENetPeer *peer;

    enet_address_set_host(&remoteAddress, remoteIp);
    remoteAddress.port = remotePort;

    // connect host machine to remote machine (peer)
    peer = enet_host_connect(m_host, &remoteAddress, 2, 0);

    if (peer == NULL) {
        printf("[Failed] ~~~ To connect to remote machine: %s::%d \n", remoteIp, remotePort);
    }

    printf("[Retrying] ~~~ -5 seconds-\n");

    if (enet_host_service (m_host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        printf("[Succeeded] ~~~ Connected to remote machine: %s::%d \n", remoteIp, remotePort);

        // ENet will only trigger a connection event at the peer only
        // after the host has sent its first packet. Don't ask why.
        // The below packet's only purpose is to trigger the onConnection case at the server and nothing more.

        std::string msg = "Dumb packet";
        send(msg, peer);


    } else {
        enet_peer_reset (peer);
        printf("[Failed] ~~~ Remote machine unavailable \n");
    }


    return peer;

}

void HiddenNet::send(std::string msg, ENetPeer* peer) {
    
    // will not send to disconnected clients
    if (peer == NULL) {
        return;
    }
    const char* c_msg = msg.c_str();
    ENetPacket* packet = enet_packet_create(c_msg, strlen(c_msg), ENET_PACKET_FLAG_RELIABLE);
    // Buffer the packet to be sent to remote
    enet_peer_send(peer, 0, packet);

    // Tell host_service to handle outstanding requests
    enet_host_flush(m_host);
}



void HiddenNet::destroyPeer(ENetPeer* peer) {
    enet_peer_reset(peer);
}

void HiddenNet::listNetDetails() {
    const char* host_machine = m_host_machine == machine::server ? "[SERVER]" : "[CLIENT]";
    printf("%s ~~~ IP: %s, PORT: %d\n", host_machine, m_ip, m_port);
}

HiddenNet::~HiddenNet() {
    enet_host_destroy(m_host);
}


