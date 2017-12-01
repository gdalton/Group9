#include "gtest/gtest.h"
#include "common.h"


//Same thing as a previous smoke tests?

//START
TEST(unitTests, loadUsersFromDatabase) { 
    accountManager testAccountManager = accountManager();
    string * userID = new string("224938990");

    ACCOUNT_TYPE type = ( ACCOUNT_TYPE ) ( userID->at ( 0 ) - '0' );
    Account * account = testAccountManager.getAccount(userID, type);

    ASSERT_TRUE(type == provider) << "Failed to get proper user type" << endl;
    ASSERT_TRUE(account != NULL) << "Failed to login to test account " << *userID;
    delete userID;
    delete account;
}

TEST(unitTests, checkMemberStatus) {
    
    accountManager testAccountManager = accountManager();
    Member * memberCurrent = createDummyMember(string("364744432"));
    Member * memberExpired = createDummyMember(string("464744432"));
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

TEST(unitTests, addServiceToMemberRecord) { 
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
//END

TEST(unitTests, addService) { 
    providerDirectory testDirectory = providerDirectory();
    string testServiceName = string("This is a test service");
    Service toAdd;
    /*
    struct Service { 
        string serviceID;
        string name;
        float fee;
    };
    */
    toAdd.fee = 0;
    toAdd.name = testServiceName;
    toAdd.serviceID = "2323232";

    testDirectory.addService(toAdd);
    list<Service> directory = testDirectory.getDirectory();
    bool found = false;
    for ( list<Service>::iterator j = directory.begin(); j != directory.end(); ++j ) {
        if (j->name == testServiceName)
        {
            found = true;
        }
    }
    ASSERT_TRUE(found) << "Failed to add test service";
}




TEST(unitTests, addMember) {
    
    accountManager testAccountManager = accountManager();
    Member * memberCurrent = createDummyMember(string("364558132"));
    testAccountManager.addAccount(memberCurrent, member);

    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(memberCurrent->getID(), member)));
    ASSERT_TRUE(memberCurrent != NULL) << "Failed to add member";

    delete memberCurrent;
}

TEST(unitTests, addProvider) {
    
    accountManager testAccountManager = accountManager();
    
    Provider * providerCurrent = createDummyProvider(string("264788132"));
    testAccountManager.addAccount(providerCurrent, provider);
    
    providerCurrent = (static_cast<Provider*>(testAccountManager.getAccount(providerCurrent->getID(), provider)));
    ASSERT_TRUE(providerCurrent != NULL) << "Failed to add provider";
}


TEST(unitTests, removeMember) {
    
    accountManager testAccountManager = accountManager();
    string * testID =  new string("564788132");
    Member * memberCurrent = createDummyMember(*testID);
    testAccountManager.addAccount(memberCurrent, member);
    
    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(memberCurrent->getID(), member)));
    ASSERT_TRUE(memberCurrent != NULL) << "Failed to add member";

    testAccountManager.removeAccount(testID, member);
    ASSERT_TRUE(testAccountManager.getAccount(testID, member) == NULL) << "Failed to remove member";

    delete testID;
}

TEST(unitTests, removeProvider) {
    
    accountManager testAccountManager = accountManager();
    string * testID =  new string("264788132");
    Provider * providerCurrent = createDummyProvider(*testID);
    testAccountManager.addAccount(providerCurrent, provider);

    providerCurrent = (static_cast<Provider*>(testAccountManager.getAccount(providerCurrent->getID(), provider)));
    ASSERT_TRUE(providerCurrent != NULL) << "Failed to add provider";

    testAccountManager.removeAccount(testID, provider);
    ASSERT_TRUE(testAccountManager.getAccount(testID, provider) == NULL) << "Failed to remove provider";

    delete testID;
}

TEST(unitTests, editMember) {
    
    accountManager testAccountManager = accountManager();
    string testID = string("564788132");
    Member * memberCurrent = createDummyMember(testID);
    Member * newMemberInfo = createDummyMember2(testID);

    infoStruct * newInfo = newMemberInfo->getInfo();
    testAccountManager.addAccount(memberCurrent, member);

    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(&testID, member)));
    ASSERT_TRUE(memberCurrent != NULL) << "Failed to add member";
    ASSERT_TRUE(testAccountManager.editAccount(&testID, newMemberInfo, member)) << "Failed to edit member";

    memberCurrent = (static_cast<Member*>(testAccountManager.getAccount(&testID, member)));

    ASSERT_TRUE(memberCurrent != NULL) << "Failed to reget member";
    infoStruct * setInfo = memberCurrent->getInfo();

    ASSERT_TRUE(setInfo->ID == newInfo->ID) << "Failed set ID?";
    ASSERT_TRUE(setInfo->name == newInfo->name) << "Failed set name?";
    ASSERT_TRUE(setInfo->email == newInfo->email) << "Failed set email?";
    //securityLevel is not set
    //ASSERT_TRUE(setInfo->securityLevel == newInfo->securityLevel) << "Failed set securityLevel?" << setInfo->securityLevel << " != " << newInfo->securityLevel;
    ASSERT_TRUE(*setInfo->theAddress.getFullAddress() == *newInfo->theAddress.getFullAddress()) << "Failed set address?";
}

TEST(unitTests, displayService) {
    providerDirectory testProviderDirectory;
    ASSERT_TRUE(testProviderDirectory.displayService("759433")) << "Unable to display service that should exist.";
}