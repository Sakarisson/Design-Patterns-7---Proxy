/*
   File:        Client.h
   Objective:   ChatClient. Attaches to and communicates with a
                ChatServer.
   Date:        2008 / Örjan Sterner
*/

#ifndef CLIENT_H
#define CLIENT_H

#include<string>
#include "ChatObserver.h"

class ServerProxy;

using namespace std;

class Client: public ChatObserver {

public:
  Client(string name, ServerProxy* aServProxy);
  ~Client() {}

  void sendMessage(string); // Send a new Mesage to server
  void leave(); // Leave the chat
  virtual void update(Message &mess); // Called by Server

  void run();  // The main loop
  
  void test() { cout << "Client test" << endl; }

private:
  ServerProxy *iServProxy;

};

#endif
