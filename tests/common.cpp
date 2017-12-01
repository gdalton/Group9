#include "common.h"
Member * createDummyMember(string id)
{
    string name = string("John Freewaffle");
    string email = string("IhateEmail@gmail.com");
    string street = string("Apple");
    string city = string("Apple City");
    string state = string("Apple State");
    string country = string("Apple Nation");
    Address fakeAddress = Address(&street, &city, &state, &country);
    memberRecordList fakeRecordList;

    return new Member(&name, &email, &id, &fakeAddress, member, current, &fakeRecordList);
}


Member * createDummyMember2(string id)
{
    string name = string("Johnny Freewaffle");
    string email = string("emailIsOkay@gmail.com");
    string street = string("Orange");
    string city = string("Orange City");
    string state = string("Orange State");
    string country = string("Orange Nation");
    Address fakeAddress = Address(&street, &city, &state, &country);
    memberRecordList fakeRecordList;

    return new Member(&name, &email, &id, &fakeAddress, member, current, &fakeRecordList);
}

Provider * createDummyProvider(string id)
{
    string name = string("John Freewaffle");
    string email = string("IhateEmail@gmail.com");
    string street = string("Apple");
    string city = string("Apple City");
    string state = string("Apple State");
    string country = string("Apple Nation");
    string password = string("I'm a pass");
    Address fakeAddress = Address(&street, &city, &state, &country);
    memberRecordList fakeRecordList;
    providerRecordList provList;

    return new Provider(&name, &email, &id, &fakeAddress, provider, &password, 0, provList);
}
