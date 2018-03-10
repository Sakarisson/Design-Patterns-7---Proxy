//---------------------------------------------------------------------------

#ifndef CHATOBSERVER_H
#define CHATOBSERVER_H

#include<string>

#include "Message.h"
using namespace std;

class ChatObserver {
public:
   ChatObserver(string name)
   :myName(name)  { }

   virtual ~ChatObserver() {}

   virtual void update(const Message &mess)=0;

   string getName() { return myName; }

private:
   string myName;

};


#endif
