#pragma once
#include "../network/hidden_net.h"


class HiddenClient {
    protected:
        std::unique_ptr<HiddenNet> m_network;
        unsigned int m_GUID = 0;
        ENetPeer* m_server = nullptr;
        bool m_terminate = true;

        // below are removable?
        const char* m_ip;
        int m_port;
        machine m_host_machine;
        ENetHost* m_client_host;

    public:
        HiddenClient(const char* ip, int port, machine host_machine);
        virtual void run();
        void connectToServer(const char* remoteIp, int remotePort);
        void handleEvent();
        virtual void onMessage(ENetEvent& event);
        virtual void onConnection(ENetEvent& event);
        virtual void onDisconnection(ENetEvent& event);
        template <typename T>
        void sendMessage(T msg, ENetPeer* server) {
            if(m_GUID){
                m_network->send<T>(msg, server);
            }
        }
        void sendTestMessage();
        void info();
        ~HiddenClient();
};