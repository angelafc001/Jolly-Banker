/**
 * Class header file. This class represents a transaction to open an account. It takes the first and last name
 * of the account holder, and an account ID number.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTIONOPEN_H
#define ASSIGNMENT6_TRANSACTIONOPEN_H

using namespace std;

#include <string>
#include "account.h"
#include "accountmanager.h"
#include "transaction.h"
#include "bstree.h"

class TransactionOpen: public Transaction {
public:
    /**
     * Class constructor. It takes an stringstream, which contains the information of the account about to be opened
     * @param ss stringstream
     */
    TransactionOpen(stringstream &ss);
    /**
     * Create an new account, and saves it in the AccountManager
     * @param accountManager AccountManager BSTree class wrapper
     * @return bool True if the transaction was completed, false otherwise
     */
    bool PerformTransaction(AccountManager &accountManager) override;
    /**
     * Class destructor
     */
    virtual ~TransactionOpen();

private:
    const string TRANSACTION_TYPE = "O";
    string firstName;
    string lastName;
    int ID;
};


#endif //ASSIGNMENT6_TRANSACTIONOPEN_H
