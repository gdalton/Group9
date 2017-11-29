//  CS300 - Group 9
//  Filename: mainHeader.h


//General Include
#include "standardHeader.h"
#include "list" //http://www.cplusplus.com/reference/list/list/
#include "string" //http://www.cplusplus.com/reference/string/string/
#include "Account.h"
#include <map>
#include <time.h> // time_t
#include <sstream> // stringstream http://www.cplusplus.com/reference/sstream/stringstream/


using namespace std;


/* Structs to be used Globally
 *
 *
 */

struct Service { 
        string * serviceID;
        string * name;
        float fee;
};

struct eft { 
        string providerName;
        string providerID;
        float totalFee; 
};

/**Report Structs**/

struct membersReport {
    string memberName;
    string memberID;
    address theAddress;
};

struct providersReport {
    string providerName;
    string providerID;
    address theAddress;
    int consultations;
    float weekFee;
};

struct managersReport {
    map < string, map < int, float > > providerDetails;//<providerID, <numMembersSeen, feesDue>
    float totalFees;
};


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
    map<const string, Account* >* getAllAccounts(ACCOUNT_TYPE type);
    void displayAllAccounts(ACCOUNT_TYPE type); //For testing...
    
    
    private:
    bool loadDataFromDisk();
    bool checkAccountType(string* idNumber, ACCOUNT_TYPE type);
    string* generateAccountID(ACCOUNT_TYPE type);
    map<const string, Account*> memberTree;
    map<const string, Account*> providerTree;
    map<const string, Account*> managerTree;
    
    //See for refrence: http://en.cppreference.com/w/cpp/container/map
};

class providerDirectory{
public:
    providerDirectory ( void );
    providerDirectory ( const providerDirectory & toCopy );
    ~providerDirectory ( void );

    list < Service > getDirectory ( void );
    bool addService ( Service addedService);
    bool removeService ( string * serviceID);
    bool displayService ( string * serviceID);
    bool updateFee ( string * serviceID, float newFee);

private:
    list < Service > directory;
};



class reportManager{
public:
    reportManager ( void );
    reportManager ( const reportManager & toCopy );
    ~reportManager ( void );

    managersReport managerReport ( map < string, Provider > );
    providersReport providerReport ( Provider * );
    membersReport memberReport ( Member * );
    list < providersReport >  providerAllReports ( map < string, Provider > );
    list < membersReport > memberAllReports ( map < string, Member > );
    eft generateEFT ( Provider * );
};

class Warden { 
public:
    Warden ( void );
    Warden ( const Warden & toCopy );
    ~Warden ( void );

    bool addCredential ( string newUsername, string newPassword);
    bool updateCredential ( string newUsername, string newPassword);
    bool deleteCredential ( string newUsername, string newPassword);
    bool validateLogin ( string, string );
    bool checkLoginAttempts ( int );
    bool addLog ( string logToAdd);
    bool checkActive ( void );

private:
    time_t currentTime;
    time_t referenceTime;
    //list < string [ 2 ] > systemCredentials;
    list < string > userActions; //could probably just make this a string ( not a list of strings )
    FILE * logFile;
    int loginAttempts;
};

class UserInterface {
public:
    UserInterface ( void );
    UserInterface ( const UserInterface & toCopy );
    ~UserInterface ( void );

    string currentUser;
    int clearanceLevel;

private:
    bool runSystem ( void );
    bool runProviderMenu ( void );
    bool runManagerMenu ( void );

    Warden warden;
    accountManager accounts;
    providerDirectory directory;
    reportManager reports;
    fileSystem database;
    float timeInactive;
};
