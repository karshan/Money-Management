#include <ctime>
#include "account.h"

void account::add_transaction(transaction t)
{
    unsigned int id;
    if (free_ids.size() != 0) {
	id = free_ids.back();
	free_ids.pop_back();
    }
    else
	id = transactions.size() + 1;
    t.id = id;
    transactions.push_back(t);
}

bool account::delete_transaction(unsigned int id)
{
    for (auto it = transactions.begin();
	 it != transactions.end(); it++) {
	if ((*it).id == id) {
	    transactions.erase(it);
	    free_ids.push_back(id);
	    return true;
	}
    }
    return false;
}

void account::serialize(std::ostream & os)
{
    unsigned int tmp;
    tmp = free_ids.size();
    os.write((const char *)&tmp, sizeof(tmp));
    for (auto j = free_ids.begin(); j != free_ids.end(); j++) {
	tmp = *j;
	os.write((const char *)&tmp, sizeof(tmp));
    }
    os.write((const char *)&id, sizeof(id));
    os.write(name.c_str(), name.size() + 1);
    tmp = transactions.size();
    os.write((const char *)&tmp, sizeof(tmp));
    for (auto j = transactions.begin(); j != transactions.end(); j++)
	(*j).serialize(os);
}
