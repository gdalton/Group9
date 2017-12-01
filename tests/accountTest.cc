
#include "gtest/gtest.h"
#include "common.h"

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
    delete account;
}


TEST(smokeTesting, checkMemberStatus) {
    
    accountManager testAccountManager = accountManager();
    Member * memberCurrent = createDummyMember(string("364788132"));
    Member * memberExpired = createDummyMember(string("464788132"));
    ASSERT_TRUE(memberExpired->setMemberStatus(expired)) << "Failed to set expired member status";

    testAccountManager.addAccount(memberCurrent, member);
    testAccountManager.addAccount(memberExpired, member);
    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(memberCurrent->getID(), member)));
    memberExpired = (static_cast<Member*>(testAccountManager.getAccount(memberExpired->getID(), member)));

    
    ASSERT_TRUE(memberCurrent != NULL) << "Failed to get member current";
    ASSERT_TRUE(memberExpired != NULL) << "Failed to get member expired";

    ASSERT_TRUE(memberCurrent->getMemberStatus() == current) << "Failed to get current status " << memberCurrent->getMemberStatus();
    ASSERT_TRUE(memberExpired->getMemberStatus() == expired) << "Failed to get expired status " << memberExpired->getMemberStatus();

    delete memberCurrent;
    delete memberExpired;
}


TEST(smokeTesting, generateAMemberReport) {
    reportManager testReportManger = reportManager();
    string providerName = string("Provider Provideson");
    string serviceName = string("The Best Service");

    memberRecord * newMemberReport = testReportManger.generateMemberServiceRecord(&providerName, &serviceName);
    ASSERT_TRUE(newMemberReport != NULL) << "Failed to generate member report";

    delete newMemberReport;
}


TEST(smokeTesting, generateAProviderReport) {
    reportManager testReportManger = reportManager();
    string newDateOfService = string("11/30/2017");
    string newMemberName = string("Member Memberson");
    string providerID = string("224938990");
    string serviceID = string("TestServiceID");
    string memberID = string("522225555");
    string comments = string("Didn't like our service? :(");

    providerRecord * newProvideReport = testReportManger.generateProviderServiceRecord(&newDateOfService, &newMemberName, &providerID, &serviceID, &memberID, &comments, 20);
    ASSERT_TRUE(newProvideReport != NULL) << "Failed to generate member report";
    delete newProvideReport;
}

TEST(smokeTesting, addServiceToMemberRecord) { 
    Member * memberCurrent = createDummyMember(string("222288132"));
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

    delete providerServiceRecord;
}

TEST(smokeTesting, saveFileSuccess) { 
    accountManager testAccountManager = accountManager();
    string testID = string("522222222");
    Member * memberCurrent = createDummyMember(testID);
    ASSERT_TRUE(testAccountManager.addAccount(memberCurrent, member)) << "Failed to add account";
    ifstream account;
    account.open("accounts/522222222.txt");
    ASSERT_TRUE(account) << "Failed to write account file";

    accountManager newAccountManager = accountManager();

    ASSERT_TRUE(newAccountManager.getAccount(&testID , member) != NULL) << "Failed to read member after save";

    delete memberCurrent;
}
