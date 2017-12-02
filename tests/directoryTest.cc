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
    testDirectory.removeService(testServiceID);

    list<Service> directory = testDirectory.getDirectory();
    bool found = true; 

    for(list<Service>::iterator i = directory.begin(); i != directory.end(); ++i) {
        if(i -> name == testName)
            found = false;
    }
    ASSERT_TRUE(found) << "Failed to remove test service";
}    

