/*
  File:       Message.cpp
  Date:       2008 / Örjan Sterner
*/

#include "Message.h"

ostream& operator<<(ostream &aStrm, const Message &aMsg) {
   aStrm << aMsg.getSender() << STX << aMsg.getMessage() << endl;
   return aStrm;
}

istream& operator>>(istream &aStrm, Message &aMsg) {

   string buff;
   getline(aStrm, buff);

   int pos = buff.find(STX);
   string sender = buff.substr(0,pos);
   string msg = buff.substr(pos+1,buff.length()-pos-1);
   aMsg = Message(sender,msg);
   return aStrm;
}


