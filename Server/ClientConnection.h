/*
  File:       ClientConnection.h
  Objective:  A connection point to a remote Client
  Date:       2008 / Örjan Sterner
*/

#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <fstream>
#include "Message.h"
#include "Address.h"
#include "Connection.h"

using std::ifstream;
using std::ofstream;


class HDclientConnection : public Connection {
// Used by server to communicate with its clients
public:
   HDclientConnection();  // Path in filesystem
   virtual ~HDclientConnection();
   virtual void connect(const Address &aClientAddr);
   virtual void disconnect();
   virtual void receive(Message &aMsg) { } // Not used
   virtual void send(const Message &aMsg);

protected:
   const Address *iClientAddr; // My path+filename
   ofstream iRemoteMailBox; // Written by server, read by client
};

#endif


