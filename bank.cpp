#include "bank.h"

unsigned int bank::add_account(account a)
{
    unsigned int id;
    if (free_ids.size() != 0) {
	id = free_ids.back();
	free_ids.pop_back();
    }
    else
	id = accounts.size() + 1;
    a.id = id;
    accounts.push_back(a);
    return id;
}

bool bank::delete_account(unsigned int id)
{
    for (auto it = accounts.begin();
	 it != accounts.end(); it++) {
	if ((*it).id == id) {
	    accounts.erase(it);
	    free_ids.push_back(id);
	    return true;
	}
    }
    return false;
}

account & bank::get_account(unsigned int id) throw(bad_id)
{
    for (auto it = accounts.begin();
	 it != accounts.end(); it++) {
	if ((*it).id == id) {
	    return *it;
	}
    }
    throw bad_id();
}

