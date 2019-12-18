/**
 * Class .cpp file. This class allows to read a file of transaction. As it reads the file, it create each transaction
 * and store it in a queue. After it has reach the end of the file, it starts processing each transaction dequeing the
 * queue. When all the transaction has been performed, it prints out the information of all the accounts and their funds
 * in the bank.
 * It allows to read a file of transactions, to process them, and to display them.
 * It uses an AccountManager to access the information of each account opened.
 * Author: Angela Ferro Capera
 * Date:    12/6/19
 */
#include <sstream>
#include <fstream>
#include "bank.h"
/**
 * Class constructor
 */
Bank::Bank() {

}
/**
 * Class destructor. Destroys each Transaction pointer stored in the transaction queue
 */
Bank::~Bank() {
    while (!transactions.empty())
    {
        Transaction *save = transactions.front();
        transactions.pop();
        delete save;
    }
}
/**
 * Create transactions by reading them from a file
 * @param FileName string The name of the file
 */
void Bank::createTransactions(const string &FileName) {

    ifstream file; //convert to an istream

    file.open(FileName);

    string readLine;

    if(!file){
        cerr<< "Invalid file name" << endl;
        exit(1);
    }

    while(!file.eof()){ // read until the end of file

        getline(file, readLine);
        stringstream ss (readLine);

        Transaction* currTrans = nullptr;

        char transactionType;

        ss >> transactionType;

        switch(transactionType){

            case OPEN:
                currTrans = new TransactionOpen(ss);
                transactions.push(currTrans);
                break;

            case DEPOSIT:
                currTrans = new TransactionDeposit(ss);
                transactions.push(currTrans);
                break;

            case WITHDRAW:

                currTrans = new TransactionWithdraw(ss);
                transactions.push(currTrans);
                break;
            case TRANSFER:

                currTrans = new TransactionTransfer(ss);
                transactions.push(currTrans);
                break;
            case HISTORY:

                currTrans = new TransactionHistory(ss);

                transactions.push(currTrans);
                break;
            default:
                cout <<":) ";
                delete currTrans;
            }

    }

    file.close();
}
/**
 * Process each transaction inside the queue of Transaction pointers
 */
void Bank::processTransaction() {
        while(!transactions.empty()){
               Transaction* temp = transactions.front();
            temp->PerformTransaction(accounts);
               transactions.pop();
               delete temp;
        }
}
/**
 * Display to console the information of each Account: Account holder name, account ID, Funds and their current balance
 */
void Bank::DisplayAccounts() const {
    accounts.Display();
}
