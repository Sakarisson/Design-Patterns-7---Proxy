/*
    File:       ServerConnection.cpp

*/

#include <sstream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif
#include <thread>
#include "ServerConnection.h"

using std::ios;
using std::string;
using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::thread;
//---------------------------------------------------------------------------

HDserverConnection::HDserverConnection() {
    char cwd[200];
    char delim;

#if defined(_WIN32) || defined(_WIN64)
    delim = '\\';
     _getcwd(cwd,200);
#else
    delim = '/';
    getcwd(cwd,200);
#endif

    stringstream ss;
    // Use the unique numerical thread-id to name the mailbox
#if defined(_WIN32) || defined(_WIN64)
    ss << cwd << delim << GetCurrentThreadId() << ".mb";
#else
    ss << cwd << delim << getpid() << ".mb";
#endif
    iMyAddr = new HDaddress(ss.str());
}

HDserverConnection::~HDserverConnection() {
   delete iMyAddr;
   if(iMyMailBox.is_open())
      iMyMailBox.close();
   if(iServerMailBox.is_open())
      iServerMailBox.close();
}

void HDserverConnection::connect(const Address &aPeerAddr) {
   ofstream tmp(*iMyAddr);   // Create my mailbox file...
   tmp.close(); //...and close it.
   iMyMailBox.open(*iMyAddr,ios::in); // Open it again for reading
   if(!iMyMailBox.is_open())
     cerr << "ServerConnection error on opening my mailbox" << endl;
   iServerMailBox.open(aPeerAddr,ios::app); // We will write to this mailbox
   if(!iServerMailBox.is_open())
     cerr << "ServerConnection error on opening server mailbox" << endl;
}

void HDserverConnection::disconnect() {
   iMyMailBox.close();
   iServerMailBox.close();
}

bool HDserverConnection::receive(Message &aMsg) {
   // Check for a new message
   // If message read into aMsg return true, else false 

	Message msg;
	iMyMailBox.clear();
	iMyMailBox >> msg;
 
	if(msg.size()==0) 
		return false;
	
	aMsg = msg;
	return true;
}
		  

void HDserverConnection::send(const Message &aMsg) {
   iServerMailBox << aMsg;  // Write to remote mailbox
}

string HDserverConnection::getLocalAddress() const {
   return *iMyAddr;
}



