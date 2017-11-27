
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

    //Load any existing member data from the disk
    loadDataFromDisk();
}
accountManager::accountManager(const accountManager & toCopy){
    
    memberTree = toCopy.memberTree;
    providerTree = toCopy.providerTree;
    managerTree = toCopy.managerTree;
}

accountManager::~accountManager(){
    // No action needed -
    // map destructors should delete the data
}


/**
 * Function to add an account to the database
 * @param  toAdd (account to add), accountType (type of account)
 * @return             True if the account is added, False otherwise
 */
bool accountManager::addAccount(Account* toAdd, ACCOUNT_TYPE type){
    bool toReturn = false;
    string* memberID = toAdd->getID();

    //Make sure account type matches ID number
    if(checkAccountType(memberID, type)){

        //Add the account
        switch (type) {
            case member:
                memberTree[*memberID] = toAdd;
                toReturn = true;
                break;

            case provider:
                providerTree[*memberID] = toAdd;
                toReturn = true;
                break;

            case manager:
                managerTree[*memberID] = toAdd;
                toReturn = true;
                break;

            default:
                toReturn = false;
                break;
        }
    }

    return toReturn;
}



/**
 * Function to remove an account from the database
 * @param  accountID (account to remove), accountType (type of account)
 * @return             True if the account is removed, False otherwise
 */
bool accountManager::removeAccount(string* accountID, ACCOUNT_TYPE type){
    bool toReturn = false;

    //Make sure account type matches ID number
    if(checkAccountType(accountID, type)){
        
        //Add the account
        switch (type) {
            case member:
                delete memberTree[*accountID];
                memberTree.erase(*accountID);
                toReturn = true;
                break;
                
            case provider:
                delete providerTree[*accountID];
                providerTree.erase(*accountID);
                toReturn = true;
                break;
                
            case manager:
                delete providerTree[*accountID];
                providerTree.erase(*accountID);
                toReturn = true;
                break;
                
            default:
                toReturn = false;
                break;
        }
    }
    return toReturn;
}




/**
 * Function to edit (replace) an account in the database
 * @param  accountID (account to edit), newAccount(account to add), accountType (type of account)
 * @return             True if the account is replaced, False otherwise
 */
bool accountManager::editAccount(string* accountID, Account* newAccount, ACCOUNT_TYPE type){
    bool toReturn = false;
    
    //@todo - make sure that member already exists
    
    //Make sure account type matches ID number
    if(checkAccountType(accountID, type)){
        
        //Add the account
        switch (type) {
            case member:
                //Free memory
                delete memberTree[*accountID];
                
                //Reset the account
                memberTree[*accountID] = newAccount;
                toReturn = true;
                break;
                
            case provider:
                //Free memory
                delete providerTree[*accountID];
                
                //Reset the account
                providerTree[*accountID] = newAccount;
                toReturn = true;
                break;
                
            case manager:
                //Free memory
                delete managerTree[*accountID];
                
                //Reset the account
                managerTree[*accountID] = newAccount;
                toReturn = true;
                break;
                
            default:
                toReturn = false;
                break;
        }
    }
    
    return toReturn;
}

/**
 * Function to get a single account from the database
 * @param  accountID (Id number of the account to get), accountType (type of account)
 * @return             Account* (pointer) if account is found, NULL otherwise
 */
Account* accountManager::getAccount(string* accountID, ACCOUNT_TYPE type){
    Account* toReturn = NULL;
    //Make sure account type matches ID number
    if(checkAccountType(accountID, type)){
        
        //Add the account
        switch (type) {
            case member:
                toReturn=memberTree[*accountID];
                break;
                
            case provider:
                toReturn=providerTree[*accountID];
                break;
                
            case manager:
                toReturn=managerTree[*accountID];
                break;
                
            default:
                toReturn = NULL;
                break;
        }
    }
    return toReturn;
}


/**
 * Function to return a tree of all accounts from the database
 * @param              accountType (type of account to get)
 * @return             map* if successful, NULL otherwise
 */
map<const string, Account*>* accountManager::getAllAccounts(ACCOUNT_TYPE type){
    
    map<const string, Account*>* toReturn = NULL;
    
    //Find the right tree and return a copy
    switch (type) {
        case member:
            //Create a new tree
            toReturn = new map<const string, Account*>;
            
            //Copy the tree over (using map's copy constructor)
            *toReturn = memberTree;
            break;
            
        case provider:
            //Create a new tree
            toReturn = new map<const string, Account*>;
            
            //Copy the tree over (using map's copy constructor)
            *toReturn = providerTree;
            break;
            
        case manager:
            //Create a new tree
            toReturn = new map<const string, Account*>;
            
            //Copy the tree over (using map's copy constructor)
            *toReturn = managerTree;
            break;
            
        default:
            toReturn = NULL;
            break;
    }

    return toReturn;
}


//Display all accounts
void accountManager::displayAllAccounts(ACCOUNT_TYPE type){
    
}


//Private Function
bool accountManager::loadDataFromDisk(){
    
    return false;
}

bool accountManager::checkAccountType(string* idNumber, ACCOUNT_TYPE type){
    bool toReturn = true;

    
    return toReturn;
}






