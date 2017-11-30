
#include "gtest/gtest.h"
#include "../mainHeader.h"

//File for Account Testing 
TEST(accountTesting, allUsersExistInTable) {
    accountManager testAccountManager = accountManager();
    ifstream allAccounts;
    ifstream account;
    allAccounts.open("../accounts/allIDs.txt");
    ASSERT_TRUE(allAccounts) << "Failed to open allIDs.txt" << endl;
    while(!allAccounts.eof())
    {
        char accountID [20];
        allAccounts.getline(accountID, 20, '\n');
        ACCOUNT_TYPE type = init;
        if(accountID[0] == '1'){
            type=manager;
        }
        else if(accountID[0] == '2'){
            type=provider;
        }
        else type = member;

        char temp [60] = "../accounts/";
        strcat(temp,accountID);
        account.open(temp);//Dynamically opens file
        ASSERT_TRUE(account) << "Failed to open " << temp;
        //Stop if account not found
        if(!account) continue;
        
        account.getline(accountID, 20, '\n');
        account.get();

        string * stringAccountID = new string(accountID);
        ASSERT_TRUE(testAccountManager.getAccount(stringAccountID, type) != NULL) << "Account failed to load " << accountID;
        delete stringAccountID;
    }
}

TEST(accountTesting, canLogin) {
    
    accountManager testAccountManager = accountManager();
    string * userID = new string("224938990");

    ACCOUNT_TYPE type = ( ACCOUNT_TYPE ) ( userID->at ( 0 ) - '0' );
    Account * account = testAccountManager.getAccount(userID, type);

    ASSERT_TRUE(type == provider) << "Failed to get proper user type" << endl;
    ASSERT_TRUE(account != NULL) << "Failed to login to test account " << *userID;
    delete userID;
}