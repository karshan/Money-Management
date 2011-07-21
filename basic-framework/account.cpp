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

void account::serialize(std::ostream & os) const
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

account & account::unserialize(std::istream & is)
{
    unsigned int size;
    unsigned int free_id;
    char ch;

    free_ids.clear();
    name.clear();
    transactions.clear();

    is.read((char *)&size, sizeof(size));
    for (unsigned int i = 0; i < size; i++) {
        is.read((char *)&free_id, sizeof(free_id));
        free_ids.push_back(free_id);
    }
    is.read((char *)&id, sizeof(id));
    is >> ch;
    while (ch != '\0') {
        name.append(1, ch);
        is >> ch;
    }
    is.read((char *)&size, sizeof(size));
    for (unsigned int i = 0; i < size; i++)
        transactions.push_back(transaction().unserialize(is));
    return *this;
}
