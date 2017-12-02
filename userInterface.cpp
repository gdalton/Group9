/* filename: userInterface.cpp
* Programmers: Matthew Greenlaw, Katie Loveland, Dalton Gray
* Class Number: CS-300
* Date: 22NOV17
* Purpose:The User Interface (UI) class manages all input from the user and all
  output to the user, as well as enforcing the proper access levels for each
  user. This entails providing the user with menu’s, accepting their
  selections/data, and passing this data on to other classes to consume. The UI
  class will also query deeper level classes (such as the Account Manager or
  Report Manager) in order to provide information to the user, if the user
  selects a menu option that requires such action. The UI class will utilize the
  Warden class to determine the security clearance of each user and will present
  menu options to them based on that clearance.
*/

#include "mainHeader.h"

//Forward declarations
void createAccount ( accountManager & );
void createManager ( accountManager & );
void createProvider ( accountManager & );
void createMember ( accountManager & );
void deleteAccount ( accountManager & );
void editAccount ( accountManager & );
void viewAccount ( accountManager & );
bool createService(providerDirectory &master);
bool deleteService(providerDirectory &master);
bool updateService(providerDirectory &master);
void generateProviderServiceRecord( fileSystem & database, accountManager & accounts );
void generateProviderRepot();
bool writeManageReport(managersReport * toWrite);
void writeProviderReports(list <providersReport> * toWrite);
void writeMemberReports(list <membersReport> * toWrite);
bool getProviderReport(reportManager &, accountManager &);
void writeProviderRpt(providersReport * toWrite);
bool getMemberReport(reportManager & reports, accountManager & accounts);
void writeMemberRpt(membersReport * toWrite);
bool getEFT(reportManager & reports, accountManager & accounts);
bool writeEFT(eft * toWrite);
  
/** Constructs the object.
 */
UserInterface :: UserInterface () {

}

/** Constructs the object.
 * @param      toCopy  To copy
 */
UserInterface :: UserInterface ( const UserInterface & toCopy ) {
    currentUser = string(toCopy.currentUser);
}

/** Destroys the object.
 */
UserInterface :: ~UserInterface ( void ) {
}

bool UserInterface :: login () {
   string userID = "";
   string password = "";
   Account * account = NULL;
   Manager * manager = NULL;
   Provider * provider = NULL;


   int loginAttempts = 0;
   ACCOUNT_TYPE accountType = ( ACCOUNT_TYPE ) 0;

    cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│                     Login Menu" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
   do {

      cout << "Account ID: ";
      getline ( cin, userID );
      cout << "Password: ";
      getline ( cin, password );

       if(userID != "" && password != "")
           account = accounts.getAccount( &userID, ( ACCOUNT_TYPE ) ( userID.at ( 0 ) - '0' ) );
      
      if ( account ) {
         switch ( userID.at ( 0 ) - '0' ) {
            case 1:
               manager = static_cast < Manager * > ( account );

               if( manager && manager->checkPassword(&password))
                  return runManagerMenu();
               else{
                   //Inform of incorrect password and reset account object
                   cout << "\n[✗] Incorrect Passowrd (Failed login " << ++loginAttempts << "/3) " << endl;
                   account = NULL;
               }
            break;
            case 2:
               provider = static_cast < Provider * > ( account );

               if( provider && provider->checkPassword(&password))
                  return runProviderMenu();
               else{
                   //Inform of incorrect password and reset account object
                   cout << "\n[✗] Incorrect Passowrd (Failed login " << ++loginAttempts << "/3) " << endl;
                   account = NULL;
               }
            break;
            default:
               return 0;
         }
      } else {
         cout << "\n[✗] (Failed login " << ++loginAttempts << "/3) " << endl;

         if ( loginAttempts < 3 ) 
            cout <<   "    There is no account with that ID number. Try again..." << endl;
         else {
            cout << "\n You failed to log in too many times." << endl;
            cout <<   " Contact your administrator to regain access to your account.\n" << endl;
            //@todo warden log
            return 0;
         }
      }
   } while ( loginAttempts < 3);
    
    return false;
}

