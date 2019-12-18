/**
 * Class header file. This class represents a deposit transaction.
 * It inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include "transactiondeposit.h"
/**
* Constructor. It takes an stringstream
* @param ss stringstream Stringstream with all the data needed to deposit money
* in an account: ID of the account to deposit, the Fund to deposit to, and the amount to deposit
*/
TransactionDeposit::TransactionDeposit(stringstream &ss) {
    string holder;
    ss >> holder;
    if(holder.length() == 0){
        cout<< "Invalid accountID. Try again." <<endl;
        exit(1);
    }
    ss >> amount; // amount to deposit

    fundType = stoi(holder.substr(holder.length() - 1));
    accountID = stoi(holder.substr(0, 4));

}
/**
* Perform the deposit transaction
* @param accountManager AccountManager
* @return bool True if the transaction was successfully completed, otherwise false
*/
bool TransactionDeposit::PerformTransaction(AccountManager &accountManager) {

    Account *accDep = accountManager.GetAccount(accountID);

    if(accDep == nullptr){
        cout << "Inside perform transaction deposit." << endl;
        cout << "Attempt to deposit failed. Invalid accountID ID. Please try again." <<endl;
        return false;
    }

    if(!isValidFund(fundType)){

        cout << "Attempt to deposit failed. Fund " << fundType << " is invalid. Please try again." <<endl;

        return false;
    }

    double newBalance = accDep->GetFundBalance(fundType);
    newBalance += amount;

    updateHistory(accDep);

    return accDep->UpdateFund(fundType, newBalance);
}
/**
 * Class destructor
 */
TransactionDeposit::~TransactionDeposit() {

}
/**
 * Check if the Fund to deposit is a valid Fund
 * @param fundNum int The Fund number
 * @return bool True if the Fund is valid, otherwise false
 */
bool TransactionDeposit::isValidFund(const int &fundNum) const{
     return (fundType >= 0 && fundType < 10);;
}
/**
 * Save a stamp of the transaction in the Account history of tran
 * sactions' vector
 * @param currAcc Account pointer A pointer to an Account reference to
 * save the transaction stamp
 */
void TransactionDeposit::updateHistory(Account *&currAcc) const {
    stringstream ss;
    ss << accountID << fundType << " " <<amount;

    string transactionStamp = TRANSACTION_TYPE + " " + ss.str();

    currAcc->UpdateAccountHistory(fundType, transactionStamp);
}