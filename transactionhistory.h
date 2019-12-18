/**
 * Header file of class. This class represents a transaction to obtain a history of
 * transactions done in an account. The displayed history can be for all Funds, or
 * a particular Fund.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTIONHISTORY_H
#define ASSIGNMENT6_TRANSACTIONHISTORY_H
#include "transaction.h"
#include "accountmanager.h"
#include "account.h"
#include <vector>
#include <string>
using namespace std;
class TransactionHistory: public Transaction{

public:
    /**
     * Class constructor
     */
    TransactionHistory();
    /**
     * Class constructor. It takes a stringstream, which contains the transaction data.
     * @param ss stringstream The Transaction information
     */
    TransactionHistory(stringstream  &ss);
    /**
     * Display the history of the transactions done in a particular account. It can display a general
     * transaction history for the account, or a transaction history for a particular Fund from the account
     * @param accountManager AccountManager
     * @return bool True if the transaction was successful, otherwise false
     */
    bool PerformTransaction(AccountManager &accountManager);

    /**
     * Class destructor
     */
    ~TransactionHistory() ;

private:
    const string TRANSACTION_TYPE = "H";
    /**
     *
     */
    int accountID;
    int fundType;
    /**
     * Check if the Fund to deposit is valid (0,9)
     * @param fundNum int The fund to deposit
     * @return bool True if the fund number is between 0 and 9, false otherwise
     */
    bool isValidFund(const int &FundType)const;
    /**
     * Print out to console all the transactions done in all the Funds of an account
     * @param currAcount Account pointer The account to get the history of transactions
     */
    void DisplayAll(Account *&currAcount)const;
    /**
     * Print out to console all the transactions done in an specific Fund from the  account
     * @param fund int The fund number to get the history
     * @param currAcount Account pointer The account to get the history of transactions
     */
    void DisplayByFund(const int &fund, Account *&currAccount) const;
    /**
     * Check if the account is valid
     * @param holder string Account and Fund number together
     * @return bool
     */
    bool isValidAccount(const string &holder);
};


#endif //ASSIGNMENT6_TRANSACTIONHISTORY_H
