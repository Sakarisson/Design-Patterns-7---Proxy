/*
   File:        Client.cpp
*/
#include "ServerProxy.h"
#include "Client.h"

static const char BS = 8;   // Backspace

Client::Client(string name, ServerProxy *aServProxy)
:ChatObserver(name),iServProxy(aServProxy)
{ }

void Client::update(Message &mess) {
    if(mess.getSender()!= getName()) {
       cout <<BS<<BS<<BS<< mess.getSender()<< "=> "<< mess.getMessage() << endl;
       cout << "<= ";
       cout.flush();
    }
}


void Client::sendMessage(string messStr) {
    iServProxy->sendMessage(Message(getName(),messStr));
}

void Client::leave() {
   iServProxy->detach();
}


void Client::run() {  // The loop
   bool keepOn = true;
   string str;
   while(keepOn) {
       cout << "<= ";
       getline(cin,str);
       if(str=="exit")
          keepOn = false;
       else
          sendMessage(str);
   }
   leave();
}
