/**
 * Class header file. This class represents a withdraw transaction.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include <cassert>
#include "transactionwithdraw.h"
/**
* Constructor
* @param ss stringstream A line read from the file containing the information of the withdraw transaction
*/
TransactionWithdraw::TransactionWithdraw(stringstream &ss) {
    string holder;
    ss >> holder;

    if(holder.length() != 5){
        cout << "Transaction failed. Invalid accountID. Please try again" <<endl;
        return;

    }else {

        ss >> amount;
        fundType = stoi(holder.substr(holder.length() - 1));
        accountID = stoi(holder.substr(0, 4));
    }
}
/**
* Withdraw money from an specific Fund in an Account. There are special cases when trying to
* withdraw money from: Money Market and Prime Money Market; Long-Term Bonds and Short-Term Bonds. If one of these funds does
* not have enough money to withdraw, then such Fund can 'borrow' money from their linked Fund
* (Money Market - Prime Money Market) (Long-Term Bond - Short-Term Bond). If the linked Fund does not have enough
* money to complete the transaction, then the transaction is unsuccessful
* @param accountManager
* @return bool True if withdraw is successful, otherwise false
*/
bool TransactionWithdraw::PerformTransaction(AccountManager &accountManager) {

    Account * currAcc = accountManager.GetAccount(accountID);

    if(!isValidFund(fundType)){
        cout << "Attempt to deposit failed. Invalid Fund. Please try again." <<endl;
        return false;
    }

    if(currAcc == nullptr){
        cout << "Attempt to withdraw from account " << accountID << " failed. Invalid ID. Please try again." <<endl;
        return false;
    }

    double fundBalance = currAcc->GetFundBalance(fundType);

    if(!isEnoughMoney(fundBalance) && isShareFund(fundType)){
        performWithdrawHelper(accountManager, currAcc, fundBalance);

    }else if(!isEnoughMoney(fundBalance) && !isShareFund(fundType)){

        cout << "ERROR: not enough funds to withdraw $" << amount << " from " << currAcc->GetFirstName() << " " << currAcc->GetLastName() <<
             " " << currAcc->GetFundName(fundType) << endl;

        successfulTransaction = false;
        updateHistory(currAcc, fundType, amount);
        return false;

    }else {

            double newBalance = fundBalance - amount;
            successfulTransaction =  currAcc->UpdateFund(fundType, newBalance);
            assert(successfulTransaction);
        updateHistory(currAcc);
            return true;

        }
}
/**
 * Class destructor
 */
TransactionWithdraw::~TransactionWithdraw() {

}
/**
* Withdraw Helper function. If the Fund to withdraw from does not has enough funds, it will attempt to borrow money from
* linked fund to complete the transaction
* @param accountManager AccountManager    AccountManager containing all current exiting accounts and their info
* @param currAccFrom   Account pointer     Account to transfer from
* @param fundFromBal   double      Amount to transfer
* @return  bool    True if the linked fund had enough money to complete the transaction, otherwise false
*/
// when withdrawing from money markets or bonds
bool TransactionWithdraw::performWithdrawHelper(AccountManager &accountManager, Account *&currAcc, double fundBal) {

    double toPay = amount - fundBal;
    double linkedFundBalance;

    int secondFundType = getSecondFundBalance(currAcc, linkedFundBalance);

    if(!isValidFund(secondFundType)){
        cout << "ERROR: Invalid attempt to withdraw from account: " << accountID << " The fund does not exist. " <<endl;
        successfulTransaction = false;
        return false;
    }

    if(linkedFundBalance < 0 || linkedFundBalance < toPay){

        cout << "ERROR: not enough funds to withdraw $" << amount << " from " << currAcc->GetFirstName() << " " << currAcc->GetLastName() <<
             " " << currAcc->GetFundName(fundType) << " nor " << currAcc->GetFundName(secondFundType) << endl;

        successfulTransaction = false;
        updateHistory(currAcc, fundType, toPay);
        updateHistory(currAcc, secondFundType, toPay);

        return false;

    }else{

        double fundPrincipalBal = currAcc->GetFundBalance(fundType);

         successfulTransaction = currAcc->UpdateFund(fundType, 0);
         assert(successfulTransaction);

        updateHistory(currAcc, fundType, fundPrincipalBal);

        double newBalance = (linkedFundBalance - toPay);

        successfulTransaction  = currAcc->UpdateFund(secondFundType, newBalance);

        assert(successfulTransaction);
        updateHistory(currAcc, secondFundType, toPay);

        return true;
    }
}

/**
* Get the balance from linked fund
* @param account Account pointer Current account
* @param secondFundBalance  double Placeholder for the balance of the second fund
* @return the second fund type
*/
const int TransactionWithdraw::getSecondFundBalance(const Account *account, double &secondFundBalance) {

    switch(fundType){
        case 0 :

            secondFundBalance = account->GetFundBalance(1);
            return 1;
        case 1 :

            secondFundBalance = account->GetFundBalance(0);
            return 0;
        case 2:

            secondFundBalance = account->GetFundBalance(3);
            return 3;
        case 3:

            secondFundBalance = account->GetFundBalance(2);
            return 2;
        default:
            secondFundBalance = 0;
            return -1;
    }

}
/**
* Check if Fund is valid
* @param FundType int The fund number
* @return bool True if the fund is valid, otherwise false
*/
bool TransactionWithdraw::isValidFund(int fundType) const {

    return (fundType >= 0 && fundType < 10);
}
/**
* Check if current balance covers amount to be withdrew
* @param currBalance
* @return bool true if valid, false otherwise
*/
bool TransactionWithdraw::isEnoughMoney(double currentBalance) const {
    return currentBalance >= amount;
}
/**
* Check if the fund is a linked fund (0,1,2, or 3)
* @param fundType int Fund number
* @return bool True if it is a linked fund, false otherwise
*/
bool TransactionWithdraw::isShareFund(const int fundType) const {
    return (fundType == 0 || fundType == 1 || fundType == 2 || fundType == 3);
}
/**
* Save transaction stamp in account history of transactions
* @param currAcc   Account pointer The account to update
*/
void TransactionWithdraw::updateHistory(Account *&currAcc) const {

    stringstream ss;
    ss << accountID << fundType << " " << amount;

    string transactionStamp;
    if(successfulTransaction){
        transactionStamp = TRANSACTION_TYPE + " " + ss.str();

    }else{

        transactionStamp = TRANSACTION_TYPE+ " " + ss.str() + " (Failed)";
    }
    currAcc->UpdateAccountHistory(fundType, transactionStamp);
}
/**
* Save transaction stamp in account history of transactions
* @param currAcc Account pointer The account to update
* @param fundId Fund num to update
* @param amount double Amount to register in transaction stamp
*/
void TransactionWithdraw::updateHistory(Account *&currAcc, const int &fundId, const double &amount) const {

    stringstream ss;
    ss << currAcc->GetID() << fundId << " " << amount;
    string transactionStamp;

    if(successfulTransaction){
         transactionStamp = TRANSACTION_TYPE+ " "+ ss.str();

    }else{

        transactionStamp = TRANSACTION_TYPE+ " " + ss.str() + " (Failed)";
    }

    currAcc->UpdateAccountHistory(fundId, transactionStamp);
}