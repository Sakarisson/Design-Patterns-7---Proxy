/*
   File:       ServerProxy.h
   Objective:  Used by Client, acts as a proxy for a remote server.
               Writing: sendMessage sends a Message to the server
               Reading: A separate thread is used for polling. The client
               is updated when a new Message is read.
   Date:       2017 / Örjan Sterner
*/

#ifndef SERVERPROXY_H
#define SERVERPROXY_H

#include <list>
#include <thread>
#include <chrono>
#include <atomic>
#include "Address.h"
#include "Client.h"
#include "ServerConnection.h"


using std::list;
using std::thread;
using std::atomic_bool;
//using namespace std::chrono_literals; // C++14

class Subject {

public:
  virtual ~Subject() { }
  virtual void attach(Client*)=0;
  virtual void detach()=0;

};

class ServerProxy : public Subject {
public:
    ServerProxy(const Address &aServAddr);
    virtual ~ServerProxy();

    //  Client ==> To Server
    virtual void attach(Client*); // Triggers notify on server
    virtual void detach(); // Triggers notify on server
    virtual void sendMessage(const Message &mess); // Triggers notify on server
    bool canContinue() const;
    
private:
    
	/* Thread work: poll server proxy for updates ----------------------*/
	class ProxyPoller {

	public:
		ProxyPoller(ServerProxy *proxy, HDserverConnection *servCon, Client* client)
			:iProxy(proxy), iServCon(servCon), iClient(client)
		{}

		void handleUpdates() {
			Message msg;
			do {
				if (iServCon->receive(msg))
					iClient->update(msg);
				else
					//std::this_thread::sleep_for(200ms);  // C++14
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
			} while(iProxy->canContinue());
		}

	private:
		ServerProxy* iProxy;
		HDserverConnection* iServCon;
		Client* iClient;
	};
	/* End polling thread ----------------------------------------------------*/
	
private:
	HDserverConnection *iServCon;
	Client *iClient;
	thread iProxyPollerThread;  // polling thread
	atomic_bool iThreadKeepOn;
};

#endif
