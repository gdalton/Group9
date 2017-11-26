
/* filename: accountManager.cpp
 * Programmers: Dmitri Murphy, (Add your name here)
 * Class Number: CS-300
 * Date: 22NOV17
 * Purpose:
 * @todo
 */

#include "mainHeader.h"


    
//Constructors and Destructors
accountManager::accountManager(){
    
    loadDataFromDisk();
    
}
accountManager::accountManager(const accountManager & toCopy){
    
}

accountManager::~accountManager(){
    
}

//Add/Remove Functionality
bool accountManager::addAccount(Account* toAdd, ACCOUNT_TYPE type){
    return false;
}
bool accountManager::removeAccount(string* accountID, ACCOUNT_TYPE type){
    return false;
}

//Account Edit Functionality
bool accountManager::editAccount(string* accountID, Account* newAccount, ACCOUNT_TYPE type){
    return false;
}

//Get single account Functionality
Account* accountManager::getAccount(string* accountID, ACCOUNT_TYPE type){
    return NULL;
}


//Get all Accounts
map<string, Account>* accountManager::getAllAccounts(ACCOUNT_TYPE type){
    return NULL;
}


//Display all accounts
void accountManager::displayAllAccounts(ACCOUNT_TYPE type){
    
}


//Private Function
bool accountManager::loadDataFromDisk(){
    
    return false;
}






