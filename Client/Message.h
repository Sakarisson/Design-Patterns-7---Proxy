/*
  File:       Message.h
  Objective:  A wrapper class for a chat message
  Date:       2008 / Örjan Sterner
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::endl;

const char STX = 2; // Delimiter

class Message {  // A chat message
public:
   Message()
   :iSize(0)
   { }

   Message(string s, string m)
   :sender(s),mess(m)
   {
	   iSize = sender.size()+mess.size();
   }

   string getSender() const {
      return sender;
   }

   string getMessage() const {
      return mess;
   }

   int size() const {
	   return iSize;
   }

protected:
   string mess, sender;
   int iSize;
};


ostream& operator<<(ostream &aStrm, const Message &aMsg);

istream& operator>>(istream &aStrm, Message &aMsg);

#endif
