/*
Filename: Account.cpp
Programmers: Matthew Greelaw, (Add your name here)
Class: CS-300
Date: 22NOV17
Purpose:

 */

#include "mainHeader.h"


////////////////////////
//      Account       //
////////////////////////


Account :: Account ( void ) : name ( NULL ), ID ( NULL ), email  ( NULL ), securityLevel ( init ) {}

Account :: Account (  string * newName,   string * newEmail, string * newID, address* newAddress, SECURITY_LEVEL newSecurityLevel) :
name ( NULL ), email ( NULL ), ID ( newID ), securityLevel ( newSecurityLevel ) {
	name = new string ( * newName );
	email = new string ( * newEmail );
	ID = new string (*newID);
    theAddress = new address(*newAddress);
}


Account :: Account ( const Account & copied) : 
name ( NULL ), email ( NULL ), ID ( NULL), theAddress (NULL), securityLevel ( copied.securityLevel ) {
	name = new   string ( * copied.name );
	email = new   string ( * copied.email );
	ID = new string (*copied.ID);
    theAddress = new address(*copied.theAddress);
}

Account :: Account ( infoStruct* newInfo){
    name = new string ( *newInfo->name );
    email = new string ( * newInfo->email );
    ID = new string (*newInfo->ID);
    theAddress = new address(*newInfo->theAddress);
}

Account :: ~Account ( void ) {

	//Delete dynamic memory
	if ( name ) {
		delete name;
		name = NULL;
	}

	if ( email ) {
		delete email;
		email = NULL;
	}

	if ( ID ) {
		delete ID;
		ID = NULL;
	}
    
    if(theAddress){
        delete theAddress;
        theAddress = NULL;
    }
}

void Account::display() {
	cout<<*name<<endl;
	cout<<*email<<endl;
	cout<<*ID<<endl;
    cout<<*theAddress->getFullAddress()<<endl; 
	cout<<securityLevel<<endl;
}

infoStruct* Account::getInfo(){
	infoStruct* toReturn = new infoStruct;

	toReturn->name = name;
	toReturn->email = email;
	toReturn->theAddress = theAddress;
	toReturn->ID = ID;
	return toReturn;
}

SECURITY_LEVEL Account::getSecurityLevel(){
	return securityLevel;
}


////////////
//Manager //
////////////

Manager :: Manager ( void ) : 
Account ( ), password ( NULL ) {}

Manager :: Manager ( string * newName, string * newEmail, string * newID, address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword) : Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( NULL ) {
	password = new   string ( *newPassword );
}

Manager :: Manager ( const Manager & copied) : 
Account ( copied ) {//@todo
	//Deep Copy

	//password
}

Manager :: ~Manager ( void ){//@todo
	//Delete dynamic memory

	//password
}

/**
 * Setter for Manager's data member
 * @param  newPassword The new password to be set
 * @return             True iff the password is set
 */
bool Manager :: setPassword (   string * newPassword ) {//@todo
	
	//Delete old password
	//set NULL
	//Reinitialize and set new password

	return false;
}

/**
 * Checks to see if the password provided by the user matches the existing password
 * @param  passwordToCheck Provided by user
 * @return                 True if the passwords match, false otherwise
 */
bool Manager :: checkPassword (   string * passwordToCheck ) {
	if ( * password == * passwordToCheck )
		return true;

	return false;
}

/////////////
//Provider //
/////////////

Provider :: Provider ( void ) : 
Account ( ), password ( NULL ), numMembersSeen ( 0 ), membersSeen ( NULL ), serviceRecord ( NULL ) {}

Provider :: Provider (   string * newName,   string * newEmail, string * newID, address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword, int newNumMembersSeen,   list < int > * newMembersSeen,   list < Record >  * newServiceRecord) :
    Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( newPassword ), numMembersSeen ( newNumMembersSeen ), membersSeen ( NULL ),
serviceRecord ( NULL )  {
	//Initialize membersSeen if it remains a pointer
	
	//@todo Read-up on list and make sure this is the correct syntax
	//Also, do we want the provider to own this memory or deal with it in the program?
	membersSeen = new   list < int >;
	*membersSeen = *newMembersSeen;

	serviceRecord = new   list < Record >; //@todo
	*serviceRecord = *newServiceRecord;
}

Provider :: Provider ( const Provider & copied) {//@todo
	//Deep Copy
	
	//members seen
	
	//serviceRecord
}

Provider :: ~Provider ( void ) {//@todo
	//Delete dynamic memory
	
	//members seen
	
	//serviceRecord
}

