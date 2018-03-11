#pragma once

#include <vector>

#include "ChatLogger.h"
#include "ClientProxy.h"
#include "Message.h"

class Server {
public:
    Server() {}
    ~Server() {}
    void addMessage(Message);
    void attach(ChatLogger*);
    void attach(ClientProxy*);

    void detach(ClientProxy*);
private:
    bool clientExists(ClientProxy*) const;
    size_t getClientIndex(ClientProxy*) const;
private:
    ChatLogger* _chatLogger;
    std::vector<ClientProxy*> _clients;
};
