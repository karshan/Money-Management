#ifndef _BANK_H
#define _BANK_H

#include <string>
#include <vector>
#include "account.h"

//This is a bank in the sense there's only one for a user, the actual banks will
//be accounts within this one.
class bank
{
    std::vector<account> accounts;
    std::vector<unsigned int> free_ids; //for account, XXX use stack instead ?
public:
    unsigned int add_account(account a);

    bool delete_account(unsigned int id); //XXX or delete_account(account &) ?

    const std::vector<account> & get_accounts() const {
        return accounts;
    }

    account *get_account(unsigned int id);

    void serialize(std::ostream & os) const;
    bank & unserialize(std::istream & is); //the return is just convenience

    virtual void save() = 0;
    virtual void load() = 0;
//TODO: an interface for random access.... all the vectors are just cache's
//so basically a partial load is required for efficiency
};


#endif //_BANK_H
