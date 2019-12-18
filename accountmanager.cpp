/**
 * AccountManager class .cpp file. This class uses a BSTree to store the bank accounts.
 * It serves as a bridge between the BSTree and the all the Transaction child classes
 * It allows to add, get, and display accounts from the BSTree.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include <iostream>
#include <stdexcept>
#include "accountmanager.h"

/**
* Get the Account associated with the ID
* @param accountID int The ID of the Account
* @return Account* A pointer associated to the Account
*/
bool AccountManager::AddAccount(Account *account) {
    if(accounts.Insert(account)){
        return true;
    }else {
        return false;
    }
}
/**
 * Class constructor
 */
AccountManager::AccountManager() {
    accounts;
}
/**
 * Get the account associated with the ID
 * @param accountID int Account ID
 * @return Account* A pointer to the Account associated to the ID
 */
Account* AccountManager::GetAccount(const int &accountID) const{

    Account *newAccount = nullptr;

    if(!accounts.Retrieve(accountID, newAccount)){
        cout << "Error! Account :" << accountID << " does not exist in our system"<<endl;
        delete newAccount;
        return nullptr;
    }

    return newAccount;
}
/**
 * Check if AccountManager is empty
 * @return bool True if it is empty, otherwise false
 */
bool AccountManager::isEmpty()const {
    return accounts.isEmpty();
}
/**
 * Class destructor
 */
AccountManager::~AccountManager() {
    accounts.Empty();
}
/**
 * Display all the accounts stored in AccountManager
 */
void AccountManager::Display() const {
    accounts.Display();
}

