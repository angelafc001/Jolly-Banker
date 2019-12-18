/**
 * .cpp file of class. This class represents a transaction to obtain a history of
 * transactions done in an account. The displayed history can be for all Funds, or
 * a particular Fund.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include "transactionhistory.h"
/**
 * Class constructor. It takes a stringstream, which contains the transaction data.
 * @param ss stringstream The Transaction information
 */
TransactionHistory::TransactionHistory(stringstream &ss) {

    string holder;
    ss >>holder;

    if(!isValidAccount(holder)){
        cout<< "ERROR: Unable to execute History Transaction. Account ID is not valid."<<endl;
        return;
    }

    if(holder.length() > 4){
        accountID = stoi(holder.substr(0,4));
        fundType = stoi(holder.substr(holder.length()-1));

    }else{
        accountID = stoi(holder);
        fundType = -1;
    }
}

/**
* Display the history of the transactions done in a particular account. It can display a general
* transaction history for the account, or a transaction history for a particular Fund from the account
* @param accountManager AccountManager
*@return bool True if the transaction was successful, otherwise false
*/
bool TransactionHistory::PerformTransaction(AccountManager &accountManager) {
    Account *currAct = accountManager.GetAccount(accountID);

    if(currAct == nullptr){

        cout << "ERROR: Account under ID " << accountID << " does not exist."<<endl;
        cout << "Attempt to get history failed. Invalid accountID. Please try again." <<endl;
        return false;

    }else{

        if(fundType == -1 ){ //if not specific Fund was requested, then we print all
            DisplayAll(currAct);

        }else{
            DisplayByFund(fundType, currAct);
        }
    }
}
/**
 * Class destructor
 */
TransactionHistory::~TransactionHistory() {

}
/**
 * Check if the account read from file is valid
 * @param holder string The account and Fund number together
 * @return bool True if its valid, otherwise false
 */
bool TransactionHistory::isValidAccount(const string &holder) {

    return  holder.length() >=4 || holder.length() < 6 ;
}

/**
* Print out to console all the transactions done in all the Funds of an account
* @param currAcount Account pointer The account to get the history of transactions
*/
void TransactionHistory::DisplayAll(Account *&currAcc)const {


    cout << "Transaction History for " << currAcc->GetFirstName() << " " << currAcc->GetLastName() << " by fund." << endl;

    for (int i = 0; i <currAcc->GetMaxFunds() ; ++i) {
        int fundTransactions = currAcc->GetFundTransactionHistory(i).size();

        if(fundTransactions == 0){
            continue;
        }else{
           cout << currAcc->GetFundName(i) << ": $" << currAcc->GetFundBalance(i) <<endl;
           for(auto item : currAcc->GetFundTransactionHistory(i)){
                cout << '\t' + item <<endl;
           }
            cout<<endl;
        }
    }


}
/**
* Print out to console all the transactions done in an specific Fund from the  account
* @param fund int The fund number to get the history
* @param currAcount Account pointer The account to get the history of transactions
*/
void TransactionHistory::DisplayByFund(const int &fund, Account *& currAccount) const {

    if(!isValidFund(fund)){
        cout << "Invalid type of fund to print." << endl;
        return;
    }else{
        cout << "Transaction History for " << currAccount->GetFirstName() << " " << currAccount->GetLastName() << " " << FUNDS[fund] << " :$" <<
             currAccount->GetFundBalance(fund) << endl;
        vector<string> transactions = currAccount->GetFundTransactionHistory(fund);

        if(transactions.empty()){ // If there are no transaction stamps registered under the specified fund
            cout << "There are no recent transactions in "<< FUNDS[fund]<<" fund to display" <<endl;
            cout << endl;
        }else {
            for (auto item: transactions) {

                cout << "\t" + item << endl;
            }
            cout << endl;
            }
        }
}
/**
 * Class destructor
 */
TransactionHistory::TransactionHistory() {
    accountID = 0;
    fundType = -1;

}
/**
 * Check if the fund is valid
 * @param FundType int The Fund number
 * @return bool True if the Fund number is valid, otherwise false
 */
bool TransactionHistory::isValidFund(const int &FundType) const {
    return (fundType >= 0 && fundType < 10);
}