/** Runs the provider menu system. It presents the provider with a series of
 * commands for the provider to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runProviderMenu () {
    Account * accountToCheck = NULL;
    Member * memberToCheck = NULL;
    int selection = 0;
    string userInput = "";

    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                   Provider Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                  Choose an option:" << endl;
        cout << "│ 0. Exit" << endl;      
        cout << "│ 1. Search for service in Provider Directory" << endl;
        cout << "│ 2. Validate Member Status" << endl;
        cout << "│ 3. Create Service Record" << endl;
        cout << "│ 4. View Provider Directory" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙";
        read_num("                      Option: ", selection);


        switch ( selection) {
            case 0:
                return true;
                break;

            case 1:
                cout << "\nEnter service ID: ";
                getline( cin, userInput );
                if (!directory.displayService ( userInput ) )
                    cout << "\n[✗] Invlaid service ID.\n"<<endl;
                waitForEnter();
                break;

            case 2:
                cout << "\nEnter member ID: ";
                getline( cin, userInput );
                accountToCheck = accounts.getAccount( &userInput, member);
                memberToCheck = static_cast < Member * > ( accountToCheck );

                if ( memberToCheck ){
                    cout << "Member " << userInput << ": ";

                    if ( memberToCheck -> getMemberStatus() == current )
                        cout  << "CURRENT"<<endl;
                    else cout  << "EXPIRED"<<endl;

                } else cout << "\n[✗] Invlaid member ID.\n"<<endl;
                waitForEnter();

                break;

            case 3:
                generateProviderServiceRecord( database, accounts );
                break;

            case 4:
                directory.displayAll();
                waitForEnter();
                break;

            default:
                cout << "\n[✗] \"" << selection << "\" is not an option\n" << endl;
        }
    } while ( selection );


}

void generateProviderServiceRecord( fileSystem & database, accountManager & accounts ) {
    string userInput;
    string * dateOfService = new string;
    string * memberName = new string;
    string * memberID = new string;
    string * providerID = new string;
    string * serviceID = new string;
    string * comments = new string;
    string * serviceFee = new string;
    Provider * accountToEdit = NULL;
    ACCOUNT_TYPE type = provider;
    providerRecord * newServiceRecord = NULL;
    float servicefee = 0;
    bool validFloat = false;


    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│          Provider Service Record Creation" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│ New Provider Service Record Information: " << endl;
        cout << "│" << endl;
        cout << "│ Date of Service.......: "; getline ( cin, *dateOfService);
        cout << "│ Member Name...........: "; getline ( cin, *memberName);
        cout << "│ Member ID.............: "; getline ( cin, *memberID);
        cout << "│ Provider ID...........: "; getline ( cin, *providerID);
        cout << "│ Service ID............: "; getline ( cin, *serviceID);
        cout << "│ Comments (Single Line): "; getline ( cin, *comments);
        cout << "│ Service Fee:..........: $"; 
        if (cin >> servicefee) {
            cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
            cout << "         Is this information correct? (y/n):";
            validFloat = true;
        } else if (cin.fail()) {
            cin.clear();
            cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
            cout << "\n[✗] Invalid service fee. \nExit? (y/n):";
        }
        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    accountToEdit = static_cast < Provider * > ( accounts.getAccount ( providerID, type ) );

    if ( validFloat && accountToEdit ) {
        newServiceRecord = new providerRecord ( new string ( currentDateTime() ), dateOfService, memberName, providerID, serviceID, memberID, comments, servicefee);

        if ( accountToEdit -> addServiceRecord( database, * newServiceRecord ) )
            cout << "\n[✓] Record added." << endl;
        else
            cout << "\n[✗] Failed to add Record." << endl;
    }
}

void generateProviderRepot() {
    /*
    managersReport * reportManager :: managerReport ( const map < string, Provider > & providerTree )
    providersReport {
    string providerName;
    string providerID;
    Address theAddress;
    int consultations;
    float weekFee;
    */
   
}

