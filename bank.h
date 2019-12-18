/**
 * Class header file. This class allows to read a file of transaction. As it reads the file, it create each transaction
 * and store it in a queue. After it has reach the end of the file, it starts processing each transaction dequeing the
 * queue. When all the transaction has been performed, it prints out the information of all the accounts and their funds
 * in the bank.
 * It allows to read a file of transactions, to process them, and to display them.
 * It uses an AccountManager to access the information of each account store in the BSTree.
 * Author: Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_BANK_H
#define ASSIGNMENT6_BANK_H

#include <queue>
#include "bstree.h"
#include "transaction.h"
#include "transactionopen.h"
#include "transactiondeposit.h"
#include "transactionwithdraw.h"
#include "transactiontransfer.h"
#include "transactionhistory.h"

class Bank {
public:
    /**
     * Bank constructor
     */
    Bank();
    /**
     * Bank destructor
     */
    ~Bank();
    /**
     * Create transactions by reading a file
     * @param FileName string The name of the file to read
     */
    void createTransactions(const string &FileName);
    /**
     * Process the transactions stored in the queue of transactions
     */
    void processTransaction();
    /**
     * Display accounts opened in Bank
     */
    void DisplayAccounts()const;

private:
    /**
     * Queue of transaction Pointers
     */
    queue<Transaction*> transactions;
    // Bridge between BST and transactions
    AccountManager accounts;
};
#endif //ASSIGNMENT6_BANK_H
