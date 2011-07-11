#ifndef _BANK_H
#define _BANK_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "account.h"

class bad_id : public std::exception
{
public:
    virtual const char * what() const throw()
    {
        return "no such account";
    }
};

//This is a bank in the sense there's only one for a user, the actual banks will
//be accounts within this one.
class bank
{
    std::vector<account> accounts;
    std::vector<unsigned int> free_ids; //for account, XXX use stack instead ?
public:
    unsigned int add_account(account a);
    
    //XXX use exceptions instead of bool here ?
    bool delete_account(unsigned int id); //XXX or delete_account(account &) ?

    std::vector<account>::const_iterator accounts_begin() const {
        return accounts.begin();
    }
    
    std::vector<account>::const_iterator accounts_end() const {
        return accounts.end();
    }

    account & get_account(unsigned int id) throw(bad_id);

    void serialize(std::ostream & os) const;
    bank & unserialize(std::istream & is); //the return is just convenience

    virtual void save() = 0;
    virtual void load() = 0;
//TODO: an interface for random access.... all the vectors are just cache's
//so basically a partial load is required for efficiency
};


#endif //_BANK_H
