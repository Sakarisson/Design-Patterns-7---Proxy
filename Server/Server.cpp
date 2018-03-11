/*
Server.cpp
Version 1
Kristian Sakarisson
*/

#include "Server.h"

#include <iostream>

Server::~Server() {
    delete _chatLogger;
}

void Server::addMessage(Message message) {
    if (_chatLogger == nullptr) {
        return;
    }
    _chatLogger->update(message);
    for (auto client : _clients) {
        client->send(message);
    }
    std::cout << message << std::endl;
}

void Server::attach(ChatLogger* chatLogger) {
    if (_chatLogger != nullptr) {
        delete _chatLogger;
    }
    _chatLogger = chatLogger;
}

void Server::attach(ClientProxy* clientProxy) {
    if (!this->clientExists(clientProxy)) {
        _clients.push_back(clientProxy);
    }
}

void Server::detach(ClientProxy* clientProxy) {
    size_t index = this->getClientIndex(clientProxy);
    if (index >= 0) {
        _clients.erase(_clients.begin() + index);
    }
}

bool Server::clientExists(ClientProxy* clientProxy) const {
    auto it = std::find(_clients.begin(), _clients.end(), clientProxy);
    return it != _clients.end();
}

size_t Server::getClientIndex(ClientProxy* clientProxy) const {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (clientProxy == _clients[i]) {
            return i;
        }
    }
    return -1;
}
