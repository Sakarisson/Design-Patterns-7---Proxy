/*
Server.cpp
Version 2
Kristian Sakarisson
*/

#include "Server.h"

#include <iostream>

Server::~Server() {
    for (std::vector<ChatObserver*>::iterator it = _observers.begin(); it != _observers.end(); ++it) {
        delete (*it);
    }
    _observers.clear();
}

void Server::addMessage(Message message) {
    for (auto observer : _observers) {
        observer->update(message);
    }
    std::cout << message << std::endl;
}

void Server::attach(ChatObserver* observer) {
    if (!this->observerExists(observer)) {
        _observers.push_back(observer);
    }
}

void Server::detach(ChatObserver* observer) {
    size_t index = this->getObserverIndex(observer);
    if (index >= 0) {
        _observers.erase(_observers.begin() + index);
    }
}

bool Server::observerExists(ChatObserver* observer) const {
    auto it = std::find(_observers.begin(), _observers.end(), observer);
    return it != _observers.end();
}

size_t Server::getObserverIndex(ChatObserver* observer) const {
    for (size_t i = 0; i < _observers.size(); i++) {
        if (observer == _observers[i]) {
            return i;
        }
    }
    return -1;
}
