/*
Server.h
Version 2
Kristian Sakarisson
*/

#pragma once

#include <vector>

#include "ChatLogger.h"
#include "ClientProxy.h"
#include "Message.h"

class Server {
public:
    Server() {}
    ~Server();
    void addMessage(Message);
    void attach(ChatObserver*);

    void detach(ChatObserver*);
private:
    bool observerExists(ChatObserver*) const;
    size_t getObserverIndex(ChatObserver*) const;
private:
    std::vector<ChatObserver*> _observers;
};
