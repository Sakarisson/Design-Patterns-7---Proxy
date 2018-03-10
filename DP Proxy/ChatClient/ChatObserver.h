/*
   File:        ChatObserver.h
   Objective:   Observer part of DP Observer

   Date:        2008 / Örjan Sterner
*/

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

   // Update new message
   virtual void update(Message &mess)=0;

   string getName() { return myName; }

private:
   string myName;

};


#endif
