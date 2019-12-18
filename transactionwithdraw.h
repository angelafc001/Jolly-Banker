/**
 * Class header file. This class represents a withdraw transaction.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTIONWITHDRAW_H
#define ASSIGNMENT6_TRANSACTIONWITHDRAW_H

#include <sstream>
#include "transaction.h"
#include "account.h"
#include "accountmanager.h"
#include "transaction.h"
#include "bstree.h"

class TransactionWithdraw : public Transaction{
public:
     /**
     * Constructor
     * @param ss stringstream A line read from the file containing the information of the withdraw transaction
     */
    TransactionWithdraw(stringstream &ss);

    /**
     * Withdraw money from an specific Fund in an Account. There are special cases when trying to
     * withdraw money from: Money Market and Prime Money Market; Long-Term Bonds and Short-Term Bonds. If one of these funds does
     * not have enough money to withdraw, then such Fund can 'borrow' money from their linked Fund
     * (Money Market - Prime Money Market) (Long-Term Bond - Short-Term Bond). If the linked Fund does not have enough
     * money to complete the transaction, then the transaction is unsuccessful
     * @param accountManager
     * @return bool True if withdraw is successful, otherwise false
     */
    bool PerformTransaction(AccountManager &accountManager) override;
    /**
     * Class destructor
     */
    virtual ~TransactionWithdraw() override;

private:
    // when withdrawing from money markets or bonds
    /**
     * Withdraw Helper function. If the Fund to withdraw from does not has enough funds, it will attempt to borrow money from
     * linked fund to complete the transaction
     * @param accountManager AccountManager    AccountManager containing all current exiting accounts and their info
     * @param currAccFrom   Account pointer     Account to transfer from
     * @param fundFromBal   double      Amount to transfer
     * @return  bool    True if the linked fund had enough money to complete the transaction, otherwise false
     */
    bool performWithdrawHelper(AccountManager &accountManager, Account *&currAcc, double fundBal);
    /**
    * Get the balance from linked fund
    * @param account Account pointer Current account
    * @param secondFundBalance  double Placeholder for the balance of the second fund
    * @return the second fund type
    */
    const int getSecondFundBalance(const Account *account, double &secondFundBalance);
    /**
     * Check if Fund is valid
     * @param FundType int The fund number
     * @return bool True if the fund is valid, otherwise false
     */
    bool isValidFund(int fundType)const;
    /**
    * Check if current balance covers amount to be withdrew
    * @param currBalance
    * @return bool true if valid, false otherwise
    */
    bool isEnoughMoney(double currentBalance)const;
    /**
     * Check if the fund is a linked fund (0,1,2, or 3)
     * @param fundType int Fund number
     * @return bool True if it is a linked fund, false otherwise
     */
    bool isShareFund(const int fundType)const;
    /**
    * Save transaction stamp in account history of transactions
    * @param currAcc   Account pointer The account to update
    */
    void updateHistory(Account *&currAcc)const;
    /**
     * Save transaction stamp in account history of transactions
     * @param currAcc Account pointer The account to update
     * @param fundId Fund num to update
     * @param amount double Amount to register in transaction stamp
     */
    void updateHistory(Account *&currAcc, const int &fundId, const double &amount)const;

    bool successfulTransaction;
    int accountID;
    int fundType;
    double amount;

    const string TRANSACTION_TYPE = "W";
};


#endif //ASSIGNMENT6_TRANSACTIONWITHDRAW_H
