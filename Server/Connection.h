/*
   File:  	    Connection.h
   Objective:	Defines the interface for concrete Connection classes.
   Date:	    2008 / Örjan Sterner
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <fstream>
#include "Message.h"
#include "Address.h"

using std::ifstream;
using std::ofstream;

class Connection {
public:
   Connection() {}
   virtual ~Connection() {}
   virtual void connect(const Address &aPeerAddr)=0;
   virtual void disconnect()=0;
   virtual void receive(Message &aMsg)=0;
   virtual void send(const Message &aMsg)=0;
};


#endif


