/**
 * Class .cpp file. This class represents a transfer transaction. It can transfer money to other accounts. Also, it
 * can transfer money within the same account between different Funds. Money market funds are linked if a Fund does not
 * have enough money to transfer. Same goes for Bonds Funds.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include <cassert>
#include "transactiontransfer.h"
/**
* Constructor
* @param ss stringstream A line read from the file containing the information of the transfer transaction
*/
TransactionTransfer::TransactionTransfer(stringstream &ss)  {

    string holderFrom; // holds information of accountID and fund to withdraw from
    ss >> holderFrom;

    //check if the lenght is valid. Length of the string should be  5
    if(!isValidAccount(holderFrom)){
        cout << "ERROR: Invalid accountID ID. Please try again." <<endl;
        return;
    }

    ss >>amount; //amount to transfer

    string holderTo; // It holds information of accountID and fund to deposit amount
    ss>> holderTo;

    //check if the length of holderTo is 5
    if(!isValidAccount(holderTo)){
        cout << "Invalid accountID ID. Please try again." <<endl;
        return;
    }

    //After both check points have been passed, now we split the holder strings
    accountIDFrom = stoi(holderFrom.substr(0,4));
    fundTypeFrom = stoi(holderFrom.substr(holderFrom.length() - 1));

    accountIDTo = stoi(holderTo.substr(0,4));
    fundTypeTo = stoi(holderTo.substr(holderFrom.length() - 1));

}
/**
 * Class destructor
 */
TransactionTransfer::~TransactionTransfer() {

}
/**
* Transfer money between accounts, or between Funds in the same Account. There are special cases when trying to
* transfer money from funds with not enough money: Money Market Funds and Bonds Funds. If one of these funds does
* does have enough money to transfer to another account, then such Fund can 'borrow' money from their linked Fund
* (Money Market - Prime Money Market) (Long-Term Bond - Short-Term Bond). If the linked Fund does not have enough
* money to complete the transaction, then the transfer is unsuccessful
* @param accountManager
* @return bool True if transfer was successful, otherwise false
*/
bool TransactionTransfer::PerformTransaction(AccountManager &accountManager) {

    Account * currAccFrom = accountManager.GetAccount(accountIDFrom);
    Account * currAccTo = accountManager.GetAccount(accountIDTo);


    if(!(isValidFund(fundTypeFrom) ||isValidFund(fundTypeTo) )){

        cout << "ERROR: Attempt to transfer failed. Invalid Fund. Please try again." <<endl;
        return false;
    }

    if(currAccFrom == nullptr) {

        cout << "ERROR: Account " << accountIDFrom << " not found. Transferal refused."<<endl;
        return false;
    }else if(currAccTo == nullptr ){
        cout << "ERROR: Account " << accountIDTo << " not found. Transferal refused."<<endl;
        return false;
    }else if (currAccFrom->GetID() == currAccTo->GetID() && fundTypeFrom == fundTypeTo){
        cout << "ERROR: Attempt to transfer to same  fund in same account. Transfer is invalid"<<endl;

        return false;
    }

    double fundFromBalance = currAccFrom->GetFundBalance(fundTypeFrom);

    if(!hasEnoughMoney(fundFromBalance) && isShareFund(fundTypeFrom)){

        performTransferHelper(accountManager, currAccFrom,currAccTo, fundFromBalance);

    }else if (!hasEnoughMoney(fundFromBalance) && !isShareFund(fundTypeFrom)){

        cout<< "Account: " << accountIDFrom << " does not has enough money in " << currAccFrom->GetFundName(fundTypeFrom) << " fund." <<endl;
        successfulTransaction = false;
        updateHistory(currAccFrom, fundTypeFrom, amount);
        return false;

    }else if(hasEnoughMoney(fundFromBalance)){

        fundFromBalance -= amount;
        successfulTransaction = currAccFrom->UpdateFund(fundTypeFrom, fundFromBalance);
        assert(successfulTransaction);

        double accToBal = currAccTo->GetFundBalance(fundTypeTo);

        accToBal += amount;
        updateHistory(currAccFrom, currAccTo);
        successfulTransaction = currAccTo->UpdateFund(fundTypeTo, accToBal);
        assert(successfulTransaction);
        return  true;
    }
}

