#include "transaction.h"

void transaction::serialize(std::ostream & os)
{
    os.write((const char *)&id, sizeof(id));
    os.write(name.c_str(), name.size() + 1);
    os.write((const char *)&amount, sizeof(amount));
    os.write((const char *)&when, sizeof(when));
    os.write(comment.c_str(), comment.size() + 1);
}
