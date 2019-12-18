/**
 * Class header file. This class represents a deposit transaction.
 * It inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTIONDEPOSIT_H
#define ASSIGNMENT6_TRANSACTIONDEPOSIT_H

#include "transaction.h"

class TransactionDeposit : public  Transaction{

public:
    /**
     * Constructor. It takes an stringstream
     * @param ss stringstream Stringstream with all the data needed to deposit money
     * in an account: ID of the account to deposit, the Fund to deposit to, and the amount to deposit
     */
    TransactionDeposit(stringstream &ss);
    /**
     * Perform the deposit transaction
     * @param accountManager AccountManager
     * @return bool True if the transaction was successfully completed, otherwise false
     */
    bool PerformTransaction(AccountManager &accountManager) override;
    /**
     * class destructor
     */
    ~TransactionDeposit() override;
private:

    const string TRANSACTION_TYPE = "D";
    int accountID;
    int fundType;
    double amount;
    /**
     * Check if the Fund to deposit is valid (0,9)
     * @param fundNum int The fund to deposit
     * @return bool True if the fund number is between 0 and 9, false otherwise
     */
    bool isValidFund(const int&fundNum)const;
    /**
     * Record the transaction in the history of transactions of the account
     * @param currAcc Pointer to an Account reference
     */
    void updateHistory(Account *&currAcc)const;
};


#endif //ASSIGNMENT6_TRANSACTIONDEPOSIT_H
