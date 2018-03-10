/*
   File:       ChatClient.cpp
   Objective:  ChatClient main
   Date:       2016 / Örjan Sterner
*/

#include <cstdlib>
#include "Address.h"
#include "ServerProxy.h"
#include "Client.h"
#include <stdexcept>

int main(int argc, char* argv[])
{
    if(argc!=3) {
      cout << "Usage: " << "ChatClient user server-address" << endl;
      exit(1);
    }
    string serverMBpath(argv[2]);
    
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
   // Fix the path if neccessary
     // Delete trailing \ if any
    int pos=serverMBpath.find_last_of('\\');
    if(pos==serverMBpath.size()-1)
       serverMBpath.erase(pos,1);
     // Replace single \ med \\ in path
    pos=0;
    while(pos != string::npos) {
       pos = serverMBpath.find('\\',pos);
       if(pos != string::npos) {
          serverMBpath.insert(pos,1,'\\');
          pos+=2;
       }
    }
#endif
try {

    HDaddress servAddr(serverMBpath); 
    ServerProxy *servProxy = new ServerProxy(servAddr);
    Client *me = new Client(argv[1],servProxy); 
    servProxy->attach(me); 
    me->run();  // Client loop
    delete me;
    delete servProxy;
 }
catch(exception &eo) {
	std::cout << eo.what() << std::endl;
} 
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
    system("pause");
 #endif
    return 0;
}

