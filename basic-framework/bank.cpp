#include <iostream>
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
    for (std::vector<account>::iterator it = accounts.begin();
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
    for (std::vector<account>::iterator it = accounts.begin();
        it != accounts.end(); it++) {
        if ((*it).id == id) {
            return *it;
        }
    }
    throw bad_id();
}

void bank::serialize(std::ostream & os) const
{
    unsigned int tmp;
    tmp = free_ids.size();
    os.write((const char *)&tmp, sizeof(tmp));
    for (std::vector<unsigned int>::const_iterator it = free_ids.begin(); it != free_ids.end(); it++) {
        tmp = *it;
        os.write((const char *)&tmp, sizeof(tmp));
        //TODO: would this work:
        //os.write((const char *)&(*it), sizeof(*it)) ??
        //or we could use operator[]... instead of using iterators
    }
    tmp = accounts.size();
    os.write((const char *)&tmp, sizeof(tmp));
    for (std::vector<account>::const_iterator i = accounts.begin(); i != accounts.end(); i++)
        (*i).serialize(os);
}

bank & bank::unserialize(std::istream & is)
{
    unsigned int size;
    unsigned int id;

    free_ids.clear();
    accounts.clear();

    is.read((char *)&size, sizeof(size));
    for (unsigned int i = 0; i < size; i++) {
        is.read((char *)&id, sizeof(id));
        free_ids.push_back(id);
    }
    is.read((char *)&size, sizeof(size));
    for (unsigned int i = 0; i < size; i++)
        accounts.push_back(account().unserialize(is));
    return *this;
}
