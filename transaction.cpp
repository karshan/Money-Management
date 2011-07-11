#include "transaction.h"

void transaction::serialize(std::ostream & os) const
{
    os.write((const char *)&id, sizeof(id));
    os.write(name.c_str(), name.size() + 1);
    os.write((const char *)&amount, sizeof(amount));
    os.write((const char *)&when, sizeof(when));
    os.write(comment.c_str(), comment.size() + 1);
}

transaction & transaction::unserialize(std::istream & is)
{
    char ch;
    is.read((char *)&id, sizeof(id));
    is >> ch;
    while (ch != '\0') {
        name.append(1, ch);
        is >> ch;
    }
    is.read((char *)&amount, sizeof(amount));
    is.read((char *)&when, sizeof(when));
    is >> ch;
    while (ch != '\0') {
        comment.append(1, ch);
        is >> ch;
    }    
    return *this;
}


