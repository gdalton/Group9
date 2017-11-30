//  CS300 - Group 9
//  Filename: main.cpp


#include "mainHeader.h"

int main(int argc, const char * argv[]) {


	string userID = "";
	string password = "";
	Account * account = NULL;
	Manager * manager = NULL;
	Provider * provider = NULL;


	int loginAttempts = 0;
	ACCOUNT_TYPE accountType = ( ACCOUNT_TYPE ) 0;
	accountManager accounts;
	Warden security;

		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑" << endl;
		cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
		cout << "│                       ChocAn" << endl;
		cout << "│                     Login Menu" << endl;
		cout << "┝━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┥" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << endl;
	do {

		cout << "Account ID: ";
		getline ( cin, userID );
		cout << "password: ";
		getline ( cin, password );


		account = accounts.getAccount( &userID, ( ACCOUNT_TYPE ) ( userID.at ( 0 ) - '0' ) );//check what this is returning, account?
		//check_train = dynamic_cast <train *> (transit_to_copy);
		
		if ( account ) {
			switch ( userID.at ( 0 ) - '0' ) {
				case 1:
					manager = static_cast < Manager * > ( account );

					if( ! manager )
						cerr << "Double account type authentication failed." << endl;
					else{
						cout << "Account is a Manager" << endl;
						//runManagerMenu();
					}
					return 0;

				break;
				case 2:
					provider = static_cast < Provider * > ( account );

					if( ! provider )
						cerr << "Double account type authentication failed." << endl;
					else{
						cout << "Account is a Provider" << endl;
						//runProviderMenu();
					}
					return 0;
				break;
				default:
				return 1;
			}
		} else {
		 	cout << "\n[✗] (Failed login " << ++loginAttempts << "/3) " << endl;

		 	if ( loginAttempts < 3 ) 
		 		cout <<   "    There is no account with that password. Try again..." << endl;
		 	else {
		 		cout << "\n You failed to log in too many times." << endl;
				cout <<   " Contact your administrator to regain access to your account.\n" << endl;
				return 0;
			}
		}
	} while ( loginAttempts < 3);

	return 0;
}