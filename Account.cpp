/*
Filename: Account.cpp
Programmers: Matthew Greelaw, Dalton Gray, Katie Loveland
Class: CS-300
Date: 22NOV17
Purpose:

 */

#include "mainHeader.h"


////////////////////////
//      Account       //
////////////////////////


Account :: Account ( void ) : name ( NULL ), ID ( NULL ), email  ( NULL ), theAddress (NULL), securityLevel ( init ) {}

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
	string* fullAddress = theAddress->getFullAddress();
	cout<<*name<<endl;
	cout<<*email<<endl;
	cout<<*ID<<endl;
    cout<<*fullAddress<<endl;
	cout<<securityLevel<<endl;
	delete fullAddress;
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

string* Account::getID(){
    return ID;
}


////////////
//Manager //
////////////

Manager :: Manager ( void ) : 
Account ( ), password ( NULL ) {}

Manager :: Manager ( string * newName, string * newEmail, string * newID, address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword) : Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( NULL ) {
	if(newPassword) {
		password = new string ( *newPassword );
	}
}

Manager :: Manager ( const Manager & copied) : 
Account ( copied ) {//@todo
	//Deep Copy
	if(copied.password) {
		password = new string ( *copied.password );
	}
	
}

Manager :: ~Manager ( void ){
	//Delete dynamic memory
	if ( password ) {
		delete password;
		password = NULL;
	}
}

/**
 * Setter for Manager's data member
 * @param  newPassword The new password to be set
 * @return             True iff the password is set
 */
