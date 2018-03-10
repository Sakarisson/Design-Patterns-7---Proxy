/*
   File:       ChatLogger.cpp
*/

#if defined(_WIN32) ||defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <ctime>
#include "ChatLogger.h"
#include "Server.h"

//-------------------------------------------------------------

ChatLogger::ChatLogger(const string &aFileName, Server *aServ)
:ChatObserver("Logger"), iFileName(aFileName),iServ(aServ)
{
   iLogFile.open(iFileName.c_str(),ios::out|ios::trunc);
   iServ->attach(this);
   time_t t;
   time(&t);
   iLogFile << "Server started at " + string(ctime(&t));
   iLogFile.flush();
}

ChatLogger::~ChatLogger() {
   time_t t;
   time(&t);
   iLogFile << "Server stoppped at " + string(ctime(&t));
   iLogFile.close();
}

void ChatLogger::update(const Message &mess) {
    iLogFile << mess.getSender()<< "> " << mess.getMessage() << endl;
}

