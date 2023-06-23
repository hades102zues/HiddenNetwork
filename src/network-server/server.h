#pragma once
#include "../network/hidden_net.h"
#include <unordered_map>
#include <memory>


class HiddenServer {
    private:
        int m_MAX_CLIENTS;
        unsigned int m_client_id; // Unique client IDs
        unsigned int m_connectedClients; // count of connected clients
        std::unique_ptr<HiddenNet> m_network;
        bool m_isServerRunning = false;
        std::unordered_map<unsigned int, HiddenConnection> m_clients;

        
        machine m_host_machine;

        // below are removable?
        const char* m_ip;
        int m_port;
        ENetHost* m_server_host;
        
    public:
    HiddenServer(const char* ip, int port, machine host_machine, const int maxClients);
    void run();
    void handleEvent();
    void onConnection(ENetEvent& event);
    void onDisconnection(ENetEvent& event);
    void addClient(unsigned int id, ENetPeer* peer);
    HiddenConnection* findClient(unsigned int id);
    bool isClientedConnected(unsigned int id);
    // void sendMessage(HiddenMessage msg, ENetPeer* client);

    template <typename T>
    void sendMessage(T msg, ENetPeer* client) {
        // get the client's unique id
        int clientId = *((int*)client->data);

        if(isClientedConnected(clientId)){
            m_network->send<T>(msg, client);
        }  
    }

    void info();
    void listClients();
    
    ~HiddenServer();

};