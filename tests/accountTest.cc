
#include "gtest/gtest.h"
#include "../mainHeader.h"

//File for Account Testing 
TEST(accountTesting, allUsersExistInTable) {
    accountManager testAccountManager = accountManager();
    ifstream allAccounts;
    ifstream account;
    allAccounts.open("../accounts/allIDs.txt");

    while(allAccounts)
    {
        char accountID [20];
        allAccounts.get(accountID, 20,'\n');
        allAccounts.get();
        ACCOUNT_TYPE type = init;
        if(accountID[0] == '1'){
            type=manager;
        }
        else if(accountID[0] == '2'){
            type=provider;
        }
        else type = member;

        char temp [50] = "accounts/";
        strcat(temp,accountID);
        account.open(temp);//Dynamically opens file
        
        //Stop if account not found
        if(!account) continue;
        
        account.get(accountID, 20, '\n');
        account.get();

        string * stringAccountID = new string(accountID);
        
        ASSERT_TRUE(testAccountManager.getAccount(stringAccountID, type) != NULL) << "Account failed to load " << accountID;
        delete stringAccountID;
    }
}

TEST(accountTesting, canLogin) {
    accountManager testAccountManager = accountManager();
    string userID = string("122475252");
    Account * account = testAccountManager.getAccount(&userID, ( ACCOUNT_TYPE ) ( userID.at ( 0 ) - '0' ) );
    ASSERT_TRUE(testAccountManager.getAccount(&userID, provider) != NULL) << "Account failed to load " << userID;
    ASSERT_TRUE(account != NULL) << "Failed to login to test account " << "127850894";
}