/**
 * Sets a new password
 * @param  newPassword The new password
 * @return             True if set, false otherwise
 */
bool Provider :: setPassword (   string * newPassword ) {
	* password = * newPassword;

	if ( * password == * newPassword )
		return true;

	return false;
}

/**
 * Verifies if a string is the password
 * @param  passwordToCheck The string to verify
 * @return                 True if they match, false otherwise
 */
bool Provider :: checkPassword (   string * passwordToCheck ) {//@todo
	if ( * password == * passwordToCheck)
		return true;

	return false;
}

/**
 * Displays all members
 * @return  True if the function displayed all members, false otherwise
 */
bool Provider :: displayAllMembers ( void ) {//@todo
	//Loop over each member
		//display member to console
	
	return false;
}

/**
 * Adds a service record to the list of service records
 * @param  newServiceRecord The new service record
 * @return                  True if the service record was added, false otherwise
 */
bool Provider :: addServiceRecord ( Record newServiceRecord ) {//@todo
	//Push newServiceRecord onto list head
	
	return false;
}

/**
 * Adds a member to the list of members seen
 * @param  memberID The added member's ID
 * @return          True if the member was added
 */
bool Provider :: addMemberSeen ( int memberID ) {//@todo
	//Push memberID onto membersSeen
	
	return false;
}

////////////
//Memeber //
////////////

Member :: Member ( void ) :  
Account ( ), serviceRecord ( NULL ), status ( current ) {}

Member :: Member ( const Member & copied) : 
Account ( copied ), serviceRecord ( NULL ), status ( copied.status) {
	serviceRecord = new   list < Record > ( * copied.serviceRecord );
}


Member :: Member (   string * newName,   string * newEmail, string * newID, address *newAddress, SECURITY_LEVEL newSecurityLevel,
MEMBER_STATUS newStatus,   list < Record > * newServiceRecord ) :
Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), serviceRecord ( NULL ), status ( newStatus) {

	serviceRecord = new   list < Record > ( * newServiceRecord );
}

Member :: ~Member ( void ) {//@todo
	//Delete dynamic memory
}

/**
 * Setter for status data member
 * @param  newStatus The new status
 * @return           True if set, false otherwise
 */
bool Member :: setMemberStatus ( MEMBER_STATUS newStatus ) {//@todo
	
	return false;
}

/**
 * Getter for status data member
 * @return  The status data member
 */
MEMBER_STATUS Member :: getMemberStatus ( void ) {//@todo
	return status;
}

/**
 * Appends a service record to the list of service records
 * @param  newServiceRecord The apended service record
 * @return                  True if the service record was appended, false otherwise
 */
bool Member :: appendToServiceRecord ( Record newServiceRecord) {//@todo
	//Push newServiceRecord onto serviceRecord
	serviceRecord -> push_front(newServiceRecord);
	return true;
}

/**
 * Getter for the serviceRecords data member
 * @return                  The service Records data member 
 */
  list < Record > * Member :: getServiceRecords ( void ) {
	return serviceRecord; //@todo syntax?
}




////////////
// Address //
////////////

address::address(){
    streetAdress = NULL;
    city = NULL;
    state = NULL;
    zipcode = NULL;
}
address::address(const address & toCopy){
    this->streetAdress = new string(*toCopy.streetAdress);
    this->city = new string(*toCopy.city);
    this->state = new string(*toCopy.state);
    this->zipcode = new string(*toCopy.zipcode);
}

address::address(string* streetAdress, string* city, string* state, string* zipcode){
    this->streetAdress = new string(*streetAdress);
    this->city = new string(*city);
    this->state = new string(*state);
    this->zipcode = new string(*zipcode);
}

address::~address(){
    delete streetAdress;
    delete city;
    delete state;
    delete zipcode;
}
bool address::setAddress(string* streetAdress, string* city, string* state, string* zipcode){
    this->streetAdress = new string(*streetAdress);
    this->city = new string(*city);
    this->state = new string(*state);
    this->zipcode = new string(*zipcode);
    return true;
}

void address::setAddress(const char* streetAdress, const char*  city, const char*  state, const char* zipcode){
    this->streetAdress = new string(streetAdress);
    this->city = new string(city);
    this->state = new string(state);
    this->zipcode = new string(zipcode);
}

string* address::getFullAddress(){
    return new string(*streetAdress+", "+*city+", "+*state+" "+*zipcode);
}
string* address::getStreetAddress(){
    return new string(*streetAdress);
}
string* address::getCity(){
    return new string(*city);
}
string* address::getState(){
    return new string(*state);
    
}
string* address::getZipcode(){
    return new string(*zipcode);
}



