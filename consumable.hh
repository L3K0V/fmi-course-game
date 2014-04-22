#ifndef __CONSUMABLE_H__
#define __CONSUMABLE_H__

#include <string>
#include <iostream>

using namespace std;

class Consumable {
private:
	char type_;
	string name_;
public:
	Consumable(char type, string name) 
	: type_(type), name_(name) {}

	char get_type() const;
	string get_name() const;
	virtual void print() const;
};

#endif