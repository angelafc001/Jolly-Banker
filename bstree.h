/**
 * Class header file. This class represents a binary search tree that stores pointers of Accounts. The BSTree sorts
 * the Accounts by the ID number.
 * It allows to insert and retrieve an Account pointer. It  displays all the Accounts, check if the BSTree is empty, and
 * deletes all items in the BSTree.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#ifndef ASSIGNMENT6_BSTREE_H
#define ASSIGNMENT6_BSTREE_H
#include "account.h"

class BSTree
{
public:
    /**
     * Constructor
     */
    BSTree();
    /**
     * Destructor
     */
    ~BSTree();
    /**
     * Insert  Account pointer in the BSTree
     * @param acc Account pointer
     * @return bool True if the insertion was successful; false if the BSTree contains the Account pointer already
     */
    bool Insert(Account *acc);
    /**
     * Retrieve a pointer to a Account reference
     * @param id int The ID number of the account to retrieve
     * @return bool True if the ID match an Account pointer, otherwise false
     */
    bool Retrieve(const int &id, Account * &) const;
    /**
     * Display to the console all the information of the Account pointers that the BSTree contains
     */
    void Display() const;
    /**
     * Delete all current Account pointers of BSTree
     */
    void Empty();
    /**
     * Check if BSTree is empty
     * @return bool True if BSTree is empty, otherwise false
     */
    bool isEmpty() const;

private:
    /**
     * Node inner struct. Node contains a pointer to an Account, a right pointer, and a left pointer
     */
    struct Node
    {
        Node();
        Node(Account* account);
        ~Node();
        Account *pAcct;
        Node *right;
        Node *left;
    };
    Node *root;
    /**
     * Insert recursive helper method. It inserts an Account pointer to the BSTree
     * @param acc Account pointer The account to insert
     * @param currRoot Node pointer The current root
     * @param success bool The status of the transaction
     * @return Node pointer A pointer to a Node
     */
    Node* insertHelper(Account *acc, Node *currRoot, bool &success);
    /**
     * Retrieve recursive helper method.
     * @param id The ID of the Account to retrieve
     * @param acc Account pointer Place holder for the pointer of the Account to retrieve
     * @param temp Node pointer The current node
     * @return bool True if the Account pointer was found, otherwise false
     */
    bool retrieveHelper(const int &id, Account *&acc, Node *temp) const;
    /**
     * Display recursive helper function. It prints the Account pointers contained in the BSTree nodes
     * @param root Node pointer The current root
     */
    void displayHelper(Node *root) const;
    /**
     * Empty recursive helper function. It goes through each node in the BSTree, delete its content, then deletes
     * the node
     * @param root Node pointer The current root
     */
    void emptyHelper(Node * root)const;
};
#endif //ASSIGNMENT6_BSTREE_H