/** Runs the manager menu system. It presents the manager with a series of
 * commands for the manger to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runManagerMenu ( void ) {
    int userInput = -1;
    int numAccounts = 0;
    int numServices = 0;

    do {

        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                    Manager Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                  Choose an option:" << endl;
        cout << "│ 0. Exit" << endl;  
        cout << "│" << endl;
        cout << "│ Accounts:" << endl;
        cout << "│ 1. Create Account" << endl;
        cout << "│ 2. Delete Account" << endl;
        cout << "│ 3. Edit Account" << endl;
        cout << "│ 4. View Account" << endl;
        cout << "│" << endl;
        cout << "│ Directory:" << endl;
        cout << "│ 5. Create Service" << endl;
        cout << "│ 6. Delete Service" << endl;
        cout << "│ 7. Update Service" << endl;
        cout << "│ 8. View Provider Directory" << endl;
        cout << "│" << endl;
        cout << "│ Reports:" << endl;
        cout << "│ 9.  Generate Manager Report" << endl;
        cout << "│ 10. Generate Provider Report" << endl;
        cout << "│ 11. Generate Member Report" << endl;
        cout << "│ 12. Generate EFT Report" << endl;
        cout << "│ 13. Run Weekly Reports" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙";
        read_num("                        Option: ", userInput);

        
        //Run selected functionality
        switch (userInput) {
            case 0:
                return true;
                break;

            case 1:
                createAccount ( accounts );
                break;

            case 2:
                deleteAccount ( accounts );
                break;

            case 3:
                editAccount ( accounts );
                break;

            case 4:
                viewAccount ( accounts );
                break;

            case 5:
            
                if(createService( directory ))
                    cout << "\n[✓] Service added." << endl;
                else
                    cout << "\n[✗] Failed to add service." << endl;
                waitForEnter();

                break;

            case 6:
               
                if(deleteService( directory ))
                    cout << "\n[✓] Service removed." << endl;
                else
                    cout << "\n[✗] Service was not removed." << endl;
                waitForEnter();

                break;

            case 7:

                if(updateService( directory ))
                    cout << "\n[✓] Service updated." << endl;
                else
                    cout << "\n[✗] Failed to update service." << endl;
                waitForEnter();

                break;

            case 8:
                directory.displayAll();
                waitForEnter();
                break;

            case 9:
                if(writeManageReport(reports.managerReport(accounts.getAllAccounts(provider)))){
                    cout << "\n[✓] Manager Report generated successfully!";
                    cout << "\n    It has been placed in reports/manager/\n" << endl;
                }
                else{
                    cout << "\n[✗] Manager report was not generated. Check data. \n" << endl;
                }

                waitForEnter();
                break;

            case 10:
 
                if(getProviderReport(reports, accounts)){
                    cout << "\n[✓] Provider Report generated successfully!";
                    cout << "\n    It has been placed in reports/provider/\n" << endl;
                }
                else{
                    cout << "\n[✗] ID Provider was not found." << endl;
                }

                waitForEnter();
                break;

            case 11:

                if(getMemberReport(reports, accounts)){
                    cout << "\n[✓] Member Report generated successfully!";
                    cout << "\n    It has been placed in reports/member/\n" << endl;
                }
                else{
                    cout << "\n[✗] ID Member was not found." << endl;
                }

                waitForEnter();
                break;

            case 12:
                if ( getEFT( reports, accounts ) ){
                    cout << "\n[✓] EFT report generated.";
                    cout << "\n    It has been placed in reports/eft/\n" << endl;
                }
                else{
                    cout << "\n[✗] Failed to generate EFT report." << endl;
                }

                waitForEnter(); 
                break;

            case 13:

                writeProviderReports(reports.providerAllReports(accounts.getAllAccounts(provider)));
                writeMemberReports(reports.memberAllReports(accounts.getAllAccounts(member)));
                writeManageReport(reports.managerReport(accounts.getAllAccounts(provider)));
                cout << "\n[✓] All weekly reports have been generated.";
                cout << "\n    They have been placed in the proper folders in reports/\n" << endl;
                waitForEnter();
                break;

            default:
                cout << "\n[✗] \"" << userInput << "\" is not an option.\n" << endl;
                waitForEnter();
        }

    } while (userInput != 0 );
}

void createAccount( accountManager & accounts ) {

    string userInput = "";
    Manager * newManager = NULL;
    Provider * newProvider = NULL;
    Member * newMember = NULL;
    
    do{
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│              Account Generation Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│ 1. Manager" << endl;
        cout << "│ 2. Provider" << endl;
        cout << "│ 3. Member" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "                 Enter account type: ";

        getline ( cin, userInput );

        switch ( ( int ) userInput.at ( 0 ) - '0' ) {
            case 1://Manager
                createManager ( accounts );
                break;
            case 2://Provider
                createProvider ( accounts );
                break;
            case 3://Member
                createMember ( accounts );
                break;
            default:
                cout << "\n[✗] \"" << userInput << "\" is not an option.\n" << endl;
        }
    } while(again("Would you like to create another account? (y/n):"));

}

void createManager ( accountManager & accounts ) {
    Address newAddress;
    string name;
    string email;
    string address;
    string city;
    string state;
    string zip;
    string password;
    string ID;
    string userInput;
    
    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│              Manager Generation Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│ New Manager Information: " << endl;
        cout << "│" << endl;
        cout << "│ Name....: "; getline ( cin, name);
        cout << "│ Email...: "; getline ( cin, email);
        cout << "│ Address.: "; getline ( cin, address);
        cout << "│ City....: "; getline ( cin, city);
        cout << "│ State...: "; getline ( cin, state);
        cout << "│ Zip Code: "; getline ( cin, zip);
        cout << "│ Password: "; getline ( cin, password);
        ID = *accounts.generateAccountID(manager);
        cout << "│ ID......: " << ID << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "         Is this information correct? (y/n):"; 
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount ( new Manager ( &name, &email, &ID, &newAddress, manager, &password ), manager ) )
        cout << "\n[✓] Account added." << endl;
    else
        cout << "\n[✗] Failed to add account." << endl;
}

void createProvider ( accountManager & accounts ) {
    Address newAddress;
    list < providerRecord > * newServiceRecord = new list < providerRecord >;
    list < int > * newMembersSeen = new list < int >;
    string name;
    string email;
    string address;
    string city;
    string state;
    string zip;
    string password;
    string ID;
    string userInput;

    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│              Provider Generation Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│ New Provider Information: " << endl;
        cout << "│" << endl;
        cout << "│ Name....: "; getline ( cin, name);
        cout << "│ Email...: "; getline ( cin, email);
        cout << "│ Address.: "; getline ( cin, address);
        cout << "│ City....: "; getline ( cin, city);
        cout << "│ State...: "; getline ( cin, state);
        cout << "│ Zip Code: "; getline ( cin, zip);
        cout << "│ Password: "; getline ( cin, password);
        ID = *accounts.generateAccountID(provider);
        cout << "│ ID......: " << ID << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "         Is this information correct? (y/n):"; 
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount (new Provider ( &name, &email, &ID, &newAddress, provider, &password, 0, *newServiceRecord ), provider ) )
        cout << "\n[✓] Account added." << endl;
    else 
        cout << "\n[✗] Failed to add account." << endl;

}

void createMember ( accountManager & accounts ) {
    Address newAddress;
    list < memberRecord > * newMemberRecords = new list < memberRecord >;
    string name;
    string email;
    string address;
    string city;
    string state;
    string zip;
    string password;
    string ID;
    string userInput;

    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│              Member Generation Menu" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│ New Member Information: " << endl;
        cout << "│" << endl;
        cout << "│ Name....: "; getline ( cin, name);
        cout << "│ Email...: "; getline ( cin, email);
        cout << "│ Address.: "; getline ( cin, address);
        cout << "│ City....: "; getline ( cin, city);
        cout << "│ State...: "; getline ( cin, state);
        cout << "│ Zip Code: "; getline ( cin, zip);
        ID = *accounts.generateAccountID(member);
        cout << "│ ID......: " << ID << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "         Is this information correct? (y/n):"; 
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount ( new Member ( &name, &email, &ID, &newAddress, member, current, newMemberRecords ), member ) )
        cout << "\n[✓] Account added." << endl;
    else 
        cout << "\n[✗] Failed to add account." << endl;
}

void deleteAccount ( accountManager & accounts ) {//Doesn't check if we are deleting this account
    string userInput = "";
    ACCOUNT_TYPE deletedType = (ACCOUNT_TYPE)0;

    do { 
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│               Account Deletion Menu" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "              Enter account ID to delete: ";

        getline ( cin, userInput );

        switch ( ( int ) userInput.at ( 0 ) - '0' ) {
            case 1://Manager
                deletedType = manager;
                break;
            case 2://Provider
                deletedType = provider;
                break;
            case 3://Member
                deletedType = member;
                break;
            default:
                deletedType = member;
        }
        
        if ( accounts.removeAccount( &userInput, deletedType ) )
            cout << "\n[✓] Account deleted." << endl;
        else
            cout << "\n[✗] Failed to delete account." << endl;
    

        cout << "\nWould you like to delete another account (y/n)? ";
        getline ( cin, userInput );

    } while ( userInput.at ( 0 ) == 'y' );
}


/**
 * 
 * NOT FUNCTIONING CORRECTLY - Doesn't update stuff. Prob because I am not using pointers correctly somewhere. Its late...
 * 
 */
