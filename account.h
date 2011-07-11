#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include "transaction.h"

class account
{
    friend class bank;
    unsigned int id;
    std::vector<transaction> transactions;
    std::vector<unsigned int> free_ids; //for transactions, XXX use stack instead ?
public:
    std::string name;
    account() {}
    account(std::string name): name(name) {}

    void add_transaction(transaction t); //XXX const transaction &t ??

    bool delete_transaction(unsigned int id);

    unsigned int get_id() const { return id; }

    std::vector<transaction>::const_iterator transactions_begin() const {
        return transactions.begin();
    }
    std::vector<transaction>::const_iterator transactions_end() const {
        return transactions.end();
    }


    //TODO: maybe a better interface for serialization ? return a char *i

    //this will write a serialized form of an account to os...
    void serialize(std::ostream & os) const;
    account & unserialize(std::istream & is);
};

#endif //_ACCOUNT_H
