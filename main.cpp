#include <iostream>
#include <string>
#include "file_bank.h"

int main()
{
    file_bank mybank(std::string("data.bin"));
    account & myacc = mybank.get_account(
	mybank.add_account(account(std::string("tcf"))));
    myacc.add_transaction(transaction(std::string("chipotle"), -6.5));
    return 0;
}
