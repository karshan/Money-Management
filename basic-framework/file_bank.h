#ifndef _FILE_BANK_H
#define _FILE_BANK_H

#include <fstream>
#include <inttypes.h>
#include "bank.h"

//TODO:more innovative naming =)
class file_bank : public bank
{
    //FIXME: this causes little endian vs big endian problems
    static const uint32_t magic = ('N' << 24) | ('O' << 16) | ('M' << 8) | 'K';
    static const uint32_t version = 1; // increment this for a new file format
    std::string name; //TODO:rename this to fname
public:
    file_bank(const file_bank & rhs): bank(rhs) {}
    file_bank(std::string filename): name(filename) {}
    virtual void save();
    virtual void load();
};

#endif //_FILE_BANK_H
