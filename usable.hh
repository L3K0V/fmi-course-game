#ifndef __USABLE_H__
#define __USABLE_H__

#include <string>

using std::string;

class Player;

class Usable {
private:
	char type_;
	string name_;
public:
	Usable(char type, string name) 
	: type_(type), name_(name) {}
	virtual ~Usable();

	char get_type() const {return type_;}
	string get_name() const {return name_;}
	virtual int get_attribute() const = 0;
	virtual void print() const = 0;

	/* Return 1 if is consumed,
	 * Return 0 if is not consumed */
	virtual int use(Player &player) = 0;
};

#endif
