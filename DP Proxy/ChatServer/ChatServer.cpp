/*
   File:        ChatServer.cpp
   Objective:   Main program for the chat server
   Last change: March 2014 / orjste
*/

#include<list>
#include<string>
#include<fstream>
#include<iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif

#include "ClientProxy.h"
#include "ChatLogger.h"
#include "ClientListener.h"

using namespace std;


int main()
{

	char buff[200];

#if defined(_WIN32) || defined(_WIN64)
    char delim ='\\';
    _getcwd(buff,200);  // Current directory
#else
	char delim = '/';
	getcwd(buff,200);  // Current directory
#endif


    string addrStr(string(buff)+delim+string("serv.mb"));

    HDaddress address(addrStr);
    Server *serv = new Server;
    ChatLogger logger("ChatServer.log",serv);
	cout << "Server at " << addrStr << endl;
    ClientListener listener(address,serv);

	try {
		// listen runs the server main loop forever
		listener.listen();
	}
	catch (exception &eo) {
		cerr << eo.what() << endl;
	}
    // We will never get here.
    return 0;
}

