//Money-Management command line utility
//by Karshan Sharma <sharma34@illinois.edu>

#include <iostream>
#include <string>
#include <ctime>
#include "file_bank.h"

void account_menu(account & acc);

//TODO: for now this is interactive, but later maybe add the LLVM commandline
//arguments parser, and only run in interactive mode if -i was specified
//otherwise let the arguments do everything...
int main()
{
    int chc;
    std::string fname("data.bin");
    file_bank bank(fname);

    do {
        std::cout << "Main Menu: (file: " << fname << ")\n"
                  << "accounts:\n\tid\tname\n";
        for (std::vector<account>::const_iterator it = bank.accounts_begin();
             it != bank.accounts_end(); it++)
            std::cout << "\t" << (*it).get_id() << "\t" << (*it).name << "\n";
        std::cout << "0)exit\n"
                  << "1)load\n"
                  << "2)save\n"
                  << "3)add account\n"
                  << "4)edit account\n"
                  << "5)delete account\n"
                  << "enter choice: ";

        std::cin >> chc;
        
        std::string acc;
        unsigned int id;
        switch(chc) {
        case 0:
            break;
        case 1:
            bank.load();
            break;
        case 2:
            bank.save();
            break;
        case 3:
            std::cout << "enter account name: ";
            std::cin >> acc;
            bank.add_account(account(acc));
            break;
        case 4:
            std::cout << "enter account id: ";
            std::cin >> id;
            try {
                account_menu(bank.get_account(id));
            }
            catch (bad_id & e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 5:
            std::cout << "enter account id: ";
            std::cin >> id;
            if (!bank.delete_account(id))
                std::cout << "Failed! bad id\n";
            break;
        default:
            std::cout << "bad choice\n";
        }
    } while(chc != 0);
    return 0;
}

void account_menu(account & acc)
{
    int chc;
    do {
        std::cout << "Account Menu: (account: " << acc.name << ")\n"
                  << "transactions:\n\tid\tname\tamount\ttime\n";
        for (std::vector<transaction>::const_iterator it = acc.transactions_begin();
             it != acc.transactions_end(); it++)
            std::cout << "\t" << (*it).get_id() << "\t" << (*it).name << "\t"
                      << (*it).amount << "\t" << ctime(&((*it).when)) << "\n";
        std::cout << "0)back\n"
                  << "1)add transaction\n"
                  << "2)delete transaction\n"
                  << "enter choice: ";

        std::cin >> chc;
        
        std::string name;
        float amt;
        unsigned int id;
        switch(chc) {
        case 0:
            break;
        case 1:
            std::cout << "enter name: ";
            std::cin >> name;
            std::cout << "enter amount: ";
            std::cin >> amt;
            acc.add_transaction(transaction(name, amt));
            break;
        case 2:
            std::cout << "enter id: ";
            std::cin >> id;
            if (!acc.delete_transaction(id))
                std::cout << "Failed! no such id\n";
            break;
        default:
            std::cout << "bad choice\n";
        }
    } while(chc != 0);
}