void editAccount ( accountManager & accounts ) {
    string userInput = "";
    string newValue = "";
    Address * accountAddress = NULL;
    infoStruct * accountInfo = NULL;
    Account * accountToEdit = NULL;
    Account * editedAccount = NULL;
    ACCOUNT_TYPE type = (ACCOUNT_TYPE)0;

    do { 
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                Account Editing Menu" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "              Enter account ID to edit: ";

        getline ( cin, userInput );


        type = (ACCOUNT_TYPE) ( ( int ) userInput.at ( 0 ) - '0' );
        accountToEdit = accounts.getAccount ( &userInput, type);

        if ( accountToEdit ){
            accountInfo = accountToEdit -> getInfo();
            accountAddress = &accountInfo -> theAddress;

            cout << endl;
            cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
            cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
            cout << "│                Account Editing Menu" << endl;
            cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
            cout << "│    ID......: " << accountInfo -> ID << endl;
            cout << "│ 1. Name....: " << accountInfo -> name << endl;
            cout << "│ 2. Email...: " << accountInfo -> email << endl;
            cout << "│ 3. Address.: " << *accountAddress -> getStreetAddress() << endl; 
            cout << "│ 4. City....: " << *accountAddress -> getCity() << endl; 
            cout << "│ 5. State...: " << *accountAddress -> getState() << endl;  
            cout << "│ 6. Zip Code: " << *accountAddress -> getZipcode() << endl;  

            if (( int ) userInput.at ( 0 ) - '0' < 3 )//show provider/manager level data members
                cout << "│    Password: XXXXXXXXX"<< endl;//Protected info
            
                cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
                cout << "        What would you like to update?: ";
                getline ( cin, userInput );
                cout << "        What is the new value?........: ";
                getline ( cin, newValue );

                switch ( ( int ) userInput.at ( 0 ) - '0' ) {
                case 1:
                    accountToEdit -> setInfo(&newValue, &accountInfo -> email, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                case 2:
                    accountToEdit -> setInfo(&accountInfo -> name, &newValue, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                case 3:
                    accountAddress -> setAddress(&newValue, accountAddress -> getCity(), accountAddress -> getState(), accountAddress -> getZipcode());
                    accountToEdit -> setInfo(&accountInfo -> name, &accountInfo -> email, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                case 4:
                    accountAddress -> setAddress(accountAddress -> getStreetAddress(), &newValue, accountAddress -> getState(), accountAddress -> getZipcode());
                    accountToEdit -> setInfo(&accountInfo -> name, &accountInfo -> email, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                case 5:
                    accountAddress -> setAddress(accountAddress -> getStreetAddress(), accountAddress -> getCity(), &newValue, accountAddress -> getZipcode());
                    accountToEdit -> setInfo(&accountInfo -> name, &accountInfo -> email, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                case 6:
                    accountAddress -> setAddress(accountAddress -> getStreetAddress(), accountAddress -> getCity(), accountAddress -> getState(), &newValue);
                    accountToEdit -> setInfo(&accountInfo -> name, &accountInfo -> email, &accountInfo -> ID, accountAddress, (SECURITY_LEVEL) accountInfo -> securityLevel);
                    break;
                //case 7: //Need to be able to update password
                    //accountToEdit.setInfo(accountInfo -> name, accountInfo -> ID, accountInfo -> email, accountAddress, accountInfo -> securityLevel);
                    break;
                    
                default:
                    cout << "\n[✗] \"" << userInput << "\" is not an option\n" << endl;
            }

            accountInfo = accountToEdit -> getInfo();
            accountAddress = &accountInfo -> theAddress;//ERROR
            
            //Update the Account in the database
            accounts.editAccount(&accountInfo->ID, accountToEdit, accountToEdit->getSecurityLevel());

            cout << endl;
                cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
                cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
                cout << "│                Account Editing Menu" << endl;
                cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
                cout << "│    ID......: " << accountInfo -> ID << endl;
                cout << "│ 1. Name....: " << accountInfo -> name << endl; 
                cout << "│ 2. Email...: " << accountInfo -> email << endl; 
                cout << "│ 3. Address.: " << *accountAddress -> getStreetAddress() << endl; 
                cout << "│ 4. City....: " << *accountAddress -> getCity() << endl; 
                cout << "│ 5. State...: " << *accountAddress -> getState() << endl;  
                cout << "│ 6. Zip Code: " << *accountAddress -> getZipcode() << endl;  

            if (( int ) userInput.at ( 0 ) - '0' < 3 )//show provider/manager level data members
                cout << "│    Password: XXXXXXXXX"<< endl;//Protected info //Need to be able to update password
            
                cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
                cout << "               [✓] Account updated";

            cout << "\nWould you like to edit another account (y/n)? ";
            getline ( cin, userInput );

        } else {
            cout << "\n[✗] No Account Exists for User ID#: "<< userInput << "\n" << endl;
            waitForEnter();
        }

    } while ( userInput.at ( 0 ) == 'y' );
}

//Display an account on the screen
void viewAccount ( accountManager & accounts ) {
    
    string userInput = "";
    string typeSTR = "";
    ACCOUNT_TYPE type = init;
    Account * toDisplay = NULL;
    
    do {
        cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
        cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
        cout << "│                Account Viewing Menu" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "              Enter account ID to view: ";
        
        getline ( cin, userInput );
        
        //Check account type
        if(userInput[0] == '1') {
            type = manager;
            typeSTR = "Manager";
        }
        else if(userInput[0] == '2') {
            type = provider;
            typeSTR = "Provider";
        }
        else{
            type = member;
            typeSTR = "Member";
        }
        
        //Find the Account
        toDisplay = accounts.getAccount(&userInput, type);
        
        //If an account is found
        if(toDisplay){
            if(type == manager)
                static_cast<Manager*>(toDisplay)->displayToUI();
            if(type == provider)
                static_cast<Provider*>(toDisplay)->displayToUI();
            if(type == member)
                static_cast<Member*>(toDisplay)->displayToUI();
        
        }
        //If an account is NOT found
        else {
            cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
            cout << "\n[✗] No Account Exists for User ID# "<< userInput << endl;
            cout << "    Please check the ID number and try again. " << endl;
            
        }
        
    }while(again("Would you like to view another account? (y/n):"));
}

//Creates a new Service and add it to the providerDirectory.
bool createService(providerDirectory &master) {
	char input[21];
        char * temp;
        float fee = 0;
        string id;
        char c;
        int getID = 0;
        Service toAdd;

	//Gets Service Name from user.
        cout << "\nPlease enter the name of the service: ";
        cin.get(input, 21, '\n');
        cin.ignore(100, '\n');
        temp = new char[strlen(input) + 1];
        strcpy(temp, input);
        for(int i = 0; i < strlen(temp); ++i) {
            temp[i] = toupper(temp[i]);
        }
        toAdd.name = temp;

        if(temp)
            delete [] temp;
        temp = NULL;

        //Gets Service Fee from user.
	cout << "\nPlease enter the cost of the service: $";
        cin >> fee;
 
        //Checks for numerical input.
        if(cin.fail()) {
            cout << "Please enter #'s only eg. (000.00)" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            return false;
        }
        cin.ignore(100, '\n');

        //Makes sure input is within correct range. 
        if(fee > 999.99 || fee < 0) {
            cout << "That value is not within the acceptable price range ($0-$999.99)" << endl;
            return false;
        }
        else {
            toAdd.fee = fee;
            srand(time(NULL));

	    //Generates random Service ID number.
            do {
                getID = (rand() % 899999) + 100000;
                id = toString(getID);
            }while(master.checkID(id));

            toAdd.serviceID = id;

            if(master.addService(toAdd)) {
                master.displayService(id);

                //Gets confirmation from user.
                do {
                    cout << "\nIs this information correct?" << endl
                         << "Please enter (y/n): ";
                    cin >> c;
                    c = tolower(c);
                    cin.ignore(100, '\n');
                }while(!(c == 'y' || c == 'n'));

                if(c == 'y')
                    return true;
                else {
                    if(master.removeService(id))
                        return false;
                }
            }
            else
                return false;
	}
}

//Gets a service code from the user and removes it from 
//the providerDirectory.
bool deleteService(providerDirectory &master) {
	char input[7];
	char * temp;
        char c;
	string id;

        //Gets a service code from the user.
	cout << "Please enter the 6-digit ID of the service to be removed: ";
	cin.get(input, 7, '\n');
	cin.ignore(100, '\n');
	temp = new char[strlen(input) + 1];
	strcpy(temp, input);
	id = temp;
        
        if(temp)
            delete [] temp;
        temp = NULL;

        //Validates the user input service code.
        if(master.displayService(id)) {
            do {
                cout << "\nAre you sure you want to remove this service?" << endl
                     << "Please enter (y/n): ";
                cin >> c;
                c = tolower(c);
                cin.ignore(100, '\n');
            }while(!(c == 'y' || c == 'n'));

            if(c == 'n') 
                return false;
 
            //Removes the service upon user confirmation. 
            else {
                if(master.removeService(id))
                    return true;
                else
                    return false;
            }
        }
	else {
            cout << "\nService ID was not found." << endl;
            return false;     
        }
}

//Updates a service fee in the providerDirectory.
bool updateService(providerDirectory &master) {
	char input[7];
	char * temp;
        char c;
	string id;
        float fee;

        //Gets a service code to update from the user.
	cout << "Please enter the 6-digit ID of the service to be updated: ";
	cin.get(input, 7, '\n');
	cin.ignore(100, '\n');
	temp = new char[strlen(input) + 1];
	strcpy(temp, input);
	id = temp;

        if(temp)
            delete temp;
        temp = NULL;

        //Checks providerDirectory for service code.
        if(master.displayService(id)) {
            do {
                cout << "\nAre you sure you want to update this service?" << endl
                     << "Please enter (y/n): ";
                cin >> c;
                c = tolower(c);
                cin.ignore(100, '\n');
            }while(!(c == 'y' || c == 'n'));

            if(c == 'n')
                return false;
            else {
 	        cout << "\nPlease enter the cost of the service: $";
                cin >> fee;
 
                //Checks for numerical input.
                if(cin.fail()) {
                cout << "Please enter #'s only eg. (000.00)" << endl;
                cin.clear();
                cin.ignore(100, '\n');
                return false;
                }
                cin.ignore(100, '\n');

                //Makes sure input is within correct range. 
                if(fee > 999.99 || fee < 0) {
                    cout << "That value is not within the acceptable price range ($0-$999.99)" << endl;
                    return false;
                }

                //Updates service fee upon valid input.
                else {
                    if(master.updateFee(id, fee))
                        return true;
                    else
                        return false;
                }
            }
        }
	else {
            cout << "\nService ID was not found." << endl;
            return false;     
        }
}

//Writes the Managers Summary Report to a file.
bool writeManageReport(managersReport * toWrite) {
    string filename("reports/manager/"+("summaryReport"+currentDateTime()) + ".txt");
    ofstream fileOut;
    bool toReturn = false;
    map <string, map <int, float> >::iterator i;
    fileOut.open(filename.c_str());

    if(fileOut) {
        toReturn = true;
        fileOut << "Current Date and Time: " << currentDateTime() << endl
                << "\n********PROVIDERS TO BE PAID********\n" << endl;
    
        for(i= toWrite->providerDetails.begin(); i != toWrite->providerDetails.end(); ++i) {
            map <int, float> :: iterator j = i->second.begin();

            fileOut << "\nProvider ID: " << i -> first << endl
                    << "Members Seen: " << j -> first << endl
                    << "Fees Due: $" << j -> second << endl;
        }

        fileOut << "\nTotal Providers: " << toWrite -> totalProviders << endl
                << "Total Consultations: " << toWrite -> totalConsults << endl
                << "Total Fees Owed: $" << toWrite -> totalFees << endl
                << "\n\n\n********END REPORT********" << endl;
	}
    
    fileOut.close();
    return toReturn;
}

//Writes all Provider Reports to files.
void writeProviderReports(list <providersReport> * toWrite) {

        ofstream fileOut;
        list <providersReport> :: iterator i = toWrite -> begin();
        int count = 1;

        //Cycles through providerReports opens a unique file and writes info.
        for(i; i != toWrite -> end(); ++i) {
            string id(i -> providerID);
            string filename("reports/provider/" + id + "-" + currentDateTime() + ".txt");
            fileOut.open(filename.c_str());

            if(fileOut) {
                fileOut << "********PROVIDER REPORT********" << endl
                        << "\nProvider Name: " << i -> providerName << endl
                        << "Provider ID: " << i -> providerID << endl
                        << "Street Address: " << *i -> theAddress.getStreetAddress() << endl
                        << "City: " << *i -> theAddress.getCity() << endl
                        << "State: " << *i -> theAddress.getState() << endl
                        << "Zipcode: " << *i -> theAddress.getZipcode() << endl
                        << "\n****SERVICE RECORD****" << endl;

               //Cycles through serviceRecord and writes info.
               list <providerRecord> :: iterator j = i -> serviceRecord.begin();
               for(j; j != i -> serviceRecord.end(); ++j) {
                   fileOut << "\nService #" << count << ":" << endl 
                           << "Service Date: " << j -> dateOfService << endl
                           << "Record Received: " << j -> currentDateTime << endl
                           << "Member Name: " << j -> memberName << endl
                           << "Member ID: " << j -> memberID << endl
                           << "Service Code: " << j -> serviceCode << endl
                           << "Service Fee: $" << j -> serviceFee << endl;
                   ++count;
               }
               fileOut << "\n****END SERVICE RECORD****" << endl
                       << "\nTotal Consultations: " << i -> consultations << endl
                       << "Total Fee: $" << i -> weekFee << endl
                       << "\n********END PROVIDER REPORT********" << endl;
               
               fileOut.close();
               count = 1;
           }
       }
}

//Writes all Member Reports to files.
void writeMemberReports(list <membersReport> * toWrite) {

        ofstream fileOut;
        list <membersReport> :: iterator i = toWrite -> begin();
        int count = 1;

        //Cycles through memberReports opens a unique file and writes info.
        for(i; i != toWrite -> end(); ++i) {
            string id(i -> memberID);
            string filename("reports/member/" + id + "-" + currentDateTime() + ".txt");
            fileOut.open(filename.c_str());

            if(fileOut) {
                fileOut << "********MEMBER REPORT********" << endl
                        << "\nMember Name: " << i -> memberName << endl
                        << "Member ID: " << i -> memberID << endl
                        << "Street Address: " << *i -> theAddress.getStreetAddress() << endl
                        << "City: " << *i -> theAddress.getCity() << endl
                        << "State: " << *i -> theAddress.getState() << endl
                        << "Zipcode: " << *i -> theAddress.getZipcode() << endl
                        << "\n****SERVICE RECORD****" << endl;

               //Cycles through serviceRecord and writes info.
               list <memberRecord> :: iterator j = i -> serviceRecord.begin();
               for(j; j != i -> serviceRecord.end(); ++j) {
                   fileOut << "\nService #" << count << ":" << endl 
                           << "Service Date: " << j -> dateOfService << endl
                           << "Provider Name: " << j -> providerName << endl
                           << "Service Name: " << j -> serviceName << endl;
                   ++count;
               }
               fileOut << "\n****END SERVICE RECORD****" << endl
                       << "\n\n********END MEMBER REPORT********" << endl;
               
               fileOut.close();
               count = 1;
           }
       }
}

//Gets a Provider Report and writes it to a file.
bool getProviderReport(reportManager & reports, accountManager & accounts) {

        string * id;
        char userInput[20];
        Provider * toGet = NULL;

        //Gets a Provider ID from the user.
        cout << "\nPlease Enter a Valid Provider ID: ";
        cin.get(userInput, 20, '\n');
        cin.ignore(100, '\n');

        id = new string(userInput);
        toGet = static_cast<Provider*>(accounts.getAccount(id, provider));

        //If the provider was found and their report generated
        //this calls the write to file function.
	if(toGet) {
            writeProviderRpt(reports.providerReport(*toGet));

            toGet = NULL;
            if(id) {
                delete id;
                id = NULL;
            }
            return true;
        }
        else {
            if(id) {
                delete id;
                id = NULL;
            }
            return false;
        }
    
}
   
//Writes a Provider Report to a file. 
void writeProviderRpt(providersReport * toWrite) {

        ofstream fileOut;
        int count = 1;
        string id(toWrite -> providerID);
        string filename("reports/provider/" + id + "-" + currentDateTime() + ".txt");

        fileOut.open(filename.c_str());

        if(fileOut) {
            fileOut << "********PROVIDER REPORT********" << endl
                    << "\nProvider Name: " << toWrite -> providerName << endl
                    << "Provider ID: " << toWrite -> providerID << endl
                    << "Street Address: " << *toWrite -> theAddress.getStreetAddress() << endl
                    << "City: " << *toWrite -> theAddress.getCity() << endl
                    << "State: " << *toWrite -> theAddress.getState() << endl
                    << "Zipcode: " << *toWrite -> theAddress.getZipcode() << endl
                    << "\n****SERVICE RECORD****" << endl;

               //Cycles through serviceRecord and writes info.
            list <providerRecord> :: iterator j = toWrite -> serviceRecord.begin();
            for(j; j != toWrite -> serviceRecord.end(); ++j) {
                fileOut << "\nService #" << count << ":" << endl 
                        << "Service Date: " << j -> dateOfService << endl
                        << "Record Received: " << j -> currentDateTime << endl
                        << "Member Name: " << j -> memberName << endl
                        << "Member ID: " << j -> memberID << endl
                        << "Service Code: " << j -> serviceCode << endl
                        << "Service Fee: $" << j -> serviceFee << endl;
                ++count;
            }
            fileOut << "\n****END SERVICE RECORD****" << endl
                    << "\nTotal Consultations: " << toWrite -> consultations << endl
                    << "Total Fee: $" << toWrite -> weekFee << endl
                    << "\n********END PROVIDER REPORT********" << endl;
               
            fileOut.close();
       }
}

//Gets a Member Report and writes it to a file.
bool getMemberReport(reportManager & reports, accountManager & accounts) {

        string * id;
        char userInput[20];
        Member * toGet = NULL;

        //Gets Member ID from user.
        cout << "\nPlease Enter a Valid Member ID: ";
        cin.get(userInput, 20, '\n');
        cin.ignore(100, '\n');

        id = new string(userInput);
        toGet = static_cast<Member*>(accounts.getAccount(id, member));

        //If the Member was found and their report generated
        //this calls the write report function.
	if(toGet) {
            writeMemberRpt(reports.memberReport(*toGet));

            toGet = NULL;
            if(id) {
                delete id;
                id = NULL;
            }
            return true;
        }
        else {
            if(id) {
                delete id;
                id = NULL;
            }
            return false;
        }
    
}

//Writes Member Report to file.    
void writeMemberRpt(membersReport * toWrite) {

        ofstream fileOut;
        int count = 1;
        string id(toWrite -> memberID);
        string filename("reports/member/" + id + "-" + currentDateTime() + ".txt");

        fileOut.open(filename.c_str());

        if(fileOut) {
            fileOut << "********MEMBER REPORT********" << endl
                    << "\nMember Name: " << toWrite -> memberName << endl
                    << "Member ID: " << toWrite -> memberID << endl
                    << "Street Address: " << *toWrite -> theAddress.getStreetAddress() << endl
                    << "City: " << *toWrite -> theAddress.getCity() << endl
                    << "State: " << *toWrite -> theAddress.getState() << endl
                    << "Zipcode: " << *toWrite -> theAddress.getZipcode() << endl
                    << "\n****SERVICE RECORD****" << endl;

           //Cycles through serviceRecord and writes info.
           list <memberRecord> :: iterator j = toWrite -> serviceRecord.begin();
           for(j; j != toWrite -> serviceRecord.end(); ++j) {
               fileOut << "\nService #" << count << ":" << endl 
                       << "Service Date: " << j -> dateOfService << endl
                       << "Provider Name: " << j -> providerName << endl
                       << "Service Name: " << j -> serviceName << endl;
               ++count;
           }
           fileOut << "\n****END SERVICE RECORD****" << endl
                   << "\n\n********END MEMBER REPORT********" << endl;
               
           fileOut.close();
        }
}

bool getEFT(reportManager & reports, accountManager & accounts) {
    Provider * providerAccount = NULL;
    string userID;

    cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ChocAn]━┑" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "│               EFT generation Menu" << endl;
    cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
    cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
    cout << "                 Enter Provider ID#: ";

    getline ( cin, userID );
    providerAccount = static_cast < Provider * > ( accounts.getAccount( &userID, provider) );

    if ( providerAccount ) 
        return writeEFT ( reports.generateEFT ( providerAccount ) );

    return false;
}

//Writes EFT Report to file.
bool writeEFT(eft * toWrite) {
    ofstream fileOut;
    int count = 1;
    string id(toWrite -> providerID);
    string filename("reports/eft/" + id + "-" + currentDateTime() + ".txt");

    fileOut.open(filename.c_str());

    if(fileOut) {
        fileOut << "********EFT REPORT********" << endl
                << "\nProvider Name: " << toWrite -> providerName << endl
                << "Provider ID: " << toWrite -> providerID << endl
                << "Total Fees: " << toWrite -> totalFee << endl
               << "\n\n********END EFT REPORT********" << endl;
           
       fileOut.close();

       return true;
    }

    return false;
}

/*
PARKING LOT

*/
