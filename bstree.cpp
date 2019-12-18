/**
 * Class .cpp file. This class represents a binary search tree that stores pointers of Accounts. The BSTree sorts
 * the Accounts by the ID number.
 * It allows to insert and retrieve an Account pointer. It  displays all the Accounts, check if the BSTree is empty, and
 * deletes all items in the BSTree.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */
#include <iostream>
#include "bstree.h"
/**
 * BSTree constructor
 */
BSTree::BSTree() {
    root = nullptr;
}
/**
 * Class destructor
 */
BSTree::~BSTree() {
    Empty();

}
/**
 * Node constructor
 */
BSTree::Node::Node()
{
    pAcct = nullptr;
    left = nullptr;
    right = nullptr;
}
/**
 * Node constructor
 * @param account Account pointer The Account pointer to save in the node
 */
BSTree::Node::Node(Account* account)
{
    pAcct = account;
    left = nullptr;
    right = nullptr;
}
/**
 * Node destructor
 */
BSTree::Node::~Node() {

    delete pAcct;
    left = nullptr;
    right = nullptr;
    pAcct = nullptr;
}
/**
 * Insert an Account pointer in the BSTree. The BSTree sorts the Accounts by their ID number. No duplicates are allowed.
 * If there is an account that has the same ID number as the one from acc, the function returns false.
 * @param acc Account pointer The Account pointer to insert
 * @return True if insertion was successful, otherwise false
 */
bool BSTree::Insert(Account *acc) {

    if(root == nullptr){ //If the BSTree is empty
        Node *temp = new Node(acc);
        root = temp;
        return true;
    }
    bool insertSuccess = false;

    insertHelper(acc, root, insertSuccess);
    return insertSuccess;
}
/**
 * Insert recursive function helper. It goes down the BSTree, looking for the right place where to place the new
 * Account pointer. If it finds an existing Account pointer with the same ID as acc
 * returns false.
 * @param acc Account pointer The Account to insert
 * @param currRoot  Node pointer current root in stack call
 * @param success   bool Flag to identify if the insertion was successful
 * @return Node pointer A pointer of a Node to link to the previous ones
 */
BSTree::Node *BSTree::insertHelper(Account *acc, BSTree::Node *currRoot, bool &success) {
    if(currRoot == nullptr){
        Node *temp = new Node(acc);
        currRoot = temp;
        success = true;
        return temp;

    }else{

        if(acc->GetID() == currRoot->pAcct->GetID()){
            success = false;
            return currRoot;

        }else if(acc->GetID() < currRoot->pAcct->GetID()){
            currRoot->left = insertHelper(acc, currRoot->left, success);
        }else if (acc->GetID() > currRoot->pAcct->GetID()){
            currRoot->right = insertHelper(acc, currRoot->right, success);
        }
    }
    return currRoot;
}
/**
 * Retrieve an Account pointer by using a place holder variable, acc, and passing it as a parameter.
 * @param id int The ID number of the Account to retrieve
 * @param acc Acount Pointer Place holder which will hold the reference of the Account pointer to retrieve
 * once this one is found
 * @return True if retrieval is successful, false otherwise
 */
bool BSTree::Retrieve(const int &id, Account *&acc) const {
    Node *temp = root;
    return retrieveHelper(id, acc, temp);
}
/**
 * Retrieve recursive helper function. It goes down the BSTree until it finds the
 * Account pointer to retrieve, or until it hits nullptr.
 * @param id int The ID of the account to retrieve
 * @param acc Account Pointer Place holder which will hold the reference of the Account pointer to retrieve
 * once this one is found
 * @param temp  Node pointer Current root
 * @return True if retrieval is successful, false otherwise
 */
bool BSTree::retrieveHelper(const int &id, Account *&acc, Node *temp) const{

    if(temp == nullptr){
        acc = nullptr;

        return false;
    }

    if(temp->pAcct->GetID() == id){
        acc = temp->pAcct;
        return true;

    }else{
        if(id < temp->pAcct->GetID()){
            return retrieveHelper(id, acc, temp->left);
        }else{
            return retrieveHelper(id, acc, temp->right);
        }
    }
}
/**
 * Display all the BSTree items
 */
void BSTree::Display() const {
    displayHelper(root);
}
/**
 * Display recursive helper function. It traverses the tree inorder, printing out the BSTree content
 * @param root Node pointer The current root
 */
void BSTree::displayHelper(Node *root)const {
    if(root != nullptr){
        displayHelper(root->left);
        cout << *root->pAcct << endl;
        displayHelper(root->right);
    }
}

void BSTree::Empty() {
    if(root != nullptr){
        emptyHelper(root);
    }
    root = nullptr;

}
/**
 * Empty recursive helper function. Iterates the tree in post-order order, deleting all the tree nodes
 * @param root
 */
void BSTree::emptyHelper(BSTree::Node *root)const {
    if(root != nullptr){

        emptyHelper(root->left);

        emptyHelper(root->right);

        delete root;
    }
}
/**
 * Check if the BSTree is empty
 * @return True if the tree is empty, otherwise false
 */
bool BSTree::isEmpty() const {
    return root == nullptr;
}