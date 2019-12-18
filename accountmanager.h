/**
 * AccountManager class header. This class uses a BSTree to store the bank accounts.
 * It serves as a bridge between the BSTree and the all the Transaction child classes
 * It allows to add, get, and display accounts from the BSTree.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_ACCOUNTMANAGER_H
#define ASSIGNMENT6_ACCOUNTMANAGER_H
#include "bstree.h"
#include <queue>

class AccountManager {

public:
    /**
     * Class constructor
     */
    AccountManager();
    /**
     * Class destructor
     */
    ~AccountManager();
    /**
     * Add an account into the Account Manager
     * @param account Account* A pointer to the account to add
     * @return bool True if addition was successful, otherwise false
     */
    bool AddAccount(Account *account);
    /**
     * Get the Account associated with the ID
     * @param accountID int The ID of the Account
     * @return Account* A pointer associated to the Account
     */
    Account* GetAccount(const int &accountID ) const;
    /**
     * Check if the AccountManager is empty
     * @return bool True if the AccountManager is empty, otherwise false
     */
    bool isEmpty()const;
    /**
     * Print out all the accounts stored in AccountManager to the console
     */
    void Display() const;

private:
    /**
     * Underlying BSTree storing all the accounts. It sort them by their ID
     */
    BSTree accounts;
};
#endif //ASSIGNMENT6_ACCOUNTMANAGER_H
