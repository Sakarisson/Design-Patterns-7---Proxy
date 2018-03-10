#pragma once

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
};
