/**
 * Class .cpp file. This class represents a transaction to open an account. It takes the first and last name
 * of the account holder, and an account ID number.
 * This class inherits from Transaction class
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include <sstream>
#include "transactionopen.h"

/**
 * Class destructor
 */
TransactionOpen::~TransactionOpen() {

}
/**
* Class constructor. It takes an stringstream, which contains the information of the account about to be opened
* @param ss stringstream
*/
TransactionOpen::TransactionOpen(stringstream &ss) {

    ss >> lastName;
    ss>> firstName;
    ss >> ID;
}
/**
* Create an new account, and saves it in the AccountManager
* @param accountManager AccountManager BSTree class wrapper
* @return bool True if the transaction was completed, false if the ID number is already taken by other account
*/
bool TransactionOpen::PerformTransaction(AccountManager &accountManager) {

    Account *newAccount = new Account(firstName,lastName, ID);
    if(accountManager.AddAccount(newAccount)){


        return true;
    }else{
        delete newAccount;
        cout << "ERROR: Account " << ID << " is already open. Transaction refused. "<<endl;
        return false;
    }
}