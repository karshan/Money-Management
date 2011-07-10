#include <ctime>
#include "file_bank.h"

//This implements a bank whose backing store is a plain binary file. it sucks
//because there can be no random access to the file since everything is variable
//size... but then again the bank interface doesn't have a way to allow random
//access anyways :/

//Also, it could be straight forward to add random access by limiting the string
//sizes, that will allow random access to transactions within an account pretty
//easily. But the interface has to allow for it first.

//TODO: this should open the file (whose name is this->name) and then write the
//data we need. which is:
//free_ids.size()
//all the free_ids...
//accounts.size() ?? this isn't necessary we can just wait for EOF...
//then for each account:
//  free_ids.size()
//  all the free_ids...
//  account id
//  account name (null terminated)
//  transactions.size()
//  all the transactions:
//	transaction id
//	transaction name (null terminated)
//	transaction amount
//	transaction time
//	transaction comment (null terminated)	
void file_bank::save()
{
    unsigned int tmp;	//TODO: figure out a way to not use these
    float amt;		//3 useless vars...
    time_t time;
    std::fstream file;
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    file.open(name.c_str(), std::ios::out | std::ios::binary);

    tmp = free_ids.size();
    file.write((const char *)&tmp, sizeof(tmp));
    for (auto it = free_ids.begin(); it != free_ids.end(); it++) {
	tmp = *it;
	file.write((const char *)&tmp, sizeof(tmp));
	//TODO: would this work:
	//file.write((const char *)&(*it), sizeof(*it)) ??
	//or we could use operator[]... instead of using iterators
    }
    tmp = accounts.size();
    file.write((const char *)&tmp, sizeof(tmp));
    for (auto i = accounts.begin(); i != accounts.end(); i++)
	(*i).serialize(file);

    file.close();
}

//TODO: this should read in the data from the file... which is in the format
//as above...
void file_bank::load()
{

}
