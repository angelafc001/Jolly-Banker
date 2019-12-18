/**
 * Class header file. This class is the parent class of all the transaction classes. It has a abstract function
 * "Perform Transaction" which all child classes must implement. This abstract function will take advantage of
 * polymorphism at run time, letting the compiler decide which "Perform Transaction" to execute depending on the child
 * class calling the function.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTION_H
#define ASSIGNMENT6_TRANSACTION_H
#include "accountmanager.h"
#include <iostream>
#include <sstream>
/**
 * Constant chars representing the types of Transaction child classes Transaction can have
 */
const char OPEN = 'O';
const char DEPOSIT = 'D';
const char WITHDRAW = 'W';
const char TRANSFER = 'T';
const char HISTORY = 'H';

class Transaction {
public:
    /**
     * Abstract function. Each child class must implement it , and perform their task in this function
     * @param accountManager AccountManager The Account Manager
     * @return bool
     */
    virtual bool PerformTransaction(AccountManager &accountManager) = 0;
    /**
     * Destructor
     */
    virtual ~Transaction();
private:

    int ID;
};
#endif //ASSIGNMENT6_TRANSACTION_H
