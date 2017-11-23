/*
Filename: Account.cpp
Programmers: Matthew Greelaw, (Add your name here)
Class: CS-300
Date: 22NOV17
Purpose:

 */

#include "Account.h"

////////////
//Account //
////////////

Account :: Account ( void ) : 
name ( NULL ), ID ( 0 ), email ( NULL ), securityLevel ( init ) {}

Account :: Account ( std :: string * newName, std :: string * newEmail, int newID, SECURITY_LEVEL newSecurityLevel) :
name ( NULL ), email ( NULL ), ID ( newID ), securityLevel ( newSecurityLevel ) {
	name = new std :: string ( * newName );
	email = new std :: string ( * newEmail );
}

Account :: Account ( const Account & copied) : 
name ( NULL ), email ( NULL ), ID ( copied.ID ), securityLevel ( copied.securityLevel ) {//@todo
	name = new std :: string ( * copied.name );
	email = new std :: string ( * copied.email );
}

Account :: ~Account ( void ) {//@todo
	//Delete dynamic memory
	if ( name ) {
		delete name;
		name = NULL;
	}

	if ( email ) {
		delete email;
		email = NULL;
	}
}

////////////
//Manager //
////////////

Manager :: Manager ( void ) : 
Account ( ), password ( NULL ) {}

Manager :: Manager ( std :: string * newName, std :: string * newEmail, int newID, SECURITY_LEVEL newSecurityLevel, std :: string * newPassword) :
Account ( newName, newEmail, newID, newSecurityLevel ), password ( NULL ) {
	password = new std :: string ( *newPassword );
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
bool Manager :: setPassword ( std :: string * newPassword ) {//@todo
	
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
bool Manager :: checkPassword ( std :: string * passwordToCheck ) {
	if ( * password == * passwordToCheck )
		return true;

	return false;
}

/////////////
//Provider //
/////////////

Provider :: Provider ( void ) : 
Account ( ), password ( NULL ), numMembersSeen ( 0 ), membersSeen ( NULL ), serviceRecord ( NULL ) {}

Provider :: Provider ( std :: string * newName, std :: string * newEmail, int newID, SECURITY_LEVEL newSecurityLevel,
std :: string * newPassword, int newNumMembersSeen, std :: list < int > * newMembersSeen, std :: list < Record >  * newServiceRecord) :
Account ( newName, newEmail, newID, newSecurityLevel ), password ( newPassword ), numMembersSeen ( newNumMembersSeen ), membersSeen ( NULL ), 
serviceRecord ( NULL )  {
	//Initialize membersSeen if it remains a pointer
	
	//@todo Read-up on list and make sure this is the correct syntax
	//Also, do we want the provider to own this memory or deal with it in the program?
	membersSeen = new std :: list < int >; 
	*membersSeen = *newMembersSeen;

	serviceRecord = new std :: list < Record >; //@todo
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
bool Provider :: setPassword ( std :: string * newPassword ) {
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
bool Provider :: checkPassword ( std :: string * passwordToCheck ) {//@todo
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
	serviceRecord = new std :: list < Record > ( * copied.serviceRecord );
}


Member :: Member ( std :: string * newName, std :: string * newEmail, int newID, SECURITY_LEVEL newSecurityLevel,
MEMBER_STATUS newStatus, std :: list < Record > * newServiceRecord ) : 
Account ( newName, newEmail, newID, newSecurityLevel ), serviceRecord ( NULL ), status ( newStatus) {

	serviceRecord = new std :: list < Record > ( * newServiceRecord );
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
	
	return false;
}

/**
 * Getter for the serviceRecords data member
 * @return                  The service Records data member 
 */
std :: list < Record > * Member :: getServiceRecords ( void ) {
	return serviceRecord; //@todo syntax?
}