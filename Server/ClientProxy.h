#pragma once

#include "Address.h"
#include "ClientConnection.h"

class ClientProxy : public HDclientConnection {
public:
    ClientProxy(std::string, HDaddress);
    virtual ~ClientProxy() {}
};