/**
* Transfer Helper function. If the Fund to transfer from does not has enough funds, it will borrow money from
* linked fund
* @param accountManager AccountManager    AccountManager containing all current exiting accounts and their info
* @param currAccFrom   Account pointer     Account to transfer from
* @param currAccTo     Account pointer     Account to transfer to
* @param fundFromBal   double      Amount to transfer
* @return  bool    True if the linked fund had enough money to complete the transfer, otherwise false
*/
bool TransactionTransfer::performTransferHelper(AccountManager &accountManager, Account *&currAccFrom, Account *& currAccTo, double fundFromBal) {

    double leftToPay = amount - fundFromBal;
    double sharedFundBalance;

    int secondFundType = getSecondFundBalance(currAccFrom, sharedFundBalance);


    if(!isValidFund(secondFundType)){

        cout << "ERROR: No shared fund founded." <<endl;

        return false;
    }

    //At this point, neither fund a nor fund b have enough money to transfer
    if(sharedFundBalance < 0 || sharedFundBalance < leftToPay){

        cout << "ERROR: Not enough funds to withdraw $" << leftToPay << " to complete transfer from " << currAccFrom->GetFirstName()
             << " " << currAccFrom->GetLastName() << " " << currAccFrom->GetFundName(fundTypeFrom) << endl;
        successfulTransaction = false;
        //Updating history of the first fund attempted to withdraw from
        updateHistory(currAccFrom, fundTypeFrom, amount);

        updateHistory(currAccFrom, secondFundType, leftToPay);

        return false;

    }else{

        double prcplFundBal = currAccFrom->GetFundBalance(fundTypeFrom);

        successfulTransaction = currAccFrom->UpdateFund(fundTypeFrom, 0);
        assert(successfulTransaction);

        updateHistory(currAccFrom, fundTypeFrom, prcplFundBal);

        sharedFundBalance -= leftToPay;
        successfulTransaction = currAccFrom->UpdateFund(secondFundType, (sharedFundBalance));
        assert(successfulTransaction);

        updateHistory(currAccFrom, secondFundType, leftToPay);

        double accToNewBal = currAccTo->GetFundBalance(fundTypeTo);
        accToNewBal += amount;

        return currAccTo->UpdateFund(fundTypeTo, accToNewBal);
    }
}
/**
* Check if the accout information read from the file is valid
* @param holder stringstream   Line read from file with account info
* @return true if valid, otherwise false
*/
bool TransactionTransfer::isValidAccount(const string &holder) {

    return  holder.length() == 5 ;
}
/**
* Check if Fund is valid
* @param FundType int The fund number
* @return bool True if the fund is valid, otherwise false
*/
bool TransactionTransfer::isValidFund(const int fundType)const {
    return (fundType >= 0 && fundType < 10);
}

/**
* Get the balance from linked fund
* @param account Account pointer Current account
* @param secondFundBalance  double Placeholder for the balance of the second fund
* @return the second fund type
*/
const int TransactionTransfer::getSecondFundBalance(const Account *account, double &secondFundBalance) {

    switch(fundTypeFrom){
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
* Check if current balance covers amount to be transfered
* @param currBalance
* @return bool true if valid, false otherwise
*/
bool TransactionTransfer::hasEnoughMoney(double currBalance) const {
    return currBalance >= amount;
}
/**
* Check if the fund is a linked fund (0,1,2, or 3)
* @param fundType int Fund number
* @return bool True if it is a linked fund, false otherwise
*/
bool TransactionTransfer::isShareFund(const int fundTypeFrom) const {
    return (fundTypeFrom == 0 || fundTypeFrom == 1 || fundTypeFrom == 2 || fundTypeFrom == 3);
}
/**
* Save transaction stamp in account history of transactions
* @param currAcc   Account pointer The account to update
* @param accountTo  Account pointer The account to update
*/
void TransactionTransfer::updateHistory(Account *&currAcc, Account *&accountTo) const {
    //T 10017 54 10015
    stringstream ss;

    ss << accountIDFrom << fundTypeFrom << " " << amount << " " << accountTo->GetID() << fundTypeTo;

    string transactionStamp;

    if(successfulTransaction){
      transactionStamp = TRANSACTION_TYPE + " "+ ss.str();
    }else{
        transactionStamp = TRANSACTION_TYPE + " "+ ss.str() + " (Failed)";
    }

    currAcc->UpdateAccountHistory(fundTypeFrom, transactionStamp);
    accountTo->UpdateAccountHistory(fundTypeTo, transactionStamp);


}
/**
* Save transaction stamp in account history of transactions
* @param currAcc Account pointer The account to update
* @param fundId Fund num to update
* @param amount double Amount to register in transaction stamp
*/
void TransactionTransfer::updateHistory(Account *&currAcc, const int &fundId, const double &amount) const {
    //T 10017 54 10015
    stringstream ss;

    ss << currAcc->GetID() << fundId << " " << amount << " " << accountIDTo << fundTypeTo;
    string transactionStamp;

    if(successfulTransaction){
        transactionStamp = TRANSACTION_TYPE+ " "+ ss.str();

    }else{

        transactionStamp = TRANSACTION_TYPE+ " " + ss.str() + " (Failed)";
    }

    currAcc->UpdateAccountHistory(fundId, transactionStamp);
}