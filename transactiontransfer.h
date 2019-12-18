/**
 * Class header file. This class represents a transfer transaction. It can transfer money to other accounts. Also, it
 * can transfer money within the same account between different Funds. Money market funds are linked if a Fund does not
 * have enough money to transfer. Same goes for Bonds Funds.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_TRANSACTIONTRANSFER_H
#define ASSIGNMENT6_TRANSACTIONTRANSFER_H

#include "transaction.h"

class TransactionTransfer: public Transaction{

public:
    /**
     * Constructor
     * @param ss stringstream A line read from the file containing the information of the transfer transaction
     */
    TransactionTransfer(stringstream &ss);
    /**
     * Transfer money between accounts, or between Funds in the same Account. There are special cases when trying to
     * transfer money from funds with not enough money: Money Market Funds and Bonds Funds. If one of these funds does
     * does have enough money to transfer to another account, then such Fund can 'borrow' money from their linked Fund
     * (Money Market - Prime Money Market) (Long-Term Bond - Short-Term Bond). If the linked Fund does not have enough
     * money to complete the transaction, then the transfer is unsuccessful
     * @param accountManager
     * @return bool True if transfer was successful, otherwise false
     */
    bool PerformTransaction(AccountManager &accountManager) override;
    /**
     * Class destructor
     */
    ~TransactionTransfer() override;
private:
    /**
     * Transfer Helper function. If the Fund to transfer from does not has enough funds, it will borrow money from
     * linked fund
     * @param accountManager AccountManager    AccountManager containing all current exiting accounts and their info
     * @param currAccFrom   Account pointer     Account to transfer from
     * @param currAccTo     Account pointer     Account to transfer to
     * @param fundFromBal   double      Amount to transfer
     * @return  bool    True if the linked fund had enough money to complete the transfer, otherwise false
     */
    bool performTransferHelper(AccountManager &accountManager, Account *&currAccFrom, Account *&currAccTo, double fundFromBal);
    /**
     * Check if the accout information read from the file is valid
     * @param holder stringstream   Line read from file with account info
     * @return true if valid, otherwise false
     */
    bool isValidAccount(const string &holder);
    /**
     * Check if Fund is valid
     * @param FundType int The fund number
     * @return bool True if the fund is valid, otherwise false
     */
    bool isValidFund(const int FundType)const;
    /**
     * Check if current balance covers amount to be transfered
     * @param currBalance
     * @return bool true if valid, false otherwise
     */
    bool hasEnoughMoney(double currBalance)const;
    /**
     * Check if the fund is a linked fund (0,1,2, or 3)
     * @param fundType int Fund number
     * @return bool True if it is a linked fund, false otherwise
     */
    bool isShareFund(const int fundType)const;
    /**
     * Save transaction stamp in account history of transactions
     * @param currAcc   Account pointer The account to update
     * @param accountTo  Account pointer The account to update
     */
    void updateHistory(Account *&currAcc, Account *&accountTo)const;
    /**
     * Save transaction stamp in account history of transactions
     * @param currAcc Account pointer The account to update
     * @param fundId Fund num to update
     * @param amount double Amount to register in transaction stamp
     */
    void updateHistory(Account *&currAcc, const int &fundId, const double &amount)const;
    /**
     * Get the balance from linked fund
     * @param account Account pointer Current account
     * @param secondFundBalance  double Placeholder for the balance of the second fund
     * @return the second fund type
     */
    const int getSecondFundBalance(const Account *account, double &secondFundBalance);
    bool successfulTransaction;
    int accountIDFrom;
    int fundTypeFrom;
    double amount;
    int accountIDTo;
    int fundTypeTo;
    const string TRANSACTION_TYPE = "T";

};
#endif //ASSIGNMENT6_TRANSACTIONTRANSFER_H