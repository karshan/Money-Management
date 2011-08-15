#include <ctime>
#include <inttypes.h>
#include "file_bank.h"

//This implements a bank whose backing store is a plain binary file. it sucks
//because there can be no random access to the file since everything is variable
//size... but then again the bank interface doesn't have a way to allow random
//access anyways :/

//Also its a bit difficult to have random access unless you fix the size of some
//things like strings... which would make it a lot easier...

void file_bank::save()
{
    uint32_t tmp;
    std::fstream file;
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    file.open(name.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    tmp = magic;
    file.write((const char *)&tmp, sizeof(tmp));
    tmp = version;
    file.write((const char *)&tmp, sizeof(tmp));

    serialize(file);
    file.close();
}

void file_bank::load()
{
    uint32_t tmp;
    std::fstream file;
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit |
                    std::ofstream::eofbit);
    file.open(name.c_str(), std::ios::in | std::ios::binary);

    file.read((char*)&tmp, sizeof(tmp));
    if (tmp != magic)
        throw std::exception(); // TODO: throw a meaningful exception
    file.read((char*)&tmp, sizeof(tmp));
    if (tmp != version)
        throw std::exception(); // here too

    unserialize(file);
    file.close();
}
