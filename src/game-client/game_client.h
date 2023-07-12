#pragma once

#include "../network-client/client.h"


class HiddenGameClient : public HiddenClient{

    public:
        HiddenGameClient(const char* ip, int port, machine host_machine);
        void run() override;
        void onMessage(ENetEvent& event) override;
        ~HiddenGameClient() = default;
};


