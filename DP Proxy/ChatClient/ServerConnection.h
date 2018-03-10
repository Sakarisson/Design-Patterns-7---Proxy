/*
    File:       ServerConnection.h
    Objective:  A connection point to a remote Server
    Date:       2017 / Örjan Sterner
*/


#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H


#include <fstream>

#include "Message.h"
#include "Address.h"
#include "Connection.h"

using std::ifstream;
using std::ofstream;

// Hard disk Connections

class HDserverConnection : public Connection {
// Used by clients to communicate with the server
public:
   HDserverConnection();  // Path in filesystem
   virtual ~HDserverConnection();
   virtual void connect(const Address &aPeerAddr);
   virtual void disconnect();
   virtual bool receive(Message &aMsg);
   virtual void send(const Message &aMsg);
   string getLocalAddress() const;

protected:
   Address* iMyAddr; // My path+filename
   ifstream iMyMailBox;  // Written to by server, read by me
   ofstream iServerMailBox; // Written to by me(and other clients),
                            // read by server
};


#endif


