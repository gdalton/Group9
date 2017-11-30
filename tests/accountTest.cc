
#include "gtest/gtest.h"
#include "../mainHeader.h"

//File for Account Testing 
TEST(smokeTesting, allUsersExistInTable) {
    accountManager testAccountManager = accountManager();
    ifstream allAccounts;
    ifstream account;
    allAccounts.open("accounts/allIDs.txt");
    ASSERT_TRUE(allAccounts) << "Failed to open allIDs.txt" << endl;
    while(allAccounts)
    {
        char accountID [30];
        allAccounts.get(accountID, 20,'\n');
        allAccounts.get();

        if(allAccounts.eof())
            break;
        else if(strcmp(accountID, "") == 0)
            continue;
        
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
        
        account.get(accountID, 20, '\n');
        account.close();

        string * stringAccountID = new string(accountID);
        ASSERT_TRUE(testAccountManager.getAccount(stringAccountID, type) != NULL) << "Account failed to load " << accountID;
        delete stringAccountID;
    }
    allAccounts.close();
}

TEST(smokeTesting, canLogin) {
    
    accountManager testAccountManager = accountManager();
    string * userID = new string("224938990");

    ACCOUNT_TYPE type = ( ACCOUNT_TYPE ) ( userID->at ( 0 ) - '0' );
    Account * account = testAccountManager.getAccount(userID, type);

    ASSERT_TRUE(type == provider) << "Failed to get proper user type" << endl;
    ASSERT_TRUE(account != NULL) << "Failed to login to test account " << *userID;
    delete userID;
}

TEST(smokeTesting, checkMemberStatus) {
    
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



TEST(smokeTesting, runAReport) { //@todo
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(smokeTesting, addServiceToMemberRecord) { 
    Member * memberCurrent = new Member(new string("John Freewaffle"), new string("johnnyfreewaffles@gmail.com"), new string("564788132"), new Address(new string("Apple"), new string("Apple City"), new string("Apple State"), new string("APPLES")), member, current, new memberRecordList());
    memberRecord record;
    string providerToLookFor = string("New Service Record Test 231323231");
    record.providerName = providerToLookFor;
    ASSERT_TRUE(memberCurrent->appendToServiceRecord(record)) << "Failed to add service record";
    bool found = false;
    list < memberRecord >* providerServiceRecord = memberCurrent->getServiceRecords();
    for ( list < memberRecord > :: iterator j = providerServiceRecord -> begin (); j != providerServiceRecord -> end (); ++j ) {
        if (j->providerName == providerToLookFor)
        {
            found = true;
        }
    }
    ASSERT_TRUE(found) << "Failed to add Service Record to member";

}

TEST(smokeTesting, saveFileSuccess) { 
    accountManager testAccountManager = accountManager();
    Member * memberCurrent = new Member(new string("John Freewaffle"), new string("johnnyfreewaffles@gmail.com"), new string("522222222"), new Address(new string("Apple"), new string("Apple City"), new string("Apple State"), new string("APPLES")), member, current, new memberRecordList());
    ASSERT_TRUE(testAccountManager.addAccount(memberCurrent, member)) << "Failed to add account";
    ifstream account;
    account.open("accounts/522222222.txt");
    ASSERT_TRUE(account) << "Failed to write account file";
}
