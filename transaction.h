#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include <iostream>
#include <string>
#include <ctime>

//XXX should everything except id be public ?
class transaction
{
    friend class account; //so only it can set our id...
    unsigned int id;
    std::string name;
    float amount;
    time_t when;
    std::string comment;
public:
    transaction() {}
    transaction(std::string name, float amount):
	name(name), amount(amount), when(time(NULL)) {}
    transaction(std::string name, float amount, time_t when):
	name(name), amount(amount), when(when) {}
    void serialize(std::ostream & os);
};

#endif //_TRANSACTION_H
