#ifndef _FILE_BANK_H
#define _FILE_BANK_H

#include <fstream>
#include "bank.h"

//TODO:more innovative naming =)
class file_bank : public bank
{
    std::string name;
public:
    file_bank(std::string filename): name(filename) {}
    virtual void save();
    virtual void load();
};

#endif //_FILE_BANK_H
