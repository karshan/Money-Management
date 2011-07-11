#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include <iostream>
#include <string>
#include <ctime>

class transaction
{
    friend class account; //so only it can set our id...
    unsigned int id;
public:
    std::string name;
    float amount;
    time_t when;
    std::string comment;
    
    transaction() {}
    
    transaction(std::string name, float amount):
        name(name), amount(amount), when(time(NULL)) {}
    
    transaction(std::string name, float amount, time_t when):
        name(name), amount(amount), when(when) {}
    
    unsigned int get_id() const { return id; }

    void serialize(std::ostream & os) const;
    transaction & unserialize(std::istream & is);
};

#endif //_TRANSACTION_H
