#include <iostream>
#include "account.h"
#include "bank.h"
#include "accountmanager.h"
#include "bstree.h"
#include <cassert>
#include <string>
/**
 * Main class will run and it will take a file name passed in the command line
 * It uses a Bank instance to read the transactions from the file, to process them
 * and to print them
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */

int main(int argc, char *argv[]) {

    Bank Bank;
    if (argc < 2) {
        cout << "Invalid input. Please  try again and enter the name of the file to read." << endl;
        exit(1);
    } else if (argc > 2) {
        cout << "Invalid input. Please try again and enter only the name of the file to read." << endl;
        exit(1);
    } else {

        stringstream convert(argv[1]);
        string FileName = convert.str();

        cout << FileName << endl;
        Bank.createTransactions(FileName);
        Bank.processTransaction();
        Bank.DisplayAccounts();

        return 0;
    }
}
