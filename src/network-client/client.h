#pragma once
#include "../network/hidden_net.h"


class HiddenClient {
    private:
        std::unique_ptr<HiddenNet> m_network;

        // below are removable?
        const char* m_ip;
        int m_port;
        machine m_host_machine;
        ENetHost* m_client_host;

    public:
        HiddenClient(const char* ip, int port, machine host_machine);
        void connectToServer(const char* remoteIp, int remotePort);
        void handleEvent();
        void onMessage(ENetEvent& event);
        void info();
        ~HiddenClient();
};