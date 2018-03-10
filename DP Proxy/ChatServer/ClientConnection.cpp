/*
  File:       ClientConnection.cpp
*/

#include <sstream>
#include <string>
//#include <dirent.h>
//#include <direct.h>

#include "ClientConnection.h"

using std::ios;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;


//---------------------------------------------------------------------------

HDclientConnection::HDclientConnection() { }

HDclientConnection::~HDclientConnection() {
   if(iRemoteMailBox.is_open())
      iRemoteMailBox.close();
}

void HDclientConnection::connect(const Address &aClientAddr) {
   // Server writes to this mailbox
   iRemoteMailBox.open(aClientAddr,ios::app);
}

void HDclientConnection::disconnect() {
   iRemoteMailBox.close();
}


void HDclientConnection::send(const Message &aMsg) {
   iRemoteMailBox << aMsg;  // Write to remote mailbox
}


