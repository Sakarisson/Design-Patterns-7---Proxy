/*
   File:        Address.h
   Objective:   Defines the Address interface and concrete
                HDadress which implements a 'hard disk address'.

   Date:        2016 / Örjan Sterner
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

using std::string;

class Address {
public:
   virtual string getAddress() const = 0;
   virtual operator const char*() const = 0;

};

// Hard Disk address
class HDaddress : public Address {
public:
   HDaddress(string aAddr)    // Path and filename
   :iAddr(aAddr) {}

   virtual string getAddress() const { return iAddr; }

   virtual operator const char*() const {
         return iAddr.c_str();  // Enables passing a HDaddress when a
                                // C-string is expected
   }

private:
	string iAddr;

};

#endif
