
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
    string filename("accounts/"+*memberID+".txt");
    
    //Check that we aren't overriding an account
    if(allIdNumbers.find(*memberID) != allIdNumbers.end()){
        return false; //Stop and return if account exists
    }

    //Make sure account type matches ID number
    if(checkAccountType(memberID, type)){

        //Add the account
        switch (type) {
            case member:
                memberTree[*memberID] = toAdd;
                toReturn = fileSys.writeSTR(*(static_cast<Member*>(toAdd)->writeToString()), filename);
                break;

            case provider:
                providerTree[*memberID] = toAdd;
                toReturn = fileSys.writeSTR(*(static_cast<Provider*>(toAdd)->writeToString()), filename);
                
                break;

            case manager:
                managerTree[*memberID] = toAdd;
                toReturn = fileSys.writeSTR(*(static_cast<Manager*>(toAdd)->writeToString()), filename);
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
    string filename("accounts/"+*accountID+".txt");
    accountMap::iterator it;
    
    //Make sure that member already exists
    if(allIdNumbers.find(*accountID) == allIdNumbers.end()){
        return true; //Stop and return if it does not exist
    }
    
    //Make sure account type matches ID number
    if(checkAccountType(accountID, type)){
        
        //Add the account
        switch (type) {
            case member:
                //Delete from tree and file system
                delete memberTree[*accountID];
                memberTree.erase(*accountID);
                if(remove(filename.c_str()) == 0)
                    toReturn = true;
                break;
                
            case provider:
                delete providerTree[*accountID];
                providerTree.erase(*accountID);
                if(remove(filename.c_str()) == 0)
                    toReturn = true;
                break;
                
            case manager:
                delete providerTree[*accountID];
                providerTree.erase(*accountID);
                if(remove(filename.c_str()) == 0)
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
    
    //Make sure that member already exists
    if(allIdNumbers.find(*accountID) == allIdNumbers.end()){
        return false; //Stop and return if does not exist
    }
    
    //Make sure account type matches ID number
    if(checkAccountType(accountID, type)){
        
        //Add the account
        switch (type) {
            case member:
                //Free memory
                delete memberTree[*accountID];
                
                //Reset the account
                memberTree[*accountID] = newAccount;
                if(memberTree.find(*accountID)  != memberTree.end())
                    toReturn = true;
                break;
                
            case provider:
                //Free memory
                delete providerTree[*accountID];
                
                //Reset the account
                providerTree[*accountID] = newAccount;
                if(providerTree.find(*accountID)  != providerTree.end())
                    toReturn = true;
                break;
                
            case manager:
                //Free memory
                delete managerTree[*accountID];
                
                //Reset the account
                managerTree[*accountID] = newAccount;
                if(managerTree.find(*accountID)  != managerTree.end())
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
 * @param              type (type of account to get)
 * @return             map* if successful, NULL otherwise
 */
accountMap* accountManager::getAllAccounts(ACCOUNT_TYPE type){
    
    map< string, Account*>* toReturn = NULL;
    
    //Find the right tree and return a copy
    switch (type) {
        case member:
            //Create a new tree
            toReturn = new map< string, Account*>;
            
            //Copy the tree over (using map's copy constructor)
            *toReturn = memberTree;
            break;
            
        case provider:
            //Create a new tree
            toReturn = new map< string, Account*>;
            
            //Copy the tree over (using map's copy constructor)
            *toReturn = providerTree;
            break;
            
        case manager:
            //Create a new tree
            toReturn = new map< string, Account*>;
            
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


bool accountManager::checkAccountType(string* idNumber, ACCOUNT_TYPE type){
    bool toReturn = true;
    
    //Check account number
    
    
    return toReturn;
}

//Private Function
bool accountManager::loadDataFromDisk(){
    
    ifstream allAccounts;
    ifstream account;
    ACCOUNT_TYPE type = init;
    infoStruct newStruct;
    Account* newAccount = NULL;
    allAccounts.open("accounts/allIDs.txt");//allIDs.txt is a file full of filenames
    char temp [50] = "accounts/";
    
    // Get all accounts
    char accountID [20];
    char name [100];
    char email [100];
    Address * theAddress = NULL;
    char streetAdress [100];
    char  city [100];
    char  state [10];
    char  zipcode [10];
    char status [50];
    char password [50];
    char currentDate [50];
    char memberID[12];
    char providerID[12];
    char serviceCode[25];
    char comments[1000];
    char serviceDate [50];
    char providerName [100];
    char serviceName [100];
    char memberName [75];
    int membersSeen = 0;
    float serviceFee = 0;
    MEMBER_STATUS memStatus = current;

    //Member record data
    memberRecordList* memberRecords = NULL;

    //Loop over each line (each line is a filename)
    while (allAccounts){
        allAccounts.get(accountID, 20,'\n');//accountID is a filename stored on a line
        allAccounts.get();
        //Look for data file
        
        char temp [50] = "accounts/";
        strcat(temp,accountID);
        account.open(temp);//Dynamically opens file
        
        //Stop if account not found
        if(!account) continue;
        
        account.get(accountID, 20, '\n');
        account.get();
        
        //Set the type
        if(accountID[0] == '1'){
            type=manager;
        }
        else if(accountID[0] == '2'){
            type=provider;
        }
        else type = member;
        
        
        // Get The Core Info About An Account 
        theAddress = new Address;
        memberRecords = new list<memberRecord>;
        
        //Get Core Info
        account.get(name, 100, '\n');
        account.get();
        account.get(email, 100, '\n');
        account.get();
        account.get(streetAdress,100,'^');
        account.get();
        account.get(city,100,'^');
        account.get();
        account.get(state,10,'^');
        account.get();
        account.get(zipcode,10,'\n');
        account.get();
        
        
        //****************************
        //Read in unique MEMBER info
        //****************************
        if(type == member){
            
            //Get member status
            account.get(status, 50, '\n');
            account.get();
            
            //Convert to bool
            if(strcmp(status, "Current") == 0)
                memStatus = current;
            else
                memStatus = expired;
                
            
            //Create a new record list
            memberRecords = new memberRecordList;
            
            while(!account.eof())
            {
                //Member record to fill in
                memberRecord memREC;
                
                if(account.get() != '^') //Check that record exists on line
                    break;
                
                //Read in all member record information
                account.get(serviceDate, 50, '^');
                account.get();  //Get the ^
                account.get(providerName, 100, '^');
                account.get();  //Get the ^
                account.get(serviceName,100,'\n');
                account.get();  //Get the \n
                
                //Add Info to record list
                memREC.dateOfService = serviceDate;
                memREC.providerName = providerName;
                memREC.serviceName = serviceName;
                memberRecords->insert(memberRecords->begin(), memREC);
            }

            
            newAccount = new Member(new string(name), new string(email), new string(accountID), new Address(new string(streetAdress), new string(city), new string(state),new string(zipcode)),member, memStatus, memberRecords);
            
            //Clear Memory
            delete memberRecords;
            
        }
        
        //****************************
        //Read in unique PROVIDER info
        //****************************
        if(type == provider){
            
            //Get provider password
            account.get(password, 50, '\n');
            account.get();
            
            //Get number of members seen
            account >> membersSeen;
            account.get();
            
            //Create a new record list
            providerRecordList provList;
            
            while(!account.eof())
            {
                //Member record to fill in
                providerRecord provREC;
                
                if(account.get() != '^') //Check that record exists on line
                    break;
                
                //Read in all member record information
                account.get(currentDate, 50, '^');
                account.get();  //Get the ^
                account.get(serviceDate, 50, '^');
                account.get();  //Get the ^
                account.get(providerID, 12, '^');
                account.get();  //Get the ^
                account.get(memberID, 12, '^');
                account.get();  //Get the ^
                account.get(serviceCode,25,'^');
                account.get();  //Get the ^
                account >> serviceFee;
                account.get();  //Get the ^
                account.get(comments,1000,'^');
                account.get();  //Get the ^
                account.get(memberName, 75, '\n');
                account.get();  //Get the \n

                
                //Add Info to record list
                provREC.currentDateTime = currentDate;
                provREC.dateOfService = serviceDate;
                provREC.providerID = providerID;
                provREC.memberID = memberID;
                provREC.serviceCode = serviceCode;
                provREC.comments = comments;
                provREC.serviceFee = serviceFee;
                provREC.memberName = memberName;
           
                provList.push_back(provREC);
                
            }
            
           
            newAccount = new Provider(new string(name), new string(email), new string(accountID), new Address(new string(streetAdress), new string(city), new string(state),new string(zipcode)),provider, new string(password), membersSeen , provList);
            
        }

        //****************************
        //Read in unique MANAGER info
        //****************************
        if(type == manager){
            
            //Get manager password
            account.get(password, 50, '\n');
            account.get();
            
            newAccount = new Manager(new string(name), new string(email), new string(accountID), new Address(new string(streetAdress), new string(city), new string(state),new string(zipcode)),manager, new string(password));
        }
        
        
        //Add the account
        addAccount(newAccount, type);
        
        //Log the account ID Number
        allIdNumbers.insert(accountID);
        
        //Close the Account File
        account.close();
    }
    
    //Close the list of all Accounts
    allAccounts.close();
    
    
    return true;
}




/* Function to generate a user ID
 * @param     accountType (type of account)
 * @return    Account ID as a string
 * Algorithm:
  1. Select the first digit based upon account type.
    a. Select 1 if manager.
    b. Select 2 if provider.
    c. If type is member, select a number between 3 and 9 randomly.
    2. Select the next 6 digits randomly.
  3. The final two digits are the sum of all the preceding digits.
  4. Check that the ID number is not already in use.
    a. If it is, restart at step 1.
    b. Otherwise, return the ID number as a valid identification number.
 */
string* accountManager::generateAccountID(ACCOUNT_TYPE type){

    string* toReturn = new string("");
    int random = 0;
    bool again = false;

    do{
        //Select FIRST DIGIT
        switch (type){
            case manager:
                *toReturn += "1";
                break;
            case provider:
                *toReturn += "2";
                break;
            case member:
                random = rand() % 6 + 3;
                *toReturn += toString(random);
                break;
            default:
                again = true;
                break;
        }

        //Generate next EIGHT DIGITS
        random = (rand() % 89999999)+10000000;
        
        //Add them to sum and ID string
        *toReturn += toString(random);

        //Check that ID is not already assigned
        if(allIdNumbers.find(*toReturn) == allIdNumbers.end()){
            //If everything ok, go out of function
            again = false;

        } else { //Reset if ID already exists
            //Delete String
            delete toReturn;
            toReturn = new string("");

            //Reset counters
            random = 0;

            //Signal to do again
            again = true;
        }
    } while (again);

    //Add the ID number to ID tracker
    allIdNumbers.insert(*toReturn);

    //Return User ID
    return toReturn;
}








void accountManager::generateRandomAccounts(int amount){
    
    int counter = 0;
    int random = 0;
    string* id = NULL;
    ofstream fileOut;
    //12 names
    string names [] = {"Waylon Dalton","Marcus Cruz","Justine Henderson","Thalia Cobb","Mathias Little","Steve Lang","Hadassah Hartman","Joanna Shaffer","Jimmy Fallon", "Steve Jobs","John Oliver","John Stewart"};
    string emails [] = {"w@pdx.edu","M@pdx.edu","J@pdx.edu","Th@pdx.edu","Ma@pdx.edu","S@pdx.edu","Had@pdx.edu","Joan@pdx.edu","Jimmy@pdx.edu", "Steve@pdx.edu","John@pdx.edur","John@pdx.edu"};
    string address [] = {"4 Goldfield Rd.^Honolulu^HI^96815","5 Goldfield Rd.^Honolulu^HI^96815","6 Goldfield Rd.^Honolulu^HI^96815","7 Goldfield Rd.^Honolulu^HI^96815","8 Goldfield Rd.^Honolulu^HI^96815","9 Goldfield Rd.^Honolulu^HI^96815","14 Goldfield Rd.^Honolulu^HI^96815","42 Goldfield Rd.^Honolulu^HI^96815","64 Goldfield Rd.^Honolulu^HI^968155", "47 Goldfield Rd.^Honolulu^HI^96815","74 Goldfield Rd.^Honolulu^HI^96815","34 Goldfield Rd.^Honolulu^HI^96815"};
    string status []  = {"Current","NotCurrent"};
    string dateOfService = currentDateTime();
    string providerName = "NoChoc!";
    string serviceName = "0.5lbs Choclate";
    string passwords [] = {"zx9QzHHgv5", "ib6BmXPKIh", "KBwgjUrZCc", "60o1krBXwQ","Ibgr2oUFdC"};
    
/*
    //TO CREATE MANAGER ACCOUNTS
    while(counter<amount){
        //Generate random
        random = rand() % 12;
        id = generateAccountID(manager); //CHANGE MANUALLY
        
        fileOut.open ("accounts/"+*id+".txt");
        fileOut << *id <<"\n";
        fileOut << names[random]<<"\n";
        
        random = rand() % 12;
        fileOut << emails[random]<<"\n";
        
        random = rand() % 12;
        fileOut << address[random]<<"\n";
        
        random = rand() % 12;
        if(random % 5 == 0) random = 1;
        else random=0;
        
        
        //Password
        random = rand() % 4;
        fileOut << passwords[random]<<"\n";
        
        fileOut.close();
        
        delete id;
        
        ++counter;
    }

    
    */

    //TO CREATE PROVIDER ACCOUNTS
/*
    while(counter<amount){
        //Generate random
        random = rand() % 12;
        id = generateAccountID(provider); //CHANGE MANUALLY
        
        fileOut.open ("accounts/"+*id+".txt");
        fileOut << *id <<"\n";
        fileOut << names[random]<<"\n";
        
        random = rand() % 12;
        fileOut << emails[random]<<"\n";
        
        random = rand() % 12;
        fileOut << address[random]<<"\n";
        
        random = rand() % 12;
        if(random % 5 == 0) random = 1;
        else random=0;
        

        //Password
        random = rand() % 4;
        fileOut << passwords[random]<<"\n";
        
        //Member's seen
        fileOut << rand() % 70<<"\n";
        
        //Provider Records
        fileOut <<"^"<<currentDateTime()<<"^";
        fileOut << currentDateTime()<<"^";
        fileOut << *id<<"^";
        fileOut << "467623877" <<"^";
        fileOut << "110" <<"^";
        fileOut << "15.5" <<"^";
        fileOut << "Good patient!" <<"^";
        fileOut << "Paul M." <<"\n";

        
        fileOut <<"^"<<currentDateTime()<<"^";
        fileOut << currentDateTime()<<"^";
        fileOut << *id<<"^";
        fileOut << "528777939" <<"^";
        fileOut << "120" <<"^";
        fileOut << "50.5" <<"^";
        fileOut << "Really addicted to dark choc..." <<"^";
        fileOut << "Dave W." <<"\n";
        
        fileOut.close();
        
        delete id;
        
        ++counter;
    }
    */
    
   //  TO CREATE MEMBER ACCOUNTS
    
/*
    while(counter<amount){
        //Generate random;
        random = rand() % 12;
        id = generateAccountID(member); //CHANGE MANUALLY
        
        fileOut.open ("accounts/"+*id+".txt");
        fileOut << *id <<"\n";
        fileOut << names[random]<<"\n";
        
        random = rand() % 12;
        fileOut << emails[random]<<"\n";
        
        random = rand() % 12;
        fileOut << address[random]<<"\n";
        
        random = rand() % 12;
        if(random % 5 == 0) random = 1;
        else random=0;
        
        fileOut << status[random]<<"\n";
        
        fileOut<<"^"<<dateOfService<<"^"<<providerName<<"^"<<serviceName<<"\n";
        fileOut<<"^"<<dateOfService<<"^"<<providerName<<"^"<<serviceName<<"\n";

        fileOut.close();
        
        delete id;
    
        ++counter;
    }
*/
    
}




