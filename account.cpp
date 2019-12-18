/**
 * Account class .cpp file. This class represents a customer banking account. It uses an array of constant strings to
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

#include <iostream>
#include "account.h"

/**
 * Operator << overloader.  Stores the funds and balance per fund of the account in a ostream
 * @param os The ostream
 * @param other Account The Account to print Name, ID and balance from
 * @return ostream
 */
ostream &operator<<(ostream &os, const Account &other) {
    os << other.GetFirstName() << " " << other.GetLastName() << " Account ID: " << other.GetID() << endl;
    string temp;
    int i=0;
    for(auto elem: other.balancePerFund){

        os << '\t' << FUNDS[i] << ": $" << other.balancePerFund.at(FUNDS[i]) << endl;

        i++;
    }
        return os;
}
/**
 * Class constructor
 */
Account::Account() {

    ID = 0;
    firstName = "";
    lastName = "";

    transactionsHistory.resize(MAX_FUNDS);

    for (const auto & i : FUNDS) {
        balancePerFund.insert(pair<string, double>(i, 0));
    }
}
/**
 * Account constructor. Take the first name, last name and Id of the account holder.
 * @param firstName  string The first name of the account holder
 * @param lastName  string The last name of the account holder
 * @param ID int The id of the account
 */
Account::Account(string firstName, string lastName, int ID):firstName(firstName),lastName(lastName), ID(ID)  {

    for (int i = 0; i <MAX_FUNDS ; ++i) {
        balancePerFund.insert(pair<string, double>(FUNDS[i], 0));
    }
    transactionsHistory.resize(MAX_FUNDS);
}
/**
* Set first name and last name of the current account
* @param firstName string The first name of the account holder
* @param lastName string The last name of the account holder
*/
void Account::SetName(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName=lastName;
}
/**
* Set the id of the current account
* @param ID int The account id
*/
void Account::SetID(int ID) {
    this->ID=ID;
}
/**
* Get the first name of the account holder
* @return string The first name of the account holder
*/
string Account::GetFirstName() const {
    return firstName;
}
/**
* Get the last name of the account holder
* @return string The last name of the account holder
*/
string Account::GetLastName() const {
    return lastName;
}
/**
 * Get the ID of the account
 * @return  int The ID of the account
 */
int Account::GetID() const {
    return ID;
}
/**
 * Class destructor
 */
Account::~Account() {

}
/**
* Update the balance in the fund
* @param fundNum int The fund to update
* @param amount int The new balance of the fund
* @return bool True if update was successful, otherwise false
*/
bool Account::UpdateFund(const int &fundNum, double amount)  {
    balancePerFund[FUNDS[fundNum]] = amount;
    return true;
}
/**
* Get the current balance of a fund
* @param fundNum int The fund
* @return double The balance of the fund
*/
double Account::GetFundBalance(const int &fundNum) const {

    double temp = balancePerFund.at(FUNDS[fundNum]);

    return  temp;
}
/**
* Update the history of transactions of a fund
* @param fundType int The fund to update
* @param transaction string The latest transaction to add in the vectors
*/
void Account::UpdateAccountHistory(const int &fundType, const string &transaction){
    vector<string> temp = transactionsHistory.at(fundType);
   transactionsHistory.at(fundType).push_back(transaction);
}
/**
 * Get the history of transactions of a particular fund
 * @param fund int The fund to get transactions history from
 * @return vector<string> The transactions performed in the fund
 */
const vector<string> Account::GetFundTransactionHistory(const int &fund)const {
    return transactionsHistory.at(fund);
}
/**
 * Get the max amount of fund accounts the customer can have in their account
 * @return int The max number of funds
 */
int Account::GetMaxFunds()const {
    return MAX_FUNDS;
}
/**
 * Get the name of a fund
 * @param fund int The fund to get the name of
 * @return string The name of the fund
 */
const string Account::GetFundName(int &fund) const {
    return FUNDS[fund];
}
