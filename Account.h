#ifndef ACCOUNT
#define ACCOUNT

/* filename: Acount.h
 * Programmers: Matthew Greenlaw, Dmitri Murphy, (Add your name here)
 * Class Number: CS-300 
 * Date: 22NOV17 
 * Purpose: 
 * The Account class will have fields for a name, ID number, email address, and
 * security level, as well as methods to set those fields, get those fields, and
 * create an account. The name, address, email, and security level will all
 * initially be set by a ChocAn manager via the create method, and then a unique
 * ID number will be generated by the system and applied to the appropriate
 * field. The set info method will read in information for all of the fields in
 * the class and set those fields from that information. The Account class will
 * have a get info method that will retrieve the information from the name, ID
 * number, email, and address fields, and return them via a structure to be used
 * by other methods in the system. A security check method will be implemented,
 * this will be used to retrieve the information stored in the security level
 * field that will determine the level of access a given account has to the rest
 * of the systems functionality. 
 */

class Address; //forward declaration
               


/**Service Record Structs**/

struct memberRecord {
    string dateOfService;
    string providerName;
    string serviceName;
};


struct providerRecord {
    string currentDateTime;
    string dateOfService;
    string memberName;
    string memberID;
    string serviceCode;
    float serviceFee;
};

struct provSysRecord { //@todo deconflict with providerRecord
    string currentDateTime;
    string DateOfService;
    string providerID;
    string memberID;
    string serviceCode;
    string comments; 
};

/* *** Enumerations
 * - Use to denote different statuses
 *   and security levels.
 */
enum MEMBER_STATUS {
	current, 
	expired
}; typedef enum MEMBER_STATUS MEMBER_STATUS;

enum SECURITY_LEVEL {
	init,
	manager,
	provider,
	member
}; typedef enum SECURITY_LEVEL SECURITY_LEVEL,ACCOUNT_TYPE;



class Address {
public:
	Address();
	Address(string* streetAdress, string* city, string* state, string* zipcode);
    Address(const Address & toCopy);
	~Address();
	bool setAddress(string* streetAdress, string* city, string* state, string* zipcode);
    void setAddress(const char* streetAdress, const char*  city, const char*  state, const char* zipcode);
	string* getFullAddress() const;
	string* getStreetAddress() const;
	string* getCity() const;
	string* getState() const;
	string* getZipcode() const;

private:
	string * streetAdress;
	string * city;
	string * state;
	string * zipcode;
};

//Forward declaration only allows address to be apointer, so I moved this down.
//The only other option is to seperate headers.
struct infoStruct {
    string ID;
    string name;
    Address theAddress;
    string email;
    int securityLevel;
};

// ******* Account Class *******

class Account {
public:
	Account ( void );
	Account ( const Account & );
    Account ( infoStruct * newInfo);
	Account ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel );
	~Account ( void );
	void display() const;
	infoStruct* getInfo() const;
	SECURITY_LEVEL getSecurityLevel() const;
    string* getID() const;


protected:
	string * name;
	string * ID;
	string * email;
    Address * theAddress;
	SECURITY_LEVEL securityLevel;
    
};

/* From assignment:
- Member street address (25 characters).
- Member city (14 characters).
- Member state (2 letters).
- Member zip code (5 digits).
 */

// ******* Manager Class *******

class Manager : public Account {
public:
	Manager ( void );
	Manager ( const Manager & );
	Manager ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel, string * newPassword );
	~Manager ( void );

	bool setPassword ( string * newPassword );
	bool checkPassword ( string * passwordToCheck ) const ;

protected:
	string * password;
};



// ******* Provider Class *******

class Provider : public Account {
public:
	Provider ( void );
	Provider ( const Provider & );
	Provider ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel,
  	string * newPassword, int newNumMembersSeen,   list < int > * newMembersSeen,   list < providerRecord >  * newServiceRecord);
	~Provider ( void );


	bool setPassword ( string * newPassword );
	bool checkPassword ( string * passwordToCheck ) const ;
	bool displayAllMembers ( void ) const ;
	bool addServiceRecord ( providerRecord* newServiceRecord );
	bool addMemberSeen ( int memberID );

	float getFee () const;
	int getNumMembersSeen () const;
	list < providerRecord > * getServiceRecord () const;


protected:
	string * password;
	int numMembersSeen;
	list < int > * membersSeen; //Wasn't shown as a pointer, but maybe it should be?
	list < providerRecord > * serviceRecord; //Wasn't shown as a pointer, but maybe it should be?
};



// ******* Member Class *******

class Member : public Account {
public:
	Member ( void );
	Member ( const Member & );
	Member ( string * newName, string * newEmail, string *newID, Address *newAddress, SECURITY_LEVEL newSecurityLevel,
	MEMBER_STATUS newStatus,   list < memberRecord > * newServiceRecord );
	~Member ( void );

	bool setMemberStatus ( MEMBER_STATUS newStatus );
	MEMBER_STATUS getMemberStatus ( void ) const;
	bool appendToServiceRecord ( memberRecord newServiceRecord);
	list < memberRecord > * getServiceRecords ( void ) const;

protected:
	list < memberRecord > * serviceRecord; //Should this be a pointer? // Yes, I think so...
	MEMBER_STATUS status;
};

#endif
