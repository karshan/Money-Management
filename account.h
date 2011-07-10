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
    std::string name;
    std::vector<transaction> transactions;
    std::vector<unsigned int> free_ids; //for transactions, XXX use stack instead ?
public:
    account(std::string name): name(name) {}

    void add_transaction(transaction t); //XXX const transaction &t ??

    //XXX use exceptions instead of bool here ?
    bool delete_transaction(unsigned int id); //XXX or delete_transaction(transaction &) ?

    //TODO: maybe a better interface for serialization ? return a char *
    //this will write a serialized form of an account to os...
    void serialize(std::ostream & os);
};

#endif //_ACCOUNT_H
