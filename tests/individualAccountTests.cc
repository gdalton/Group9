#include "gtest/gtest.h"
#include "../mainHeader.h"

TEST(addressTesting, addressInitialization) {
    string street = "Street";
    string city = "Portland";
    string state = "OR";
    string zipcode = "97201";
    
    Address theAddress(&street,&city,&state,&zipcode);
    
    ASSERT_TRUE(*theAddress.getStreetAddress() == "Street");
    ASSERT_TRUE(*theAddress.getCity() == "Portland");
    ASSERT_TRUE(*theAddress.getState() == "OR");
    ASSERT_TRUE(*theAddress.getZipcode() == "97201");
    
}

TEST(addressTesting, writingToStrings) {
    string street = "Street";
    string city = "Portland";
    string state = "OR";
    string zipcode = "97201";
    
    Address theAddress(&street,&city,&state,&zipcode);
    
    ASSERT_TRUE(*theAddress.getFullAddress() == "Street, Portland, OR 97201");
    ASSERT_TRUE(*theAddress.writeToString()  == "Street^Portland^OR^97201"); 
    
}


TEST(accountTesting, baseClassTesting) {
    string street = "Street";
    string city = "Portland";
    string state = "OR";
    string zipcode = "97201";
    
    Address theAddress(&street,&city,&state,&zipcode);
 
    string name= "Person";
    string email  = "p@pdx.edu";
    string id= "100000001";
    

    Account test(&name, &email, &id, &theAddress, init); 

    ASSERT_TRUE(*test.getID() == "100000001"); 
    ASSERT_TRUE(test.getSecurityLevel() == init); 

   // Account ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel );
    
}

TEST(accountTesting, managerTesting) {
    string street = "Street";
    string city = "Portland";
    string state = "OR";
    string zipcode = "97201";
    
    Address theAddress(&street,&city,&state,&zipcode);
 
    string name= "Person";
    string email  = "p@pdx.edu";
    string id= "100000001";
    string password = "password";
    

    Manager test(&name, &email, &id, &theAddress, manager, &password); 

    ASSERT_TRUE(*test.getID() == "100000001"); 
    ASSERT_TRUE(test.getSecurityLevel() == manager);

    ASSERT_TRUE(test.checkPassword(&password)); 
    
    password = "root";
    ASSERT_FALSE(test.checkPassword(&password)); 

    ASSERT_TRUE(test.setPassword(new string("root"))); 

    ASSERT_TRUE(test.checkPassword(&password)); 

   // Account ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel );
    
}


