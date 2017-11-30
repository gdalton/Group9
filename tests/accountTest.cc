
#include "gtest/gtest.h"
#include "../mainHeader.h"

//File for Account Testing 
TEST(accountTesting, allUsersExistInTable) {
    accountManager testAccountManager = accountManager();
    ifstream allAccounts;
    ifstream account;
    allAccounts.open("accounts/allIDs.txt");
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

        char temp [60] = "accounts/";
        strcat(temp,accountID);
        account.open(temp);//Dynamically opens file
        ASSERT_TRUE(account) << "Failed to open " << temp;
        //Stop if account not found
        if(!account) continue;
        
        account.getline(accountID, 20, '\n');
        account.close();

        string * stringAccountID = new string(accountID);
        ASSERT_TRUE(testAccountManager.getAccount(stringAccountID, type) != NULL) << "Account failed to load " << accountID;
        delete stringAccountID;
    }
    allAccounts.close();
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

TEST(accountTesting, checkMemberStatus) {
    
    accountManager testAccountManager = accountManager();
    Member * memberCurrent = new Member(new string("John Freewaffle"), new string("johnnyfreewaffles@gmail.com"), new string("564788132"), new Address(new string("Apple"), new string("Apple City"), new string("Apple State"), new string("APPLES")), member, current, new memberRecordList());
    Member * memberExpired = new Member(new string("Tim Freewaffle"), new string("timfreewaffles@gmail.com"), new string("564788131"), new Address(new string("Apple"), new string("Apple City"), new string("Apple State"), new string("APPLES")), member, expired, new memberRecordList());
    testAccountManager.addAccount(memberCurrent, member);
    testAccountManager.addAccount(memberExpired, member);
    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(memberCurrent->getID(), member)));
    memberExpired = (static_cast<Member*>(testAccountManager.getAccount(memberExpired->getID(), member)));
    ASSERT_TRUE(memberCurrent != NULL) << "Failed to get member current";
    ASSERT_TRUE(memberExpired != NULL) << "Failed to get member expired";

    ASSERT_TRUE(memberCurrent->getMemberStatus() == current) << "Failed to get current status";
    ASSERT_TRUE(memberExpired->getMemberStatus() == expired) << "Failed to get expired status";
}

TEST(accountTesting, displayServicesList) { // @todo I'm not sure how to test this
    UserInterface ui;
    
    ASSERT_TRUE(ui.runProviderMenu()) << "Failed to see provider menu?";
    ASSERT_TRUE(ui.runManagerMenu()) << "Failed to see manager menu?";
}