bool Manager :: setPassword (   string * newPassword ) {

	if ( password ) {
		if(*password == * newPassword) {
			return false;
		}
		delete password;
		password = NULL;
	}

	password = new string ( *newPassword );

	return true;
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

Provider :: Provider ( string * newName, string * newEmail, string * newID, address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword, int newNumMembersSeen,   list < int > * newMembersSeen,   list < providerRecord >  * newServiceRecord) :
    Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( newPassword ), numMembersSeen ( newNumMembersSeen ), membersSeen ( NULL ),
    serviceRecord ( NULL )  {
	
	password = new string ( * newPassword );

	membersSeen = new list < int >;
	*membersSeen = *newMembersSeen;

	serviceRecord = new list < providerRecord >;
	*serviceRecord = *newServiceRecord;
}

Provider :: Provider ( const Provider & copied) : 
Account ( copied ), password ( NULL ), numMembersSeen ( copied.numMembersSeen ), membersSeen ( NULL ), serviceRecord ( NULL ){
	//Deep Copy
	
	password = new string ( * copied.password );
	
	membersSeen = new list < int >;
	*membersSeen = *copied.membersSeen;

	serviceRecord = new list < providerRecord >;
	*serviceRecord = *copied.serviceRecord;
}

Provider :: ~Provider ( void ) {//@todo
	//Delete dynamic memory
	
	if ( password ) {
		delete password;
		password = NULL;
	}

	if ( membersSeen ) {
		delete membersSeen;
		membersSeen = NULL;
	}

	if ( serviceRecord ) {
		delete serviceRecord;
		serviceRecord = NULL;
	}
}

/**
 * Sets a new password
 * @param  newPassword The new password
 * @return             True if set, false otherwise
 */
bool Provider :: setPassword ( string * newPassword ) {
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
bool Provider :: checkPassword ( string * passwordToCheck ) {//@todo
	if ( * password == * passwordToCheck)
		return true;

	return false;
}

/**
 * Displays all members
 * @return  True if the function displayed all members, false otherwise
 */
bool Provider :: displayAllMembers ( void ) {//@todo
	
	for ( list < int > :: const_iterator i = membersSeen->begin(), end = membersSeen -> end(); i != end; ++i )
		cout << *i << endl;

	return false;
}

/**
 * Adds a service record to the list of service records
 * @param  newServiceRecord The new service record
 * @return                  True if the service record was added, false otherwise
 * @note	Client should not delete newServiceRecord, let Provider do that in the
 *       	destructor.
 */
bool Provider :: addServiceRecord ( providerRecord * newServiceRecord ) {//@todo
	//Push newServiceRecord onto list head
	
	serviceRecord -> push_back ( * newServiceRecord );

	//if ( serviceRecord - > end () - 1 == * newServiceRecord ) @toDo '==' operator for Record class ??? this is a struct?
		//return true; 

	return false;
}

/**
 * Adds a member to the list of members seen
 * @param  memberID The added member's ID
 * @return          True if the member was added
 */
bool Provider :: addMemberSeen ( int memberID ) {//@todo
	//Push memberID onto membersSeen
	
	membersSeen -> push_back ( memberID );

	if ( membersSeen -> back () == memberID )
		return true; 
	
	return false;
}

/**
 * Gets the fee.
 * @return     The fee.
 */
float Provider :: getFee ( void ) {}

/**
 * Gets the number memers seen.
 * @return     The number memers seen.
 */
int Provider :: getNumMembersSeen ( void ) {}

/**
 * Gets the provider record.
 * @return     The provider record.
 */
list < providerRecord > * Provider :: getServiceRecord ( void ) {}

////////////
//Member //
////////////

Member :: Member ( void ) :  
Account ( ), serviceRecord ( NULL ), status ( current ) {}

Member :: Member ( const Member & copied) : 
Account ( copied ), serviceRecord ( NULL ), status ( copied.status) {

       	serviceRecord = new list < memberRecord >;
	*serviceRecord = *copied.serviceRecord;
        status = copied.status;
}


Member :: Member (   string * newName,   string * newEmail, string * newID, address *newAddress, SECURITY_LEVEL newSecurityLevel,
MEMBER_STATUS newStatus,   list < memberRecord > * newServiceRecord ) :
Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), serviceRecord ( NULL ), status ( newStatus) {

        serviceRecord = new list < memberRecord >;
	*serviceRecord = *newServiceRecord;
        status = newStatus;
}

Member :: ~Member ( void ) {
	//Delete dynamic memory
        if(serviceRecord) {
            delete serviceRecord;
            serviceRecord = NULL;
        }
}

/**
 * Setter for status data member
 * @param  newStatus The new status
 * @return           True if set, false otherwise
 */
bool Member :: setMemberStatus ( MEMBER_STATUS newStatus ) {
	status = newStatus;
        if(status == newStatus)
            return true;
        else
	    return false;
}

/**
 * Getter for status data member
 * @return  The status data member
 */
MEMBER_STATUS Member :: getMemberStatus ( void ) {
	return status;
}

/**
 * Appends a service record to the list of service records
 * @param  newServiceRecord The apended service record
 * @return                  True if the service record was appended, false otherwise
 */
bool Member :: appendToServiceRecord ( memberRecord newServiceRecord) {//@todo check for append.
	//Push newServiceRecord onto serviceRecord
	serviceRecord -> push_front(newServiceRecord);
	return true;
}

/**
 * Getter for the serviceRecords data member
 * @return                  The service Records data member 
 */
  list < memberRecord > * Member :: getServiceRecords ( void ) {
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
    streetAdress = new string(*toCopy.streetAdress);
    city = new string(*toCopy.city);
    state = new string(*toCopy.state);
    zipcode = new string(*toCopy.zipcode);
}

address::address(string* newStreetAdress, string* newCity, string* newState, string* newZipcode){
    streetAdress = new string(*newStreetAdress);
    city = new string(*newCity);
    state = new string(*newState);
    zipcode = new string(*newZipcode);
}

address::~address(){
    if(streetAdress){
        delete streetAdress;
        streetAdress = NULL;
    }
    if(city){
        delete city;
        city = NULL;
    }
    if(state){
        delete state;
        state = NULL;
    }
    if(zipcode){
        delete zipcode;
        zipcode = NULL;
    }
}
bool address::setAddress(string* newStreetAdress, string* newCity, string* newState, string* newZipcode){
    streetAdress = new string(*newStreetAdress);
    city = new string(*newCity);
    state = new string(*newState);
    zipcode = new string(*newZipcode);
    return true;
}

void address::setAddress(const char* newStreetAdress, const char*  newCity, const char*  newState, const char* newZipcode){
    streetAdress = new string(newStreetAdress);
    city = new string(newCity);
    state = new string(newState);
    zipcode = new string(newZipcode);
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



