//  CS300 - Group 9
//  Filename: mainHeader.h


//General Include
#include "standardHeader.h"
#include "list" //http://www.cplusplus.com/reference/list/list/
#include "string" //http://www.cplusplus.com/reference/string/string/
#include "Account.h"
#include <map>


using namespace std;


/* Structs to be used Globally
 *
 *
 */


//-----------------------------
//  File System Class
//  - reads/writes to/from the file system
//-----------------------------
class fileSystem{
    public:
        
        //Constructor and Destructor
        fileSystem();
        ~fileSystem();
        
        //Read out to a file
        bool write(const char* dataToReadOut, const char* filename);
        
        //Read in from a file
        bool read(char* & allData, int length, const char* fileName);
    
        //Test Function to run the class's test suite 
        bool testFileSystem();
    
    private:
    
};


/* Account Manager Class 
 *
 */


class accountManager{
    
    public:
    
    //Constructors and Destructors
    accountManager();
    accountManager(const accountManager & toCopy);
    ~accountManager();
    
    //Add/Remove Functionality
    bool addAccount(Account* toAdd, ACCOUNT_TYPE type);
    bool removeAccount(string* accountID, ACCOUNT_TYPE type);
    bool editAccount(string* accountID, Account* newAccount, ACCOUNT_TYPE type);
    Account* getAccount(string* accountID, ACCOUNT_TYPE type);
    map<string, Account>* getAllAccounts(ACCOUNT_TYPE type);
    void displayAllAccounts(ACCOUNT_TYPE type); //For testing...
    
    
    private:
    bool loadDataFromDisk();
    map<string, Member> memberTree;
    map<string, Provider> providerTree;
    map<string, Manager> managerTree;
    
    //See for refrence: http://en.cppreference.com/w/cpp/container/map
};



class providerDirectory{
public:


private:
    list <providerRecord> allRecords;
};



class reportManager{

};



