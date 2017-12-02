#include "gtest/gtest.h"
#include "common.h"

TEST(unitTests, removeService) {
    providerDirectory testDirectory = providerDirectory();
    string testServiceID = string("111222");
    string testName = string("TEST SERVICE");
    Service toAdd;

    toAdd.fee = 0;
    toAdd.name = testName;
    toAdd.serviceID = testServiceID;

    testDirectory.addService(toAdd);
    list<Service> directory = testDirectory.getDirectory();

    bool found = false;
    for(list<Service>::iterator i = directory.begin(); i != directory.end(); ++i) {
        if(i -> name == testName)
            found = true;
    }
    ASSERT_TRUE(found) << "Failed to add test service";

    testDirectory.removeService(testServiceID);

    directory = testDirectory.getDirectory();

    for(list<Service>::iterator i = directory.begin(); i != directory.end(); ++i) {
        if(i -> name == testName)
            found = false;
    }
    ASSERT_TRUE(found) << "Failed to remove test service";
}    

TEST(unitTests, updateFee) {
    providerDirectory testDirectory = providerDirectory();
    string testServiceID = string("111222");
    string testName = string("TEST SERVICE");
    Service toAdd;

    toAdd.fee = 0;
    toAdd.name = testName;
    toAdd.serviceID = testServiceID;

    testDirectory.addService(toAdd);
    list<Service> directory = testDirectory.getDirectory();

    bool found = false;
    for(list<Service>::iterator i = directory.begin(); i != directory.end(); ++i) {
        if(i -> name == testName)
            found = true;
    }
    ASSERT_TRUE(found) << "Failed to add test service";

    testDirectory.updateFee(testServiceID, 50.5);

    directory = testDirectory.getDirectory();
    found = false;

    for(list<Service>::iterator i = directory.begin(); i != directory.end(); ++i) {
        if(i -> name == testName && i -> fee == 50.5)
            found = true;
    }
    ASSERT_TRUE(found) << "Failed to update test service fee";
}   
