/* filename: userInterface.cpp
* Programmers: Matthew Greenlaw, Katie Loveland
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
bool createService(providerDirectory &master);

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

/** Starts up the whole system and runs the UI.
 * @return     True if the user exits normally, false otherwise
 */
bool UserInterface :: runSystem ( void ) {
    bool toReturn = false;
    
    int selection = 0;
    
    //Welcome the user and explain the program
    printLine(50);
    cout<<"           Welcome to the ChocAn HCS"<<endl;
    printLine(50);
    cout<<endl<<endl;
    
    //Login Function here
    
    do
    {
        //Get the user's selection
        selection = userSelection();
        switch(selection)
        {
            case 1:
                //Some function call...
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 2:
                //Some function call...
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 3:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 4:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 5:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 9:
                //Close the program
                cout<<"Program closed... Thank you!"<<endl;
                break;
                
            default:
                cout<<"An unknown error occured!"<<endl;
                
        }
    }while(selection<=8);

    
    return toReturn;
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
      cout << "password: ";
      getline ( cin, password );


      account = accounts.getAccount( &userID, ( ACCOUNT_TYPE ) ( userID.at ( 0 ) - '0' ) );//check what this is returning, account?
      
      if ( account ) {
         switch ( userID.at ( 0 ) - '0' ) {
            case 1:
               manager = static_cast < Manager * > ( account );

               if( manager )
                  return runManagerMenu();
            break;
            case 2:
               provider = static_cast < Provider * > ( account );

               if( provider )
                  return runProviderMenu();
            break;
            default:
               return 0;
         }
      } else {
         cout << "\n[✗] (Failed login " << ++loginAttempts << "/3) " << endl;

         if ( loginAttempts < 3 ) 
            cout <<   "    There is no account with that password. Try again..." << endl;
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


//Function to allow the user to select a number for the switch statement
int UserInterface::userSelection()
{
    int userSelection=0;
    
    do
    {
        cout<<"************************************************"<<endl;;
        cout<<"            ChocAn Manager Menu"<<endl;;
        cout<<"************************************************"<<endl;
        
        //Print out the menu options
        cout<<"1. Add a Account"<<endl;
        cout<<"2. Run Reports"<<endl;
        cout<<"3. Set member status"<<endl;
        cout<<"9. Exit program."<<endl;
        
        read_num("\nPlease make a selection:", userSelection);
        
    }while(userSelection<1 || userSelection>9);
    
    return userSelection;
}

/** Runs the provider menu system. It presents the provider with a series of
 * commands for the provider to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runProviderMenu () {
    Account * accountToCheck = NULL;
    Member * memberToCheck = NULL;
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
        cout << "│ 4. Create Service Report" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "                       Option: ";

        getline( cin, userInput );

        switch ( (int) userInput.at ( 0 ) - '0' ) {
            case 0:
                return true;
                break;

            case 1:
                cout << "\nEnter service ID: ";
                getline( cin, userInput );
                if (!directory.displayService ( userInput ) )
                    cout << "\n[✗] Invlaid service ID.\n";
                break;

            case 2:
                cout << "\nEnter member ID: ";
                getline( cin, userInput );
                accountToCheck = accounts.getAccount( &userInput, member);
                memberToCheck = static_cast < Member * > ( accountToCheck );

                if ( memberToCheck ){
                    cout << "Member " << userInput << ": ";

                    if ( memberToCheck -> getMemberStatus() == current )
                        cout  << "CURRENT";
                    else cout  << "EXPIRED";

                } else cout << "\n[✗] Invlaid member ID.\n";

                break;

            case 3:
                //@todo Where is generateServiceRecord()?
                break;

            case 4:
                //@todo Where is generateServiceReport()?
                break;

            default:
                cout << "\n[✗] \"" << userInput << "\" is not an option\n" << endl;
        }
    } while ( ( int ) userInput.at ( 0 ) - '0' != 0 );


}

/** Runs the manager menu system. It presents the manager with a series of
 * commands for the manger to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runManagerMenu ( void ) {
    string userInput = "";
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
        cout << "│ 8. View ProviderDirectory" << endl;
        cout << "│" << endl;
        cout << "│ Reports:" << endl;
        cout << "│ 9. Generate Manager Report" << endl;
        cout << "│ 10. Generate Provider Report" << endl;
        cout << "│ 11. Generate Member Report" << endl;
        cout << "│ 12. Generate EFT Report" << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "                       Option: ";

        getline( cin, userInput );

        switch ( (int) userInput.at ( 0 ) - '0' ) {
            case 0:
                return true;
                break;

            case 1:

                createAccount ( accounts );
                
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:
            
                if(createService( directory ))
                    cout << "\nService added successfully!" << endl;
                else
                    cout << "\nService was not added." << endl;

                break;

            case 6:

                break;

            case 7:

                break;

            case 8:

                break;

            case 9:

                break;

            case 10:

                break;

            case 11:

                break;

            case 12:

                break;

            default:
                cout << "\n[✗] \"" << userInput << "\" is not an option\n" << endl;
        }

    } while ( ( int ) userInput.at ( 0 ) - '0' != 0 );
}

void createAccount( accountManager & accounts ) {

    string userInput = "";
    Manager * newManager = NULL;
    Provider * newProvider = NULL;
    Member * newMember = NULL;

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
            cout << "\n[✗] \"" << userInput << "\" is not an option\n" << endl;
    }

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
        cout << "│ password: "; getline ( cin, password);
        ID = *accounts.generateAccountID(manager);
        cout << "│ ID......: " << ID << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "         Is this information correct? (y/n):"; 
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    ID = *accounts.generateAccountID(manager);
    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount ( new Manager ( &name, &email, &ID, &newAddress, manager, &password ), manager ) )
        cout << "\n[✓] Account added." << endl;
    else 
        cout << "\n[✗]Failed to add account." << endl;
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
        cout << "│ password: "; getline ( cin, password);
        ID = *accounts.generateAccountID(provider);
        cout << "│ ID......: " << ID << endl;
        cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
        cout << "         Is this information correct? (y/n):"; 
        getline ( cin, userInput);
    } while ( userInput.at ( 0 ) != 'y' );

    ID = *accounts.generateAccountID(provider);
    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount (new Provider ( &name, &email, &ID, &newAddress, provider, &password, 0, *newServiceRecord ), provider ) )
        cout << "\n[✓] Account added." << endl;
    else 
        cout << "\n[✗]Failed to add account." << endl;

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

    ID = *accounts.generateAccountID(member);
    newAddress.setAddress ( &address, &city, &state, &zip );
    
    if ( accounts.addAccount ( new Member ( &name, &email, &ID, &newAddress, member, current, newMemberRecords ), member ) )
        cout << "\n[✓] Account added." << endl;
    else 
        cout << "\n[✗]Failed to add account." << endl;
}

void deleteAccount ( accountManager & accounts ) {
//bool accountManager::removeAccount(string* accountID, ACCOUNT_TYPE type){
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

        cout << "\nWould you like to delete another account (y/n)? ";
        getline ( cin, userInput );

    } while ( userInput.at ( 0 ) == 'y' );
    

    if ( accounts.removeAccount( &userInput, deletedType ) )
        cout << "\n[✓] Account deleted." << endl;
    else 
        cout << "\n[✗]Failed to delete account." << endl;

}


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
            cout << "That service is too expensive we will not accept services\n"
                 << "costing more than $999.99." << endl;
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

/*
PARKING LOT

*/
