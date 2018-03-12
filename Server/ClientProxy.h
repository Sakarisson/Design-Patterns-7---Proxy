/*
ClientProxy.h
Version 2
Kristian Sakarisson
*/

#pragma once

#include "Address.h"
#include "ChatObserver.h"
#include "ClientConnection.h"

class ClientProxy : public ChatObserver {
public:
    ClientProxy(std::string, HDaddress);
    virtual ~ClientProxy() {}
    void update(const Message&) override;
private:
    HDclientConnection _connection;
};
