#include "Server.h"

#include <iostream>

void Server::addMessage(Message message) {
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

}

bool Server::clientExists(ClientProxy* clientProxy) const {
    auto it = std::find(_clients.begin(), _clients.end(), clientProxy);
    return it != _clients.end();
}
