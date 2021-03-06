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

Account :: Account (  string * newName,   string * newEmail, string * newID, Address* newAddress, SECURITY_LEVEL newSecurityLevel) :
name ( NULL ), email ( NULL ), ID ( newID ), securityLevel ( newSecurityLevel ) {
	name = new string ( * newName );
	email = new string ( * newEmail );
	ID = new string (*newID);
    theAddress = new Address(*newAddress);
}


Account :: Account ( const Account & copied) : 
name ( NULL ), email ( NULL ), ID ( NULL), theAddress (NULL), securityLevel ( copied.securityLevel ) {
    name = new string ( * copied.name );
    email = new string ( * copied.email );
    ID = new string ( * copied.ID );
    theAddress = new Address( * copied.theAddress );
}

Account :: Account ( infoStruct * newInfo){
    name = new string ( newInfo->name );
    email = new string ( newInfo->email );
    ID = new string ( newInfo->ID);
    theAddress = new Address( newInfo->theAddress);
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

void Account::display() const {
	string* fullAddress = theAddress->getFullAddress();
	cout<<*name<<endl;
	cout<<*email<<endl;
	cout<<*ID<<endl;
    cout<<*fullAddress<<endl;
	cout<<securityLevel<<endl;
	delete fullAddress;
}

infoStruct* Account::getInfo() const {
	infoStruct* toReturn = new infoStruct;

	toReturn->name = *name;
	toReturn->email = *email;
	toReturn->theAddress = *theAddress;
	toReturn->ID = *ID;
    toReturn->securityLevel = securityLevel;
    
	return toReturn;
}


void Account :: setInfo ( string * _name, string * _email, string * _ID, Address * _theAddress, SECURITY_LEVEL _securityLevel ) {
    
    if( !name )
        name = new string;

    if ( !ID )
        ID = new string;

    if ( !theAddress )
        theAddress = new Address;

    * name = *_name;
    * ID = * _ID;
    * theAddress = * _theAddress;
    * email = *_email;

    //theAddress-> setAddress ( _theAddress -> getStreetAddress(), _theAddress -> getCity(), _theAddress -> getState(), _theAddress -> getZipcode() );   
    securityLevel = _securityLevel;
}

SECURITY_LEVEL Account::getSecurityLevel() const {
	return securityLevel;
}

string* Account::getID() const {
    return ID;
}

string* Account::writeToString(){
    //Create new string and manage returned memory
    string* address =theAddress->writeToString();
    string* toReturn = new string(*ID+"\n"+*name+"\n"+*email+"\n"+*address);
    delete address;
    return toReturn;
}


////////////
//Manager //
////////////

Manager :: Manager ( void ) : 
Account ( ), password ( NULL ) {}

Manager :: Manager ( string * newName, string * newEmail, string * newID, Address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword) : Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( NULL ) {
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
bool Manager :: setPassword ( string * newPassword ) {

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
bool Manager :: checkPassword (   string * passwordToCheck ) const {
	if ( * password == * passwordToCheck )
		return true;

	return false;
}

string* Manager::writeToString(){
    //Create new string and manage returned memory
    string* address =theAddress->writeToString();
    string* toReturn = new string(*ID+"\n"+*name+"\n"+*email+"\n"+*address+"\n"+*password);
    delete address;
    return toReturn;
}

//Function to display the account
void Manager::displayToUI(){
    string* temp = NULL;
    
    cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│              Manager Account Info" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│ Name....: "<<*name<<endl;
    cout << "│ Email...: "<<*email<<endl;
    temp = theAddress->getStreetAddress();
    cout << "│ Address.: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getCity();
    cout << "│ City....: "<<*temp<<endl;
    delete temp;
    temp =theAddress->getState();
    cout << "│ State...: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getZipcode();
    cout << "│ Zip Code: "<<*temp<<endl;
    delete temp;
    cout << "│ password: "<<*password<<endl;
    cout << "│ ID......: " << *ID << endl;
    cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
}

/////////////
//Provider //
/////////////

Provider :: Provider ( void ) :
Account ( ), password ( NULL ), numMembersSeen ( 0 ), membersSeen ( NULL ) {}

Provider :: Provider ( string * newName, string * newEmail, string * newID, Address * newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword, int newNumMembersSeen,  list < providerRecord >  & newServiceRecord) :
    Account ( newName, newEmail, newID, newAddress, newSecurityLevel ), password ( newPassword ), numMembersSeen ( newNumMembersSeen ), membersSeen ( NULL ){
	
	password = new string ( * newPassword );

	membersSeen = new list < int >;
    
	serviceRecord = newServiceRecord;
}

Provider :: Provider ( const Provider & copied) : 
Account ( copied ), password ( NULL ), numMembersSeen ( copied.numMembersSeen ), membersSeen ( NULL ){
	//Deep Copy
	
	password = new string ( * copied.password );
	
	membersSeen = new list < int >;
	*membersSeen = *copied.membersSeen;

	serviceRecord = copied.serviceRecord;
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
bool Provider :: checkPassword ( string * passwordToCheck ) const {//@todo
	if ( * password == * passwordToCheck)
		return true;

	return false;
}

/**
 * Displays all members
 * @return  True if the function displayed all members, false otherwise
 */
bool Provider :: displayAllMembers ( void ) const {//@todo
	
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
bool Provider :: addServiceRecord ( fileSystem & database, providerRecord & newServiceRecord ) {
   
    string * recordContents = NULL;
    stringstream aFloat;
    string serviceFee;

    if ( &newServiceRecord ) {
        serviceRecord.push_front ( newServiceRecord );
        aFloat << newServiceRecord . serviceFee;
        serviceFee = aFloat.str();

        recordContents = new string;
        * recordContents += "^";
        * recordContents += newServiceRecord . currentDateTime + "^";
        * recordContents += newServiceRecord . dateOfService + "^";
        * recordContents += newServiceRecord . providerID + "^";
        * recordContents += newServiceRecord . memberID + "^";
        * recordContents += newServiceRecord . serviceCode + "^";
        * recordContents += serviceFee + "^";
        * recordContents += newServiceRecord . comments + "^";
        * recordContents += newServiceRecord . memberName;
        
        if ( database . appendToFile ( new string ( "accounts/" + * ID + ".txt" ),  recordContents ) )
            return true;
    }
	


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
float Provider :: getFee ( void ) const {
    return 0;
}

/**
 * Gets the number memers seen.
 * @return     The number memers seen.
 */
int Provider :: getNumMembersSeen ( void ) const {
    return numMembersSeen;
}

/**
 * Gets the provider record.
 * @return     The provider record.
 */
list < providerRecord > * Provider :: getServiceRecord ( void ) const {
    
    return new providerRecordList(serviceRecord);
}


string* Provider::writeToString(){

    //Create new string and manage returned memory
    string* address =theAddress->writeToString();
    string serviceRecords = "";
    
    for (providerRecordList::iterator it=serviceRecord.begin(); it != serviceRecord.end(); ++it){
        serviceRecords += ("^")+it->currentDateTime+("^")+it->dateOfService+("^")+it->providerID+("^")+it->memberID+("^")+it->serviceCode+("^")+toString(it->serviceFee)+("^")+it->comments+("^")+it->memberName+("\n");
    }
    
    string* toReturn = new string(*ID+"\n"+*name+"\n"+*email+"\n"+*address+"\n"+*password+"\n"+toString(numMembersSeen)+"\n"+serviceRecords);
    
    //Free memory and return
    delete address;
    return toReturn;
}

//Function to display the account
void Provider::displayToUI(){
    int counter = 1;
    string* temp;
    
    
    cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│              Provider Account Info" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│ Name....: "<<*name<<endl;
    cout << "│ Email...: "<<*email<<endl;
    temp = theAddress->getStreetAddress();
    cout << "│ Address.: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getCity();
    cout << "│ City....: "<<*temp<<endl;
    delete temp;
    temp =theAddress->getState();
    cout << "│ State...: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getZipcode();
    cout << "│ Zip Code: "<<*temp<<endl;
    delete temp;
    cout << "│ password: "<<*password<<endl;
    cout << "│ ID......: " << *ID << endl;
    cout << "│ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl;
    cout << "│                      Records                       " << endl;
    cout << "│ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl;

    //Loop through all records
    for (providerRecordList::iterator it=serviceRecord.begin(); it != serviceRecord.end(); ++it){
        cout << "│ Record #"<<counter<< endl;
        cout << "| ━━━━━━━━━━━"<<endl;
        cout << "│ Date Created....: "<<it->currentDateTime<<endl;
        cout << "│ Date Performed..: "<<it->dateOfService<<endl;
        cout << "│ Provider ID.....: "<<it->providerID<<endl;
        cout << "│ Member ID.......: "<<it->memberID<<endl;
        cout << "│ Member Name.....: "<<it->memberName<<endl;
        cout << "│ Service Code....: "<<it->serviceCode<<endl;
        cout << "│ Service Fee.....: "<<it->serviceFee<<endl;
        cout << "│ Comments........: "<<it->comments<<endl;
        cout << "| "<<endl;
        
        counter++;
    }
    
    cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
}

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


Member :: Member (   string * newName,   string * newEmail, string * newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel,
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
MEMBER_STATUS Member :: getMemberStatus ( void ) const {
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
  list < memberRecord > * Member :: getServiceRecords ( void ) const {
	return serviceRecord; //@todo syntax?
}

string* Member::writeToString(){
    
    //Create new strings
    string serviceRecords = "";
    string strStatus = "Current";
    string* address =theAddress->writeToString();
    string* toReturn = NULL;
    
    //Set to expired if expired
    if(status == expired)
        strStatus = "Expired";
    
    //Loop through and convert
    for (memberRecordList::iterator it=serviceRecord->begin(); it != serviceRecord->end(); ++it){
        serviceRecords += ("^")+it->dateOfService+("^")+it->providerName+("^")+it->serviceName+("\n");
    }
    
    toReturn = new string(*ID+"\n"+*name+"\n"+*email+"\n"+*address+"\n"+strStatus+"\n"+serviceRecords);
    
    //Free memory and return
    delete address;
    return toReturn;
}


//Function to display the account
void Member::displayToUI(){
    int counter = 1;
    
    string* temp;
    
    cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│              Member Account Info" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│ Name....: "<<*name<<endl;
    cout << "│ Email...: "<<*email<<endl;
    temp = theAddress->getStreetAddress();
    cout << "│ Address.: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getCity();
    cout << "│ City....: "<<*temp<<endl;
    delete temp;
    temp =theAddress->getState();
    cout << "│ State...: "<<*temp<<endl;
    delete temp;
    temp = theAddress->getZipcode();
    cout << "│ Zip Code: "<<*temp<<endl;
    delete temp;
    cout << "│ ID......: " << *ID << endl;
    cout << "│ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl;
    cout << "│                      Records                       " << endl;
    cout << "│ ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " << endl;
    
    //Loop through all records
    for (memberRecordList::iterator it=serviceRecord->begin(); it != serviceRecord->end(); ++it){
        cout << "│ Record #"<<counter<< endl;
        cout << "| ━━━━━━━━━━━"<<endl;
        cout << "│ Date of Service: "<<it->dateOfService<<endl;
        cout << "│ Service Name...: "<<it->serviceName<<endl;
        cout << "│ Provider Name..: "<<it->providerName<<endl;
        cout << "| "<<endl;
        
        counter++;
    }
    
    cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
}




////////////
// Address //
////////////

Address::Address(){
    streetAdress = NULL;
    city = NULL;
    state = NULL;
    zipcode = NULL;
}

Address::Address(const Address & toCopy){
    streetAdress = new string(*toCopy.streetAdress);
    city = new string(*toCopy.city);
    state = new string(*toCopy.state);
    zipcode = new string(*toCopy.zipcode);
}

Address::Address(string* newStreetAdress, string* newCity, string* newState, string* newZipcode){
    streetAdress = new string(*newStreetAdress);
    city = new string(*newCity);
    state = new string(*newState);
    zipcode = new string(*newZipcode);
}

Address::~Address(){
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
void Address::setAddress( string * newStreetAdress, string * newCity, string * newState, string * newZipcode){

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
    
    streetAdress = new string( * newStreetAdress );
    city = new string ( * newCity ) ;
    state = new string ( * newState );
    zipcode = new string ( * newZipcode );
}

void Address::setAddress(const char* newStreetAdress, const char*  newCity, const char*  newState, const char* newZipcode){
    streetAdress = new string(newStreetAdress);
    city = new string(newCity);
    state = new string(newState);
    zipcode = new string(newZipcode);
}

string* Address::getFullAddress() const {
    return new string(*streetAdress+", "+*city+", "+*state+" "+*zipcode);
}
string* Address::getStreetAddress() const {
    return new string(*streetAdress);
}
string* Address::getCity() const {
    return new string(*city);
}
string* Address::getState() const {
    return new string(*state);
    
}
string* Address::getZipcode() const {
    return new string(*zipcode);
}
string* Address::writeToString() {
    return new string(*streetAdress+"^"+*city+"^"+*state+"^"+*zipcode);
}
