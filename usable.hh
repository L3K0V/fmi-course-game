#ifndef __USABLE_H__
#define __USABLE_H__

#include <string>
#include <iostream>

using namespace std;

class Usable {
private:
	char type_;
	string name_;
public:
	Usable(char type, string name) 
	: type_(type), name_(name) {}

	char get_type() const;
	string get_name() const;
	virtual void print() const;
};

#endif