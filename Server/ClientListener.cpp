/*
   File:        ChatListener.cpp
   Objective:   Listen for messages from Clients
   Last change: February 2017 / Örjan Sterner
*/

#include <thread>
#include <chrono>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>
#endif

#include "ClientListener.h"
#include "Message.h"

ClientListener::ClientListener(const Address &aListenAddr, Server *aServer)
:iListenAddr(aListenAddr),iServer(aServer)
{
  iMailbox.open(iListenAddr,ios::out|ios::trunc); // Make zero
  iMailbox.close();

  iMailbox.open(iListenAddr,ios::in); //  Open for reading
  if(!iMailbox) {
    cerr << "Could not open server mailbox: " << iListenAddr << endl;
    exit(1);
  }
}

ClientListener::~ClientListener() {
  iMailbox.close();
#if defined(_WIN32) || defined(_WIN64)
  _unlink(iListenAddr);
#else
  unlink(iListenAddr);
#endif
}

void ClientListener::listen() {
   // Polling loop
   while(true) {
	  iMailbox.clear();
      Message msg;
	  iMailbox >> msg;

      if(msg.size() == 0) { 
		//std::this_thread::sleep_for(200ms);  // C++14
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	  }
      else  {
        string sender = msg.getSender();
        string mess = msg.getMessage();

        // New Client
        if(sender=="__ATTACH__") {
        // Split message to get name and HDaddress
            int pos=mess.find('@');
            string name = mess.substr(0,pos);
            string stringAddr(mess.substr(pos+1,mess.length()-pos-1));
            HDaddress addr(stringAddr);
            ClientProxy *clp = new ClientProxy(name,addr);
            // Map address to proxy
            iClientMap[stringAddr]= clp;
            // Attach to server
            iServer->attach(clp);
        } // Attach

        // Client leave
        else if(sender=="__DETACH__") {
        // Split message to get name and HDaddress
            int pos=mess.find('@');
            string name = mess.substr(0,pos);
            string stringAddr(mess.substr(pos+1,mess.length()-pos-1));
            iServer->detach(iClientMap[stringAddr]);
            delete iClientMap[stringAddr]; // delete proxy
            iClientMap.erase(stringAddr);  // Erase from proxy map
        } // Detach

        else {  // Ordinary chat message -> dispatch to server
            iServer->addMessage(msg);
        } // Chat message
     }
   }
}

