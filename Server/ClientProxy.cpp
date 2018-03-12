/*
ClientProxy.cpp
Version 2
Kristian Sakarisson
*/

#include "ClientProxy.h"

ClientProxy::ClientProxy(std::string clientName, HDaddress address) : ChatObserver(clientName) {
    _connection.connect(address);
}

void ClientProxy::update(const Message& message) {
    _connection.send(message);
}
