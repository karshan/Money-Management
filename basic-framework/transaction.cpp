#include <iostream>
#include "transaction.h"

void transaction::serialize(std::ostream & os) const
{
    os.write((const char *)&id, sizeof(id));
    os.write(name.c_str(), name.size() + 1);
    os.write((const char *)&amount, sizeof(amount));
    os.write((const char *)&when, sizeof(when));
    os.write(category.c_str(), category.size() + 1);
    os.write(comment.c_str(), comment.size() + 1);
}

transaction & transaction::unserialize(std::istream & is)
{
    char ch;
    name.clear();
    category.clear();
    comment.clear();
    is.read((char *)&id, sizeof(id));
    is.get(ch);
    while (ch != '\0') {
        name.append(1, ch);
        is.get(ch);
    }
    is.read((char *)&amount, sizeof(amount));
    is.read((char *)&when, sizeof(when));

    is.get(ch);
    while (ch != '\0') {
        category.append(1, ch);
        is.get(ch);
    }

    is.get(ch);
    while (ch != '\0') {
        comment.append(1, ch);
        is.get(ch);
    }
    return *this;
}


