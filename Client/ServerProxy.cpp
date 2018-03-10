/*
   File:       ServerProxy.h
   Date: February 2017
*/

#include "ServerProxy.h"
#include "Address.h"


// ChatServerProxy

ServerProxy::ServerProxy(const Address &aServAddr)
{
   iServCon = new HDserverConnection;
   iServCon->connect(aServAddr);
   iThreadKeepOn = true;
}


ServerProxy::~ServerProxy() {
	delete iServCon;
}

bool ServerProxy::canContinue() const {
    return iThreadKeepOn;
}


void ServerProxy::attach(Client *aClient) {
   iClient = aClient;
   string myAddress {iServCon->getLocalAddress()};
   iServCon->send(Message("__ATTACH__",iClient->getName() + "@" + myAddress));
   ServerProxy::ProxyPoller proxyPoller(this, iServCon, iClient);  // Reads msgs from server and updates client
  
   // Start polling thread
   iProxyPollerThread = thread(&ServerProxy::ProxyPoller::handleUpdates,proxyPoller);
}

void ServerProxy::detach() {
   string myAddress {iServCon->getLocalAddress()};
   iServCon->send(Message("__DETACH__",iClient->getName() + "@" + myAddress));
   iThreadKeepOn.store(false);  // Stop reader thread
   
   if(iProxyPollerThread.joinable())
	iProxyPollerThread.join();
   else
	throw(std::runtime_error("ServerProxy::detach: Couldn't join iProxyPollerThread"));
}

void ServerProxy::sendMessage(const Message &aMess) {
   iServCon->send(aMess);
}


