/**
 * Account class header file. This class represents a customer banking account. It uses an array of constant strings to
 * represent the name of each fund. To keep track of the balance per fund, it uses a map, pairing the name of the fund
 * from the const string array to its current balance. When a transaction is done in any of the funds, the transaction
 * stamp is stored in a vector of vector of strings, keeping a list of transactions per fund.
 * This class allows to get and set the first name and last name of the account holder, and the account id. It also has
 * getters for the name of each fund, the max amount of funds existing in the account, a fund current balance and a fund
 * history of transactions vector.
 * To update the information of the account, this class allows to update a fund balance, and to update a history of
 * transactions.
 * Author:  Angela Ferro Capera
 * Date:    12/6/19
 */

#ifndef ASSIGNMENT6_ACCOUNT_H
#define ASSIGNMENT6_ACCOUNT_H
#include <string>
#include <vector>
#include <map>

using namespace std;
const int MAX_FUNDS = 10;
/**
 * Constant array representing name of possible funds
 */
const string FUNDS[MAX_FUNDS] = {
        "Money Market",
        "Prime Money Market",
        "Long-Term Bond",
        "Short-Term Bond",
        "500 Index Fund",
        "Capital Value Fund",
        "Growth Equity Fund",
        "Growth Index Fund",
        "Value Fund",
        "Value Stock Index"
};

class Account {
    /**
     * Operator << overloader
     * @param os The ostream
     * @param other Account The Account to print Name, ID and balance from
     * @return ostream
     */
    friend ostream& operator<<(ostream &os, const Account& other);

public:
    /**
     * Account default constructor
     */
    Account();
    /**
     * Account constructor. Take the first name, last name and Id of the account holder.
     * @param firstName  string The first name of the account holder
     * @param lastName  string The last name of the account holder
     * @param ID int The id of the account
     */
    Account(string firstName, string lastName, int ID);
    /**
     * Account destructor
     */
    ~Account();
    /**
     * Set first name and last name of the current account
     * @param firstName string The first name of the account holder
     * @param lastName string The last name of the account holder
     */
    void SetName(string firstName, string lastName);
    /**
     * Set the id of the current account
     * @param ID int The account id
     */
    void SetID(int ID);
    /**
     * Get the first name of the account holder
     * @return string The first name of the account holder
     */
    string GetFirstName()const;
    /**
     * Get the last name of the account holder
     * @return string The last name of the account holder
     */
    string GetLastName()const;
    /**
     * Get the ID of the current account
     * @return int The ID of the current account
     */
    int GetID()const;
    /**
     * Get the max amount of funds a customer can have in their account
     * @return int The max amount of funds
     */
    int GetMaxFunds()const;
    /**
     * Get the name of the fund
     * @param fund int The fund in the accout
     * @return string The name of the fund
     */
    const string GetFundName(int &fund)const;
    /**
     * Update the balance in the fund
     * @param fundNum int The fund to update
     * @param amount int The new balance of the fund
     * @return bool True if update was successful, otherwise false
     */
    bool UpdateFund(const int &fundNum , double amount);
    /**
     * Get the current balance of a fund
     * @param fundNum int The fund
     * @return double The balance of the fund
     */
    double GetFundBalance(const int &fundNum)const;
    /**
     * Get the history of transactions done in a particular fund
     * @param fund int The fund to get history of transactions from
     * @return vector<string> The history of transactions performed in the fund
     */
    const vector<string> GetFundTransactionHistory(const int &fund)const;
    /**
     * Update the history of transactions of a fund
     * @param fundType int The fund to update
     * @param transaction string The latest transaction to add in the vectors
     */
    void UpdateAccountHistory(const int &fundType, const string &transaction);

private:

    int ID;

    string firstName;
    string lastName;
    /**
     * Vector of vector of strings storing the transactions performed in each fund
     */
    vector<vector<string>> transactionsHistory;
    /**
     * Map storing pair of Fund and balance of the fund
     */
    map<string, double> balancePerFund;
};


#endif //ASSIGNMENT6_ACCOUNT_H
