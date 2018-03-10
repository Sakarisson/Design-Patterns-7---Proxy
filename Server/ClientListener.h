/*
   File:        ChatListener.h
   Objective:   Listen for messages from Clients
   Date:        2008 Örjan Sterner
*/

#ifndef CLIENTLISTENER_H
#define CLIENTLISTENER_H

#include <map>
#include <fstream>
#include <string>
#include "Server.h"
#include "ClientProxy.h"

using namespace std;

class ClientListener {
public:
   ClientListener(const Address &aListenAddr, Server *aServer);
   ~ClientListener();

   // A polling loop that never returns.
   // Listens for client messages,
   // unmarshalls them and take proper action
   // Creates a ClientProxy for every new Client.
   void listen();

private:
   const Address &iListenAddr; // Server's HDaddress
   Server *iServer;
   map<string,ClientProxy*> iClientMap;  // Map client's addr to proxy
   fstream iMailbox; // The server mailbox

};


#endif
