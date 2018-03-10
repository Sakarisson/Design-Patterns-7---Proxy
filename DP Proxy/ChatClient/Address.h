/*
   File:        Address.h
   Objective:   Defines the Address interface and concrete
                HDadress which implements a 'hard disk address'.

   Last change: February 2017 / Örjan Sterner
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

using std::string;

class Address {
public:
   virtual string getAddress() const = 0;
   virtual operator string() const = 0;

};

// Hard Disk address
class HDaddress : public Address {
public:
   HDaddress(string aAddr)    // Path and filename
   :iAddrStr(aAddr) {}

   virtual string getAddress() const { return iAddrStr; }
   virtual operator string() const {
         return iAddrStr; // Enables passing a HDaddress when a
                       // string is expected
   }
   
private:
	string iAddrStr;

};

#endif
