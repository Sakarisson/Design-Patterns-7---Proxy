/*
ClientProxy.cpp
Version 1
Kristian Sakarisson
*/

#include "ClientProxy.h"

ClientProxy::ClientProxy(std::string clientName, HDaddress address) {
    this->connect(address);
}
